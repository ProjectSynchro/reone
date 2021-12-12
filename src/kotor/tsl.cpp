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

#include "tsl.h"

#include "../common/pathutil.h"
#include "../game/services.h"
#include "../resource/2da.h"
#include "../resource/resources.h"

#include "gui/console.h"
#include "gui/loadscreen.h"
#include "gui/map.h"
#include "gui/profileoverlay.h"
#include "script/routines.h"

using namespace std;

using namespace reone::audio;
using namespace reone::game;
using namespace reone::graphics;
using namespace reone::resource;
using namespace reone::scene;
using namespace reone::script;

namespace fs = boost::filesystem;

namespace reone {

namespace kotor {

static constexpr char kVoiceDirectoryName[] = "streamvoice";
static constexpr char kLocalizationLipFilename[] = "localization";
static constexpr char kExeFilename[] = "swkotor2.exe";

static constexpr char kBlueprintResRefAtton[] = "p_atton";
static constexpr char kBlueprintResRefKreia[] = "p_kreia";

void TSL::initResourceProviders() {
    _services.resources.indexKeyFile(getPathIgnoreCase(_path, kKeyFilename));

    fs::path texPacksPath(getPathIgnoreCase(_path, kTexturePackDirectoryName));
    _services.resources.indexErfFile(getPathIgnoreCase(texPacksPath, kGUITexturePackFilename));
    _services.resources.indexErfFile(getPathIgnoreCase(texPacksPath, kTexturePackFilename));

    _services.resources.indexDirectory(getPathIgnoreCase(_path, kMusicDirectoryName));
    _services.resources.indexDirectory(getPathIgnoreCase(_path, kSoundsDirectoryName));
    _services.resources.indexDirectory(getPathIgnoreCase(_path, kVoiceDirectoryName));

    fs::path lipsPath(getPathIgnoreCase(_path, kLipsDirectoryName));
    _services.resources.indexErfFile(getPathIgnoreCase(lipsPath, kLocalizationLipFilename));

    _services.resources.indexDirectory(getPathIgnoreCase(_path, kOverrideDirectoryName));
    _services.resources.indexExeFile(getPathIgnoreCase(_path, kExeFilename));
}

void TSL::init() {
    Game::init();

    auto routines = make_unique<Routines>(*this, _services);
    routines->initForTSL();

    _routines = move(routines);
    _scriptRunner = make_unique<ScriptRunner>(*_routines, _services.scripts);

    _mainMenuMusicResRef = "mus_sion";
    _charGenMusicResRef = "mus_main";
    _charGenLoadScreenResRef = "load_default";

    _guiColorBase = glm::vec3(0.192157f, 0.768627f, 0.647059f);
    _guiColorHilight = glm::vec3(0.768627f, 0.768627f, 0.686275f);
    _guiColorDisabled = glm::vec3(0.513725f, 0.513725f, 0.415686f);

    auto map = make_unique<Map>(*this, _services);
    map->setArrowResRef("mm_barrow_p");
    _map = move(map);

    auto console = make_unique<Console>(*this, _services);
    console->init();
    _console = move(console);

    auto profileOverlay = make_unique<ProfileOverlay>(_services);
    profileOverlay->init();
    _profileOverlay = move(profileOverlay);
}

void TSL::getDefaultPartyMembers(string &member1, string &member2, string &member3) const {
    member1 = kBlueprintResRefAtton;
    member2 = kBlueprintResRefKreia;
    member3.clear();
}

} // namespace kotor

} // namespace reone
