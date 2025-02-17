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

#include "types.h"
#include "uniformbuffer.h"

namespace reone {

namespace graphics {

struct UniformsFeatureFlags {
    static constexpr int lightmap = 1;
    static constexpr int envmap = 2;
    static constexpr int normalmap = 4;
    static constexpr int heightmap = 8;
    static constexpr int skeletal = 0x10;
    static constexpr int discard = 0x20;
    static constexpr int shadows = 0x40;
    static constexpr int water = 0x80;
    static constexpr int fog = 0x100;
    static constexpr int fixedsize = 0x200;
    static constexpr int hashedalphatest = 0x400;
    static constexpr int premulalpha = 0x800;
    static constexpr int envmapcube = 0x1000;
};

struct GeneralUniforms {
    glm::mat4 projection {1.0f};
    glm::mat4 screenProjection {1.0f};
    glm::mat4 view {1.0f};
    glm::mat4 viewInv {1.0f};
    glm::mat4 model {1.0f};
    glm::mat4 modelInv {1.0f};
    glm::mat3x4 uv {1.0f};
    glm::vec4 cameraPosition {0.0f};
    glm::vec4 color {1.0f};
    glm::vec4 worldAmbientColor {1.0f};
    glm::vec4 selfIllumColor {1.0f};
    glm::vec4 discardColor {0.0f};
    glm::vec4 fogColor {0.0f};
    glm::vec4 shadowLightPosition {0.0f}; /**< W = 0 if light is directional */
    glm::vec4 heightMapFrameBounds {0.0f};
    glm::vec2 screenResolution {0.0f};
    glm::vec2 screenResolutionRcp {0.0f};
    glm::vec2 blurDirection {0.0f};
    glm::ivec2 gridSize {0};
    float clipNear {kDefaultClipPlaneNear};
    float clipFar {kDefaultClipPlaneFar};
    float alpha {1.0f};
    float waterAlpha {1.0f};
    float fogNear {0.0f};
    float fogFar {0.0f};
    float heightMapScaling {1.0f};
    float shadowStrength {0.0f};
    float shadowRadius {0.0f};
    float billboardSize {1.0f};
    float ssaoSampleRadius {0.5f};
    float ssaoBias {0.1f};
    float ssrBias {0.5f};
    float ssrPixelStride {4.0f};
    float ssrMaxSteps {32.0f};
    float sharpenAmount {0.25f};
    int featureMask {0}; /**< any combination of UniformFeaturesFlags */
    float padding[3];
    glm::vec4 shadowCascadeFarPlanes {0.0f};
    glm::mat4 shadowLightSpace[kNumShadowLightSpace] {glm::mat4(1.0f)};

    void resetGlobals() {
        projection = glm::mat4(1.0f);
        view = glm::mat4(1.0f);
        viewInv = glm::mat4(1.0f);
        cameraPosition = glm::vec4(0.0f);
        worldAmbientColor = glm::vec4(1.0f);
        fogColor = glm::vec4(0.0f);
        shadowLightPosition = glm::vec4(0.0f);
        fogNear = 0.0f;
        fogFar = 0.0f;
        shadowStrength = 1.0f;
        shadowRadius = 0.0f;
        shadowCascadeFarPlanes = glm::vec4(0.0f);
        for (int i = 0; i < kNumShadowLightSpace; ++i) {
            shadowLightSpace[i] = glm::mat4(1.0f);
        }
    }

