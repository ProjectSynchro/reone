/*
 * Copyright (c) 2020-2023 The reone project contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "reone/movie/movie.h"

#include "reone/audio/di/services.h"
#include "reone/audio/player.h"
#include "reone/graphics/context.h"
#include "reone/graphics/di/services.h"
#include "reone/graphics/mesh.h"
#include "reone/graphics/meshes.h"
#include "reone/graphics/shaders.h"
#include "reone/graphics/textures.h"
#include "reone/graphics/textureutil.h"
#include "reone/graphics/uniforms.h"

using namespace reone::audio;
using namespace reone::graphics;

namespace reone {

namespace movie {

void Movie::init() {
    if (_inited) {
        return;
    }
    if (!_texture && _videoStream) {
        _width = _videoStream->width();
        _height = _videoStream->height();
        _texture = std::make_shared<Texture>("video", getTextureProperties(TextureUsage::Movie));
        _texture->clear(1, 1, PixelFormat::RGB8, 1);
    }
    if (!_audioSource && _audioStream) {
        _audioSource = _audioSvc.player.play(_audioStream, AudioType::Movie);
    }
    _inited = true;
}

void Movie::deinit() {
    if (!_inited) {
        return;
    }
    if (_audioSource) {
        _audioSource.reset();
    }
    if (_audioStream) {
        _audioStream.reset();
    }
    if (_texture) {
        _texture.reset();
    }
    if (_videoStream) {
        _videoStream.reset();
    }
    _inited = false;
}

void Movie::update(float dt) {
    if (!_inited) {
        init();
    }
    if (!_videoStream || _finished) {
        return;
    }
    _time += dt;
    _videoStream->seek(_time);
    if (_videoStream->hasEnded()) {
        _finished = true;
        return;
    }
    if (_audioSource) {
        _audioSource->update();
    }
}

void Movie::render() {
    if (!_inited) {
        init();
    }
    if (!_videoStream) {
        return;
    }
    auto &frame = _videoStream->frame();
    if (frame.pixels) {
        _graphicsSvc.textures.bind(*_texture);
        _texture->setPixels(_width, _height, PixelFormat::RGB8, Texture::Layer {frame.pixels}, true);
    }
    _graphicsSvc.uniforms.setGeneral([](auto &general) {
        general.resetGlobals();
        general.resetLocals();
        general.uv = glm::mat3x4(
            glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
            glm::vec4(0.0f, -1.0f, 0.0f, 0.0f),
            glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
    });
    _graphicsSvc.shaders.use(ShaderProgramId::GUI);
    _graphicsSvc.meshes.quadNDC().draw();
}

} // namespace movie

} // namespace reone
