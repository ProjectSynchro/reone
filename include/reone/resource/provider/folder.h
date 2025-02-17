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

#include "reone/system/types.h"

#include "../provider.h"
#include "../types.h"

namespace reone {

namespace resource {

class Folder : public IResourceProvider, boost::noncopyable {
public:
    Folder(std::filesystem::path path) :
        _path(std::move(path)) {
    }

    void init();

    // IResourceProvider

    std::optional<ByteBuffer> findResourceData(const ResourceId &id) override;

    const ResourceIdSet &resourceIds() const override { return _resourceIds; }

    // END IResourceProvider

private:
    struct Resource {
        std::filesystem::path path;
        ResourceType type;
    };

    std::filesystem::path _path;

    ResourceIdSet _resourceIds;
    std::unordered_map<ResourceId, Resource, ResourceIdHasher> _idToResource;

    void loadDirectory(const std::filesystem::path &path);
};

} // namespace resource

} // namespace reone