    void resetLocals() {
        screenProjection = glm::mat4(1.0f);
        model = glm::mat4(1.0f);
        modelInv = glm::mat4(1.0f);
        uv = glm::mat3x4(1.0f);
        color = glm::vec4(1.0f);
        selfIllumColor = glm::vec4(1.0f);
        discardColor = glm::vec4(0.0f);
        heightMapFrameBounds = glm::vec4(0.0f);
        screenResolution = glm::vec2(0.0f);
        screenResolutionRcp = glm::vec2(0.0f);
        blurDirection = glm::vec2(0.0f);
        gridSize = glm::ivec2(0);
        alpha = 1.0f;
        waterAlpha = 1.0f;
        heightMapScaling = 1.0f;
        billboardSize = 1.0f;
        ssaoSampleRadius = 0.5f;
        ssaoBias = 0.1f;
        ssrBias = 0.5f;
        ssrPixelStride = 4.0f;
        ssrMaxSteps = 32.0f;
        sharpenAmount = 0.25f;
        featureMask = 0;
    }
};

struct LightUniforms {
    glm::vec4 position {0.0f}; /**< W = 0 if light is directional */
    glm::vec4 color {1.0f};
    float multiplier {1.0f};
    float radius {1.0f};
    int ambientOnly {0};
    int dynamicType {0};
};

struct LightingUniforms {
    int numLights {0};
    float padding[3];
    LightUniforms lights[kMaxLights];
};

struct SkeletalUniforms {
    glm::mat4 bones[kMaxBones] {glm::mat4(1.0f)};
};

struct ParticleUniforms {
    glm::vec4 positionFrame {1.0f};
    glm::vec4 right {0.0f};
    glm::vec4 up {0.0f};
    glm::vec4 color {1.0f};
    glm::vec2 size {0.0f};
    float padding[2];
};

struct ParticlesUniforms {
    ParticleUniforms particles[kMaxParticles];
};

struct GrassClusterUniforms {
    glm::vec4 positionVariant {0.0f}; /**< fourth component is a variant (0-3) */
    glm::vec2 lightmapUV {0.0f};
    float padding[2];
};

struct GrassUniforms {
    glm::vec2 quadSize {0.0f};
    float radius {0.0f};
    float padding;
    GrassClusterUniforms clusters[kMaxGrassClusters];
};

struct TextCharacterUniforms {
    glm::vec4 posScale {0.0f};
    glm::vec4 uv {0.0f};
};

struct TextUniforms {
    TextCharacterUniforms chars[kMaxTextChars];
};

struct SSAOUniforms {
    glm::vec4 samples[kNumSSAOSamples] {glm::vec4(0.0f)};
};

struct WalkmeshUniforms {
    glm::vec4 materials[kMaxWalkmeshMaterials] {glm::vec4(1.0f)};
};

struct PointsUniforms {
    glm::vec4 points[kMaxPoints] {glm::vec4(0.0f)};
};

class IUniforms {
public:
    virtual ~IUniforms() = default;

    virtual void setGeneral(const std::function<void(GeneralUniforms &)> &block) = 0;
    virtual void setText(const std::function<void(TextUniforms &)> &block) = 0;
    virtual void setLighting(const std::function<void(LightingUniforms &)> &block) = 0;
    virtual void setSkeletal(const std::function<void(SkeletalUniforms &)> &block) = 0;
    virtual void setParticles(const std::function<void(ParticlesUniforms &)> &block) = 0;
    virtual void setGrass(const std::function<void(GrassUniforms &)> &block) = 0;
    virtual void setSSAO(const std::function<void(SSAOUniforms &)> &block) = 0;
    virtual void setWalkmesh(const std::function<void(WalkmeshUniforms &)> &block) = 0;
    virtual void setPoints(const std::function<void(PointsUniforms &)> &block) = 0;
};

class Uniforms : public IUniforms, boost::noncopyable {
public:
    ~Uniforms() { deinit(); }

    void init();
    void deinit();

    void setGeneral(const std::function<void(GeneralUniforms &)> &block) override;
    void setText(const std::function<void(TextUniforms &)> &block) override;
    void setLighting(const std::function<void(LightingUniforms &)> &block) override;
    void setSkeletal(const std::function<void(SkeletalUniforms &)> &block) override;
    void setParticles(const std::function<void(ParticlesUniforms &)> &block) override;
    void setGrass(const std::function<void(GrassUniforms &)> &block) override;
    void setSSAO(const std::function<void(SSAOUniforms &)> &block) override;
    void setWalkmesh(const std::function<void(WalkmeshUniforms &)> &block) override;
    void setPoints(const std::function<void(PointsUniforms &)> &block) override;

private:
    bool _inited {false};

    // Uniforms

    GeneralUniforms _general;
    TextUniforms _text;
    LightingUniforms _lighting;
    SkeletalUniforms _skeletal;
    ParticlesUniforms _particles;
    GrassUniforms _grass;
    SSAOUniforms _ssao;
    WalkmeshUniforms _walkmesh;
    PointsUniforms _points;

    // END Uniforms

    // Uniform Buffers

    std::shared_ptr<UniformBuffer> _ubGeneral;
    std::shared_ptr<UniformBuffer> _ubText;
    std::shared_ptr<UniformBuffer> _ubLighting;
    std::shared_ptr<UniformBuffer> _ubSkeletal;
    std::shared_ptr<UniformBuffer> _ubParticles;
    std::shared_ptr<UniformBuffer> _ubGrass;
    std::shared_ptr<UniformBuffer> _ubSSAO;
    std::shared_ptr<UniformBuffer> _ubWalkmesh;
    std::shared_ptr<UniformBuffer> _ubPoints;

    // END Uniform Buffers

    std::unique_ptr<UniformBuffer> initBuffer(const void *data, ptrdiff_t size);

    void refreshBuffer(UniformBuffer &buffer, int bindingPoint, const void *data, ptrdiff_t size);
};

} // namespace graphics

} // namespace reone
