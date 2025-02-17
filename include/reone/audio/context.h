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

#pragma once

namespace reone {

namespace audio {

class IAudioContext {
public:
    virtual ~IAudioContext() = default;

    virtual void setListenerPosition(glm::vec3 position) = 0;
};

class AudioContext : public IAudioContext, boost::noncopyable {
public:
    ~AudioContext() { deinit(); }

    void init();
    void deinit();

    void setListenerPosition(glm::vec3 position) override;

private:
    ALCdevice *_device {nullptr};
    ALCcontext *_context {nullptr};

    glm::vec3 _listenerPosition {0.0f};
};

} // namespace audio

} // namespace reone
