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

#include <cstdint>

namespace reone {

/** Reseeds the shared generator, for deterministic scripted runs. */
void setRandomSeed(uint32_t seed);

/**
 * A random number from a stream kept for the renderer, apart from the shared
 * one. Renderer noise such as the SSAO kernel, which only the PBR pipeline
 * builds, leaves the shared stream where it was for particles and grass.
 *
 * @param min lower bound (inclusive)
 * @param max upper bound (exclusive)
 */
float renderRandomFloat(float min, float max);

/**
 * @param min lower bound (inclusive)
 * @param max upper bound (inclusive)
 */
int randomInt(int min, int max);

/**
 * @param min lower bound (inclusive)
 * @param max upper bound (inclusive)
 */
float randomFloat(float min, float max);

} // namespace reone
