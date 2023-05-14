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

#include <gmock/gmock.h>

#include "reone/gui/di/services.h"

namespace reone {

namespace gui {

class MockGUI : public IGUI, boost::noncopyable {
};

class MockGUIs : public IGUIs, boost::noncopyable {
public:
    MOCK_METHOD(void, invalidate, (), (override));
    MOCK_METHOD(std::shared_ptr<IGUI>, get, (const std::string &), (override));
};

class TestGUIModule : boost::noncopyable {
public:
    void init() {
        _guis = std::make_unique<MockGUIs>();
        _services = std::make_unique<GUIServices>(*_guis);
    }

    MockGUIs &guis() {
        return *_guis;
    }

    GUIServices &services() {
        return *_services;
    }

private:
    std::unique_ptr<MockGUIs> _guis;

    std::unique_ptr<GUIServices> _services;
};

} // namespace gui

} // namespace reone
