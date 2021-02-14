/*
 * Copyright (c) 2020-2021 The reone project contributors
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

#pragma once

#include <functional>
#include <memory>
#include <vector>

#include <boost/noncopyable.hpp>

#include "glm/vec3.hpp"

#include "../render/shaders.h"
#include "../render/types.h"

namespace reone {

namespace scene {

class CameraSceneNode;
class EmitterSceneNode;
class LightSceneNode;
class ModelNodeSceneNode;
class SceneNode;

class SceneGraph : boost::noncopyable {
public:
    SceneGraph(const render::GraphicsOptions &opts);

    void update(float dt);
    void render(bool shadowPass = false);

    void clear();
    void addRoot(const std::shared_ptr<SceneNode> &node);
    void removeRoot(const std::shared_ptr<SceneNode> &node);

    /**
     * Prepares this scene graph for rendering the next frame. Meshes, lights
     * and particles are extracted from the root scene nodes and sorted by
     * distance to camera. Lighting sources are selected for each model.
     */
    void prepareFrame();

    std::shared_ptr<CameraSceneNode> activeCamera() const { return _activeCamera; }
    render::ShaderUniforms baseUniforms() const { return _baseUniforms; }

    void setActiveCamera(const std::shared_ptr<CameraSceneNode> &camera);
    void setShadowReference(const std::shared_ptr<SceneNode> &node);
    void setUpdate(bool update);
    void setBaseUniforms(render::ShaderUniforms uniforms);

    // Lights and shadows

    bool isShadowLightPresent() const { return _shadowLightPresent; }

    void getLightsAt(
        const glm::vec3 &position,
        std::vector<LightSceneNode *> &lights,
        int count = render::kMaxLightCount,
        std::function<bool(const LightSceneNode &)> predicate = [](auto &light) { return true; }) const;

    const glm::vec3 &ambientLightColor() const { return _ambientLightColor; }
    const glm::vec3 &shadowLightPosition() const { return _shadowLightPosition; }

    void setAmbientLightColor(const glm::vec3 &color);

    // END Lights and shadows

private:
    render::GraphicsOptions _opts;

    std::vector<std::shared_ptr<SceneNode>> _roots;
    std::vector<ModelNodeSceneNode *> _opaqueMeshes;
    std::vector<ModelNodeSceneNode *> _transparentMeshes;
    std::vector<ModelNodeSceneNode *> _shadowMeshes;
    std::vector<LightSceneNode *> _lights;
    std::vector<EmitterSceneNode *> _emitters;
    std::shared_ptr<CameraSceneNode> _activeCamera;
    glm::vec3 _ambientLightColor { 0.5f };
    uint32_t _textureId { 0 };
    bool _shadowLightPresent { false };
    glm::vec3 _shadowLightPosition { 0.0f };
    std::shared_ptr<SceneNode> _refNode;
    bool _update { true };
    render::ShaderUniforms _baseUniforms;

    void refreshNodeLists();
    void refreshFromSceneNode(const std::shared_ptr<SceneNode> &node);
    void refreshShadowLight();
};

} // namespace scene

} // namespace reone
