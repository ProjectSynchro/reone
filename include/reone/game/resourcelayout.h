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

namespace reone {

namespace resource {

struct ResourceServices;

}

namespace game {

struct OptionsView;

class IResourceLayout {
public:
    virtual ~IResourceLayout() = default;

    virtual std::set<std::string> moduleNames() = 0;

    virtual void loadModuleResources(const std::string &moduleName) = 0;
};

class ResourceLayout : public IResourceLayout, boost::noncopyable {
public:
    ResourceLayout(GameID gameId, OptionsView &options, resource::ResourceServices &resourceSvc) :
        _gameId(gameId),
        _options(options),
        _resourceSvc(resourceSvc) {
    }

    void init();

    std::set<std::string> moduleNames() override;

    void loadModuleResources(const std::string &moduleName) override;

private:
    GameID _gameId;
    OptionsView &_options;
    resource::ResourceServices &_resourceSvc;

    void initForKotOR();
    void initForTSL();
};

} // namespace game

} // namespace reone
