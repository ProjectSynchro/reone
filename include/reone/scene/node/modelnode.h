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

#include "reone/graphics/modelnode.h"
#include "reone/graphics/texture.h"

#include "../node.h"

namespace reone {

namespace scene {

class ModelNodeSceneNode : public SceneNode {
public:
    const graphics::ModelNode &modelNode() const { return _modelNode; }

    virtual void setDiffuseMap(graphics::Texture *texture);
    virtual void setEnvironmentMap(graphics::Texture *texture);

protected:
    graphics::ModelNode &_modelNode;

    ModelNodeSceneNode(
        graphics::ModelNode &modelNode,
        SceneNodeType type,
        SceneGraph &sceneGraph,
        graphics::GraphicsServices &graphicsSvc,
        audio::AudioServices &audioSvc) :
        SceneNode(
            type,
            sceneGraph,
            graphicsSvc,
            audioSvc),
        _modelNode(modelNode) {
    }
};

} // namespace scene

} // namespace reone
