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

#include "reone/graphics/scene.h"

#include "fogproperties.h"
#include "node/camera.h"
#include "node/dummy.h"
#include "node/emitter.h"
#include "node/grass.h"
#include "node/light.h"
#include "node/mesh.h"
#include "node/model.h"
#include "node/sound.h"
#include "node/trigger.h"
#include "node/walkmesh.h"
#include "user.h"

namespace reone {

namespace graphics {

struct GraphicsOptions;
struct GraphicsServices;

class Walkmesh;

} // namespace graphics

namespace audio {

struct AudioServices;

}

namespace scene {

struct Collision;

class IAnimationEventListener;

class ISceneGraph : public graphics::IScene {
public:
    virtual void update(float dt) = 0;

    virtual void clear() = 0;

    virtual void addRoot(std::shared_ptr<ModelSceneNode> node) = 0;
    virtual void addRoot(std::shared_ptr<WalkmeshSceneNode> node) = 0;
    virtual void addRoot(std::shared_ptr<TriggerSceneNode> node) = 0;
    virtual void addRoot(std::shared_ptr<GrassSceneNode> node) = 0;
    virtual void addRoot(std::shared_ptr<SoundSceneNode> node) = 0;

    virtual void removeRoot(ModelSceneNode &node) = 0;
    virtual void removeRoot(WalkmeshSceneNode &node) = 0;
    virtual void removeRoot(TriggerSceneNode &node) = 0;
    virtual void removeRoot(GrassSceneNode &node) = 0;
    virtual void removeRoot(SoundSceneNode &node) = 0;

    virtual bool testElevation(const glm::vec2 &position, Collision &outCollision) const = 0;
    virtual bool testLineOfSight(const glm::vec3 &origin, const glm::vec3 &dest, Collision &outCollision) const = 0;
    virtual bool testWalk(const glm::vec3 &origin, const glm::vec3 &dest, const IUser *excludeUser, Collision &outCollision) const = 0;

    virtual ModelSceneNode *pickModelAt(int x, int y, IUser *except = nullptr) const = 0;

    virtual const std::string &name() const = 0;

    virtual void setAmbientLightColor(glm::vec3 color) = 0;
    virtual void setFog(FogProperties fog) = 0;

    virtual void setWalkableSurfaces(std::set<uint32_t> surfaces) = 0;
    virtual void setWalkcheckSurfaces(std::set<uint32_t> surfaces) = 0;
    virtual void setLineOfSightSurfaces(std::set<uint32_t> surfaces) = 0;

    virtual void setActiveCamera(CameraSceneNode *camera) = 0;
    virtual void setUpdateRoots(bool update) = 0;

    virtual void setDrawAABB(bool draw) = 0;
    virtual void setDrawWalkmeshes(bool draw) = 0;
    virtual void setDrawTriggers(bool draw) = 0;

    virtual std::shared_ptr<CameraSceneNode> newCamera() = 0;
    virtual std::shared_ptr<ModelSceneNode> newModel(graphics::Model &model, ModelUsage usage) = 0;
    virtual std::shared_ptr<WalkmeshSceneNode> newWalkmesh(graphics::Walkmesh &walkmesh) = 0;
    virtual std::shared_ptr<TriggerSceneNode> newTrigger(std::vector<glm::vec3> geometry) = 0;
    virtual std::shared_ptr<SoundSceneNode> newSound() = 0;
    virtual std::shared_ptr<DummySceneNode> newDummy(graphics::ModelNode &modelNode) = 0;
    virtual std::shared_ptr<MeshSceneNode> newMesh(ModelSceneNode &model, graphics::ModelNode &modelNode) = 0;
    virtual std::shared_ptr<LightSceneNode> newLight(ModelSceneNode &model, graphics::ModelNode &modelNode) = 0;
    virtual std::shared_ptr<EmitterSceneNode> newEmitter(graphics::ModelNode &modelNode) = 0;
    virtual std::shared_ptr<ParticleSceneNode> newParticle(EmitterSceneNode &emitter) = 0;
    virtual std::shared_ptr<GrassSceneNode> newGrass(GrassProperties properties, graphics::ModelNode &aabbNode) = 0;
    virtual std::shared_ptr<GrassClusterSceneNode> newGrassCluster(GrassSceneNode &grass) = 0;
};

class SceneGraph : public ISceneGraph, boost::noncopyable {
public:
    SceneGraph(
        std::string name,
        graphics::GraphicsOptions &graphicsOpt,
        graphics::GraphicsServices &graphicsSvc,
        audio::AudioServices &audioSvc) :
        _name(std::move(name)),
        _graphicsOpt(graphicsOpt),
        _graphicsSvc(graphicsSvc),
        _audioSvc(audioSvc) {
    }

