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

#include "reone/scene/node/particle.h"

#include "reone/graphics/modelnode.h"

#include "reone/scene/node/emitter.h"

using namespace reone::graphics;

namespace reone {

namespace scene {

void ParticleSceneNode::update(float dt) {
    // Lightning emitters are updated elsewhere
    auto &modelNode = _emitter.modelNode();
    if (modelNode.emitter()->updateMode == ModelNode::Emitter::UpdateMode::Lightning) {
        return;
    }

    if (_emitter.lifeExpectancy() != -1.0f) {
        _lifetime = glm::min(_lifetime + dt, _emitter.lifeExpectancy());
        if (isExpired()) {
            return;
        }
    } else if (_lifetime == _animLength) {
        _lifetime = 0.0f;
    } else {
        _lifetime = glm::min(_lifetime + dt, _animLength);
    }

    auto transform = _localTransform;
    transform *= glm::translate(_velocity * dt);
    setLocalTransform(std::move(transform));

    // A particle's position and velocity are in emitter space, as is the target.
    if (auto &target = _emitter.gravityTarget()) {
        glm::vec3 toTarget(*target - glm::vec3(_localTransform[3]));
        float distance = glm::length(toTarget);
        if (distance > 0.0f) {
            _velocity += _emitter.grav() * (toTarget / distance) * dt;
        }
    }

    updateAnimation(dt);
}

void ParticleSceneNode::updateAnimation(float dt) {
    float factor;
    if (_emitter.lifeExpectancy() != -1.0f) {
        factor = _lifetime / static_cast<float>(_emitter.lifeExpectancy());
    } else if (_animLength > 0.0f) {
        factor = _lifetime / _animLength;
    } else {
        factor = 0.0f;
    }

    // A zero authored frame rate is a static atlas selection in Odyssey. It
    // does not mean that the frame range should be spread over particle life.
    if (_animLength > 0.0f) {
        _frame = static_cast<int>(glm::ceil(_emitter.frameStart() + factor * (_emitter.frameEnd() - _emitter.frameStart())));
    } else {
        _frame = _emitter.frameStart();
    }
    _size = glm::vec2(_emitter.getParticleSize(factor));
    _color = _emitter.getColor(factor);
    _alpha = _emitter.getAlpha(factor);
}

bool ParticleSceneNode::isExpired() const {
    return _lifetime >= _emitter.lifeExpectancy();
}

} // namespace scene

} // namespace reone
