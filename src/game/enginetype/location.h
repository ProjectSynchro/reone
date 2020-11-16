/*
 * Copyright (c) 2020 Vsevolod Kremianskii
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

#include "glm/vec3.hpp"

namespace reone {

namespace game {

class Location {
public:
    Location(int id, glm::vec3 position, float facing) :
        _id(id),
        _position(std::move(position)),
        _facing(facing) {
    }

    int id() const { return _id; }
    const glm::vec3 &position() const { return _position; }
    float facing() const { return _facing; }

private:
    int _id { 0 };
    glm::vec3 _position;
    float _facing;
};

} // namespace game

} // namespace reone