    void update(float dt) override;

    void drawShadows() override;
    void drawOpaque() override;
    void drawTransparent() override;
    void drawLensFlares() override;

    const std::string &name() const override {
        return _name;
    }

    CameraSceneNode *activeCamera() const {
        return _activeCamera;
    }

    std::shared_ptr<graphics::Camera> camera() const override {
        return _activeCamera ? _activeCamera->camera() : nullptr;
    }

    void setActiveCamera(CameraSceneNode *camera) override { _activeCamera = camera; }
    void setUpdateRoots(bool update) override { _updateRoots = update; }

    void setDrawAABB(bool draw) override { _drawAABB = draw; }
    void setDrawWalkmeshes(bool draw) override { _drawWalkmeshes = draw; }
    void setDrawTriggers(bool draw) override { _drawTriggers = draw; }

    // Roots

    void clear() override;

    void addRoot(std::shared_ptr<ModelSceneNode> node) override;
    void addRoot(std::shared_ptr<WalkmeshSceneNode> node) override;
    void addRoot(std::shared_ptr<TriggerSceneNode> node) override;
    void addRoot(std::shared_ptr<GrassSceneNode> node) override;
    void addRoot(std::shared_ptr<SoundSceneNode> node) override;

    void removeRoot(ModelSceneNode &node) override;
    void removeRoot(WalkmeshSceneNode &node) override;
    void removeRoot(TriggerSceneNode &node) override;
    void removeRoot(GrassSceneNode &node) override;
    void removeRoot(SoundSceneNode &node) override;

    // END Roots

    // Lighting

    void fillLightingUniforms() override;

    const glm::vec3 &ambientLightColor() const override { return _ambientLightColor; }

    void setAmbientLightColor(glm::vec3 color) override { _ambientLightColor = std::move(color); }

    // END Lighting

    // Fog

    bool isFogEnabled() const override {
        return _fog.enabled;
    }

    float fogNear() const override {
        return _fog.nearPlane;
    }

    float fogFar() const override {
        return _fog.farPlane;
    }

    const glm::vec3 &fogColor() const override {
        return _fog.color;
    }

    void setFog(FogProperties fog) override {
        _fog = std::move(fog);
    }

    // END Fog

    // Shadows

    bool hasShadowLight() const override { return _shadowLight; }
    bool isShadowLightDirectional() const override { return _shadowLight->isDirectional(); }

    glm::vec3 shadowLightPosition() const override { return _shadowLight->getOrigin(); }
    float shadowStrength() const override { return _shadowStrength; }
    float shadowRadius() const override { return _shadowLight->radius(); }

    // END Shadows

    // Collision detection and object picking

    bool testElevation(const glm::vec2 &position, Collision &outCollision) const override;
    bool testLineOfSight(const glm::vec3 &origin, const glm::vec3 &dest, Collision &outCollision) const override;
    bool testWalk(const glm::vec3 &origin, const glm::vec3 &dest, const IUser *excludeUser, Collision &outCollision) const override;

    ModelSceneNode *pickModelAt(int x, int y, IUser *except = nullptr) const override;

    void setWalkableSurfaces(std::set<uint32_t> surfaces) override { _walkableSurfaces = std::move(surfaces); }
    void setWalkcheckSurfaces(std::set<uint32_t> surfaces) override { _walkcheckSurfaces = std::move(surfaces); }
    void setLineOfSightSurfaces(std::set<uint32_t> surfaces) override { _lineOfSightSurfaces = std::move(surfaces); }

    // END Collision detection and object picking

    // Factory methods

