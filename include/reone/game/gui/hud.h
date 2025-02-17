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

#include "reone/gui/control/button.h"
#include "reone/gui/control/label.h"
#include "reone/gui/control/progressbar.h"
#include "reone/gui/control/togglebutton.h"
#include "reone/resource/types.h"

#include "../gui.h"

#include "barkbubble.h"
#include "selectoverlay.h"

namespace reone {

namespace game {

class HUD : public GameGUI {
public:
    HUD(Game &game, ServicesView &services) :
        GameGUI(game, services),
        _select(game, services) {
        _resRef = guiResRef("mipc28x6");
    }

    bool handle(const SDL_Event &event) override;
    void update(float dt) override;
    void draw() override;

    BarkBubble &barkBubble() const { return *_barkBubble; }

private:
    struct Controls {
        std::shared_ptr<gui::Button> BTN_ABI;
        std::shared_ptr<gui::Button> BTN_ACTION0;
        std::shared_ptr<gui::Button> BTN_ACTION1;
        std::shared_ptr<gui::Button> BTN_ACTION2;
        std::shared_ptr<gui::Button> BTN_ACTION3;
        std::shared_ptr<gui::Button> BTN_ACTION4;
        std::shared_ptr<gui::Button> BTN_ACTION5;
        std::shared_ptr<gui::Button> BTN_ACTIONDOWN0;
        std::shared_ptr<gui::Button> BTN_ACTIONDOWN1;
        std::shared_ptr<gui::Button> BTN_ACTIONDOWN2;
        std::shared_ptr<gui::Button> BTN_ACTIONDOWN3;
        std::shared_ptr<gui::Button> BTN_ACTIONDOWN4;
        std::shared_ptr<gui::Button> BTN_ACTIONDOWN5;
        std::shared_ptr<gui::Button> BTN_ACTIONUP0;
        std::shared_ptr<gui::Button> BTN_ACTIONUP1;
        std::shared_ptr<gui::Button> BTN_ACTIONUP2;
        std::shared_ptr<gui::Button> BTN_ACTIONUP3;
        std::shared_ptr<gui::Button> BTN_ACTIONUP4;
        std::shared_ptr<gui::Button> BTN_ACTIONUP5;
        std::shared_ptr<gui::Button> BTN_CHAR;
        std::shared_ptr<gui::Button> BTN_CHAR1;
        std::shared_ptr<gui::Button> BTN_CHAR2;
        std::shared_ptr<gui::Button> BTN_CHAR3;
        std::shared_ptr<gui::Button> BTN_CLEARALL;
        std::shared_ptr<gui::Button> BTN_CLEARONE;
        std::shared_ptr<gui::Button> BTN_CLEARONE2;
        std::shared_ptr<gui::Button> BTN_EQU;
        std::shared_ptr<gui::Button> BTN_INV;
        std::shared_ptr<gui::Button> BTN_JOU;
        std::shared_ptr<gui::Button> BTN_MAP;
        std::shared_ptr<gui::Button> BTN_MINIMAP;
        std::shared_ptr<gui::Button> BTN_MSG;
        std::shared_ptr<gui::Button> BTN_OPT;
        std::shared_ptr<gui::ToggleButton> BTN_SWAPWEAPONS;
        std::shared_ptr<gui::Button> BTN_TARGET0;
        std::shared_ptr<gui::Button> BTN_TARGET1;
        std::shared_ptr<gui::Button> BTN_TARGET2;
        std::shared_ptr<gui::Button> BTN_TARGETDOWN0;
        std::shared_ptr<gui::Button> BTN_TARGETDOWN1;
        std::shared_ptr<gui::Button> BTN_TARGETDOWN2;
        std::shared_ptr<gui::Button> BTN_TARGETUP0;
        std::shared_ptr<gui::Button> BTN_TARGETUP1;
        std::shared_ptr<gui::Button> BTN_TARGETUP2;
        std::shared_ptr<gui::Button> LBL_ACTION0;
        std::shared_ptr<gui::Button> LBL_ACTION1;
        std::shared_ptr<gui::Button> LBL_ACTION2;
        std::shared_ptr<gui::Button> LBL_ACTION3;
        std::shared_ptr<gui::Button> LBL_ACTION4;
        std::shared_ptr<gui::Button> LBL_ACTION5;
        std::shared_ptr<gui::Label> LBL_ACTIONDESC;
        std::shared_ptr<gui::Label> LBL_ACTIONDESCBG;
        std::shared_ptr<gui::Label> LBL_ARROW;
        std::shared_ptr<gui::Label> LBL_ARROW_MARGIN;
        std::shared_ptr<gui::Label> LBL_BACK1;
        std::shared_ptr<gui::Label> LBL_BACK2;
        std::shared_ptr<gui::Label> LBL_BACK3;
        std::shared_ptr<gui::Label> LBL_CASH;
        std::shared_ptr<gui::Label> LBL_CHAR1;
        std::shared_ptr<gui::Label> LBL_CHAR2;
        std::shared_ptr<gui::Label> LBL_CHAR3;
        std::shared_ptr<gui::Label> LBL_CMBTEFCTINC1;
        std::shared_ptr<gui::Label> LBL_CMBTEFCTINC2;
        std::shared_ptr<gui::Label> LBL_CMBTEFCTINC3;
        std::shared_ptr<gui::Label> LBL_CMBTEFCTRED1;
        std::shared_ptr<gui::Label> LBL_CMBTEFCTRED2;
        std::shared_ptr<gui::Label> LBL_CMBTEFCTRED3;
        std::shared_ptr<gui::Label> LBL_CMBTMODEMSG;
        std::shared_ptr<gui::Label> LBL_CMBTMSGBG;
        std::shared_ptr<gui::Label> LBL_COMBATBG1;
        std::shared_ptr<gui::Label> LBL_COMBATBG2;
        std::shared_ptr<gui::Label> LBL_COMBATBG3;
        std::shared_ptr<gui::Label> LBL_DARKSHIFT;
        std::shared_ptr<gui::Label> LBL_DEBILATATED1;
        std::shared_ptr<gui::Label> LBL_DEBILATATED2;
        std::shared_ptr<gui::Label> LBL_DEBILATATED3;
        std::shared_ptr<gui::Label> LBL_DISABLE1;
        std::shared_ptr<gui::Label> LBL_DISABLE2;
        std::shared_ptr<gui::Label> LBL_DISABLE3;
        std::shared_ptr<gui::Label> LBL_HEALTHBG;
        std::shared_ptr<gui::Label> LBL_ITEMLOST;
        std::shared_ptr<gui::Label> LBL_ITEMRCVD;
        std::shared_ptr<gui::Label> LBL_JOURNAL;
        std::shared_ptr<gui::Label> LBL_LEVELUP1;
        std::shared_ptr<gui::Label> LBL_LEVELUP2;
        std::shared_ptr<gui::Label> LBL_LEVELUP3;
        std::shared_ptr<gui::Label> LBL_LIGHTSHIFT;
        std::shared_ptr<gui::Label> LBL_LVLUPBG1;
        std::shared_ptr<gui::Label> LBL_LVLUPBG2;
        std::shared_ptr<gui::Label> LBL_LVLUPBG3;
        std::shared_ptr<gui::Label> LBL_MAP;
        std::shared_ptr<gui::Label> LBL_MAPBORDER;
        std::shared_ptr<gui::Label> LBL_MAPVIEW;
        std::shared_ptr<gui::Label> LBL_MENUBG;
        std::shared_ptr<gui::Label> LBL_MOULDING1;
        std::shared_ptr<gui::Label> LBL_MOULDING2;
        std::shared_ptr<gui::Label> LBL_MOULDING3;
        std::shared_ptr<gui::Label> LBL_NAME;
        std::shared_ptr<gui::Label> LBL_NAMEBG;
        std::shared_ptr<gui::Label> LBL_PLOTXP;
        std::shared_ptr<gui::Label> LBL_QUEUE0;
        std::shared_ptr<gui::Label> LBL_QUEUE1;
        std::shared_ptr<gui::Label> LBL_QUEUE2;
        std::shared_ptr<gui::Label> LBL_QUEUE3;
        std::shared_ptr<gui::Label> LBL_STEALTHXP;
        std::shared_ptr<gui::Button> LBL_TARGET0;
        std::shared_ptr<gui::Button> LBL_TARGET1;
        std::shared_ptr<gui::Button> LBL_TARGET2;
        std::shared_ptr<gui::ProgressBar> PB_FORCE1;
        std::shared_ptr<gui::ProgressBar> PB_FORCE2;
        std::shared_ptr<gui::ProgressBar> PB_FORCE3;
        std::shared_ptr<gui::ProgressBar> PB_HEALTH;
        std::shared_ptr<gui::ProgressBar> PB_VIT1;
        std::shared_ptr<gui::ProgressBar> PB_VIT2;
        std::shared_ptr<gui::ProgressBar> PB_VIT3;
        std::shared_ptr<gui::ToggleButton> TB_PAUSE;
        std::shared_ptr<gui::ToggleButton> TB_SOLO;
        std::shared_ptr<gui::ToggleButton> TB_STEALTH;
    };

