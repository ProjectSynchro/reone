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

#include "reone/resource/di/module.h"

#include "../scripts.h"

#include "services.h"

namespace reone {

namespace script {

class ScriptModule : boost::noncopyable {
public:
    ScriptModule(resource::ResourceModule &resource) :
        _resource(resource) {
    }

    ~ScriptModule() { deinit(); }

    void init();
    void deinit();

    Scripts &scripts() { return *_scripts; }

    ScriptServices &services() { return *_services; }

private:
    resource::ResourceModule &_resource;

    std::unique_ptr<Scripts> _scripts;

    std::unique_ptr<ScriptServices> _services;
};

} // namespace script

} // namespace reone
