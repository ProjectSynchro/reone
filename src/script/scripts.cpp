/*
 * Copyright (c) 2020-2021 The reone project contributors
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

#include "scripts.h"

#include "../common/streamutil.h"
#include "../resource/resources.h"

#include "ncsreader.h"

using namespace std;
using namespace std::placeholders;

using namespace reone::resource;

namespace reone {

namespace script {

Scripts &Scripts::instance() {
    static Scripts instance;
    return instance;
}

Scripts::Scripts() : MemoryCache(bind(&Scripts::doGet, this, _1)) {
}

shared_ptr<ScriptProgram> Scripts::doGet(string resRef) {
    shared_ptr<ByteArray> data(Resources::instance().get(resRef, ResourceType::Ncs));
    if (!data) return nullptr;

    NcsReader ncs(resRef);
    ncs.load(wrap(data));

    return ncs.program();
}

} // namespace script

} // namespace reone