    Controls _controls;

    SelectionOverlay _select;
    std::unique_ptr<BarkBubble> _barkBubble;

    void preload(gui::IGUI &gui) override;
    void onGUILoaded() override;

    void bindControls() {
        _controls.BTN_ABI = findControl<gui::Button>("BTN_ABI");
        _controls.BTN_ACTION0 = findControl<gui::Button>("BTN_ACTION0");
        _controls.BTN_ACTION1 = findControl<gui::Button>("BTN_ACTION1");
        _controls.BTN_ACTION2 = findControl<gui::Button>("BTN_ACTION2");
        _controls.BTN_ACTION3 = findControl<gui::Button>("BTN_ACTION3");
        _controls.BTN_ACTION4 = findControl<gui::Button>("BTN_ACTION4");
        _controls.BTN_ACTION5 = findControl<gui::Button>("BTN_ACTION5");
        _controls.BTN_ACTIONDOWN0 = findControl<gui::Button>("BTN_ACTIONDOWN0");
        _controls.BTN_ACTIONDOWN1 = findControl<gui::Button>("BTN_ACTIONDOWN1");
        _controls.BTN_ACTIONDOWN2 = findControl<gui::Button>("BTN_ACTIONDOWN2");
        _controls.BTN_ACTIONDOWN3 = findControl<gui::Button>("BTN_ACTIONDOWN3");
        _controls.BTN_ACTIONDOWN4 = findControl<gui::Button>("BTN_ACTIONDOWN4");
        _controls.BTN_ACTIONDOWN5 = findControl<gui::Button>("BTN_ACTIONDOWN5");
        _controls.BTN_ACTIONUP0 = findControl<gui::Button>("BTN_ACTIONUP0");
        _controls.BTN_ACTIONUP1 = findControl<gui::Button>("BTN_ACTIONUP1");
        _controls.BTN_ACTIONUP2 = findControl<gui::Button>("BTN_ACTIONUP2");
        _controls.BTN_ACTIONUP3 = findControl<gui::Button>("BTN_ACTIONUP3");
        _controls.BTN_ACTIONUP4 = findControl<gui::Button>("BTN_ACTIONUP4");
        _controls.BTN_ACTIONUP5 = findControl<gui::Button>("BTN_ACTIONUP5");
        _controls.BTN_CHAR = findControl<gui::Button>("BTN_CHAR");
        _controls.BTN_CHAR1 = findControl<gui::Button>("BTN_CHAR1");
        _controls.BTN_CHAR2 = findControl<gui::Button>("BTN_CHAR2");
        _controls.BTN_CHAR3 = findControl<gui::Button>("BTN_CHAR3");
        _controls.BTN_CLEARALL = findControl<gui::Button>("BTN_CLEARALL");
        _controls.BTN_CLEARONE = findControl<gui::Button>("BTN_CLEARONE");
        _controls.BTN_CLEARONE2 = findControl<gui::Button>("BTN_CLEARONE2");
        _controls.BTN_EQU = findControl<gui::Button>("BTN_EQU");
        _controls.BTN_INV = findControl<gui::Button>("BTN_INV");
        _controls.BTN_JOU = findControl<gui::Button>("BTN_JOU");
        _controls.BTN_MAP = findControl<gui::Button>("BTN_MAP");
        _controls.BTN_MINIMAP = findControl<gui::Button>("BTN_MINIMAP");
        _controls.BTN_MSG = findControl<gui::Button>("BTN_MSG");
        _controls.BTN_OPT = findControl<gui::Button>("BTN_OPT");
        _controls.BTN_SWAPWEAPONS = findControl<gui::ToggleButton>("BTN_SWAPWEAPONS");
        _controls.BTN_TARGET0 = findControl<gui::Button>("BTN_TARGET0");
        _controls.BTN_TARGET1 = findControl<gui::Button>("BTN_TARGET1");
        _controls.BTN_TARGET2 = findControl<gui::Button>("BTN_TARGET2");
        _controls.BTN_TARGETDOWN0 = findControl<gui::Button>("BTN_TARGETDOWN0");
        _controls.BTN_TARGETDOWN1 = findControl<gui::Button>("BTN_TARGETDOWN1");
        _controls.BTN_TARGETDOWN2 = findControl<gui::Button>("BTN_TARGETDOWN2");
        _controls.BTN_TARGETUP0 = findControl<gui::Button>("BTN_TARGETUP0");
        _controls.BTN_TARGETUP1 = findControl<gui::Button>("BTN_TARGETUP1");
        _controls.BTN_TARGETUP2 = findControl<gui::Button>("BTN_TARGETUP2");
        _controls.LBL_ACTION0 = findControl<gui::Button>("LBL_ACTION0");
        _controls.LBL_ACTION1 = findControl<gui::Button>("LBL_ACTION1");
        _controls.LBL_ACTION2 = findControl<gui::Button>("LBL_ACTION2");
        _controls.LBL_ACTION3 = findControl<gui::Button>("LBL_ACTION3");
        _controls.LBL_ACTION4 = findControl<gui::Button>("LBL_ACTION4");
        _controls.LBL_ACTION5 = findControl<gui::Button>("LBL_ACTION5");
        _controls.LBL_ACTIONDESC = findControl<gui::Label>("LBL_ACTIONDESC");
        _controls.LBL_ACTIONDESCBG = findControl<gui::Label>("LBL_ACTIONDESCBG");
        _controls.LBL_ARROW = findControl<gui::Label>("LBL_ARROW");
        _controls.LBL_ARROW_MARGIN = findControl<gui::Label>("LBL_ARROW_MARGIN");
        _controls.LBL_BACK1 = findControl<gui::Label>("LBL_BACK1");
        _controls.LBL_BACK2 = findControl<gui::Label>("LBL_BACK2");
        _controls.LBL_BACK3 = findControl<gui::Label>("LBL_BACK3");
        _controls.LBL_CASH = findControl<gui::Label>("LBL_CASH");
        _controls.LBL_CHAR1 = findControl<gui::Label>("LBL_CHAR1");
        _controls.LBL_CHAR2 = findControl<gui::Label>("LBL_CHAR2");
        _controls.LBL_CHAR3 = findControl<gui::Label>("LBL_CHAR3");
        _controls.LBL_CMBTEFCTINC1 = findControl<gui::Label>("LBL_CMBTEFCTINC1");
        _controls.LBL_CMBTEFCTINC2 = findControl<gui::Label>("LBL_CMBTEFCTINC2");
        _controls.LBL_CMBTEFCTINC3 = findControl<gui::Label>("LBL_CMBTEFCTINC3");
        _controls.LBL_CMBTEFCTRED1 = findControl<gui::Label>("LBL_CMBTEFCTRED1");
        _controls.LBL_CMBTEFCTRED2 = findControl<gui::Label>("LBL_CMBTEFCTRED2");
        _controls.LBL_CMBTEFCTRED3 = findControl<gui::Label>("LBL_CMBTEFCTRED3");
        _controls.LBL_CMBTMODEMSG = findControl<gui::Label>("LBL_CMBTMODEMSG");
        _controls.LBL_CMBTMSGBG = findControl<gui::Label>("LBL_CMBTMSGBG");
        _controls.LBL_COMBATBG1 = findControl<gui::Label>("LBL_COMBATBG1");
        _controls.LBL_COMBATBG2 = findControl<gui::Label>("LBL_COMBATBG2");
        _controls.LBL_COMBATBG3 = findControl<gui::Label>("LBL_COMBATBG3");
        _controls.LBL_DARKSHIFT = findControl<gui::Label>("LBL_DARKSHIFT");
        _controls.LBL_DEBILATATED1 = findControl<gui::Label>("LBL_DEBILATATED1");
        _controls.LBL_DEBILATATED2 = findControl<gui::Label>("LBL_DEBILATATED2");
        _controls.LBL_DEBILATATED3 = findControl<gui::Label>("LBL_DEBILATATED3");
        _controls.LBL_DISABLE1 = findControl<gui::Label>("LBL_DISABLE1");
        _controls.LBL_DISABLE2 = findControl<gui::Label>("LBL_DISABLE2");
        _controls.LBL_DISABLE3 = findControl<gui::Label>("LBL_DISABLE3");
        _controls.LBL_HEALTHBG = findControl<gui::Label>("LBL_HEALTHBG");
        _controls.LBL_ITEMLOST = findControl<gui::Label>("LBL_ITEMLOST");
        _controls.LBL_ITEMRCVD = findControl<gui::Label>("LBL_ITEMRCVD");
        _controls.LBL_JOURNAL = findControl<gui::Label>("LBL_JOURNAL");
        _controls.LBL_LEVELUP1 = findControl<gui::Label>("LBL_LEVELUP1");
        _controls.LBL_LEVELUP2 = findControl<gui::Label>("LBL_LEVELUP2");
        _controls.LBL_LEVELUP3 = findControl<gui::Label>("LBL_LEVELUP3");
        _controls.LBL_LIGHTSHIFT = findControl<gui::Label>("LBL_LIGHTSHIFT");
        _controls.LBL_LVLUPBG1 = findControl<gui::Label>("LBL_LVLUPBG1");
        _controls.LBL_LVLUPBG2 = findControl<gui::Label>("LBL_LVLUPBG2");
        _controls.LBL_LVLUPBG3 = findControl<gui::Label>("LBL_LVLUPBG3");
        _controls.LBL_MAP = findControl<gui::Label>("LBL_MAP");
        _controls.LBL_MAPBORDER = findControl<gui::Label>("LBL_MAPBORDER");
        _controls.LBL_MAPVIEW = findControl<gui::Label>("LBL_MAPVIEW");
        _controls.LBL_MENUBG = findControl<gui::Label>("LBL_MENUBG");
        _controls.LBL_MOULDING1 = findControl<gui::Label>("LBL_MOULDING1");
        _controls.LBL_MOULDING2 = findControl<gui::Label>("LBL_MOULDING2");
        _controls.LBL_MOULDING3 = findControl<gui::Label>("LBL_MOULDING3");
        _controls.LBL_NAME = findControl<gui::Label>("LBL_NAME");
        _controls.LBL_NAMEBG = findControl<gui::Label>("LBL_NAMEBG");
        _controls.LBL_PLOTXP = findControl<gui::Label>("LBL_PLOTXP");
        _controls.LBL_QUEUE0 = findControl<gui::Label>("LBL_QUEUE0");
        _controls.LBL_QUEUE1 = findControl<gui::Label>("LBL_QUEUE1");
        _controls.LBL_QUEUE2 = findControl<gui::Label>("LBL_QUEUE2");
        _controls.LBL_QUEUE3 = findControl<gui::Label>("LBL_QUEUE3");
        _controls.LBL_STEALTHXP = findControl<gui::Label>("LBL_STEALTHXP");
        _controls.LBL_TARGET0 = findControl<gui::Button>("LBL_TARGET0");
        _controls.LBL_TARGET1 = findControl<gui::Button>("LBL_TARGET1");
        _controls.LBL_TARGET2 = findControl<gui::Button>("LBL_TARGET2");
        _controls.PB_FORCE1 = findControl<gui::ProgressBar>("PB_FORCE1");
        _controls.PB_FORCE2 = findControl<gui::ProgressBar>("PB_FORCE2");
        _controls.PB_FORCE3 = findControl<gui::ProgressBar>("PB_FORCE3");
        _controls.PB_HEALTH = findControl<gui::ProgressBar>("PB_HEALTH");
        _controls.PB_VIT1 = findControl<gui::ProgressBar>("PB_VIT1");
        _controls.PB_VIT2 = findControl<gui::ProgressBar>("PB_VIT2");
        _controls.PB_VIT3 = findControl<gui::ProgressBar>("PB_VIT3");
        _controls.TB_PAUSE = findControl<gui::ToggleButton>("TB_PAUSE");
        _controls.TB_SOLO = findControl<gui::ToggleButton>("TB_SOLO");
        _controls.TB_STEALTH = findControl<gui::ToggleButton>("TB_STEALTH");
    }

    void toggleCombat(bool enabled);
    void refreshActionQueueItems() const;

    void drawHealth(int memberIndex);
    void drawMinimap();
};

} // namespace game

} // namespace reone