    std::shared_ptr<CameraSceneNode> newCamera() override;
    std::shared_ptr<ModelSceneNode> newModel(graphics::Model &model, ModelUsage usage) override;
    std::shared_ptr<WalkmeshSceneNode> newWalkmesh(graphics::Walkmesh &walkmesh) override;
    std::shared_ptr<TriggerSceneNode> newTrigger(std::vector<glm::vec3> geometry) override;
    std::shared_ptr<SoundSceneNode> newSound() override;

    std::shared_ptr<DummySceneNode> newDummy(graphics::ModelNode &modelNode) override;
    std::shared_ptr<MeshSceneNode> newMesh(ModelSceneNode &model, graphics::ModelNode &modelNode) override;
    std::shared_ptr<LightSceneNode> newLight(ModelSceneNode &model, graphics::ModelNode &modelNode) override;

    std::shared_ptr<EmitterSceneNode> newEmitter(graphics::ModelNode &modelNode) override;
    std::shared_ptr<ParticleSceneNode> newParticle(EmitterSceneNode &emitter) override;

    std::shared_ptr<GrassSceneNode> newGrass(GrassProperties properties, graphics::ModelNode &aabbNode) override;
    std::shared_ptr<GrassClusterSceneNode> newGrassCluster(GrassSceneNode &grass) override;

    // END Factory methods

private:
    std::string _name;
    graphics::GraphicsOptions &_graphicsOpt;
    graphics::GraphicsServices &_graphicsSvc;
    audio::AudioServices &_audioSvc;

    bool _updateRoots {true};

    bool _drawAABB {false};
    bool _drawWalkmeshes {false};
    bool _drawTriggers {false};

    std::set<std::shared_ptr<SceneNode>> _nodes;

    CameraSceneNode *_activeCamera {nullptr};
    std::vector<LightSceneNode *> _flareLights;

    // Roots

    std::list<std::shared_ptr<ModelSceneNode>> _modelRoots;
    std::list<std::shared_ptr<WalkmeshSceneNode>> _walkmeshRoots;
    std::list<std::shared_ptr<TriggerSceneNode>> _triggerRoots;
    std::list<std::shared_ptr<GrassSceneNode>> _grassRoots;
    std::list<std::shared_ptr<SoundSceneNode>> _soundRoots;

    // END Roots

    // Leafs

    std::vector<MeshSceneNode *> _opaqueMeshes;
    std::vector<MeshSceneNode *> _transparentMeshes;
    std::vector<MeshSceneNode *> _shadowMeshes;
    std::vector<LightSceneNode *> _lights;
    std::vector<EmitterSceneNode *> _emitters;

    std::vector<std::pair<SceneNode *, std::vector<SceneNode *>>> _opaqueLeafs;
    std::vector<std::pair<SceneNode *, std::vector<SceneNode *>>> _transparentLeafs;

    // END Leafs

    // Lighting

    glm::vec3 _ambientLightColor {0.5f};

    std::vector<LightSceneNode *> _activeLights;

    // END Lighting

    // Shadows

    bool _shadowActive {false};
    float _shadowStrength {0.0f};

    LightSceneNode *_shadowLight {nullptr};

    // END Shadows

    // Fog

    FogProperties _fog;

    // END Fog

    // Surfaces

    std::set<uint32_t> _walkableSurfaces;
    std::set<uint32_t> _walkcheckSurfaces;
    std::set<uint32_t> _lineOfSightSurfaces;

    // END Surfaces

    void cullRoots();

    void refresh();
    void refreshFromNode(SceneNode &node);

    void updateLighting();
    void updateShadowLight(float dt);
    void updateFlareLights();
    void updateSounds();

    void prepareOpaqueLeafs();
    void prepareTransparentLeafs();

    std::vector<LightSceneNode *> computeClosestLights(int count, const std::function<bool(const LightSceneNode &, float)> &pred) const;

    template <class T, class... Params>
    std::shared_ptr<T> newSceneNode(Params... params) {
        auto node = std::make_shared<T>(params..., *this, _graphicsSvc, _audioSvc);
        _nodes.insert(node);
        return node;
    }
};

} // namespace scene

} // namespace reone
