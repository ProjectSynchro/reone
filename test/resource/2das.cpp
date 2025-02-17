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

#include <gtest/gtest.h>

#include "reone/resource/2da.h"
#include "reone/resource/2das.h"
#include "reone/resource/provider/memory.h"
#include "reone/resource/resources.h"
#include "reone/system/stream/memoryoutput.h"

using namespace reone;
using namespace reone::resource;

TEST(two_das, should_get_2da_with_caching) {
    // given

    auto resBytes = ByteBuffer();
    auto res = MemoryOutputStream(resBytes);
    res.write("2DA V2.b\n", 9);
    res.write("label\t\0", 7);
    res.write("\x00\x00\x00\x00", 4);
    res.write("\x00\x00\x00\x00", 4);

    auto resources = Resources();
    auto provider = std::make_unique<MemoryResourceProvider>();
    provider->add(ResourceId("sample", ResourceType::TwoDa), std::move(resBytes));
    resources.add(std::move(provider));

    auto twoDas = TwoDas(resources);

    // when

    auto twoDa1 = twoDas.get("sample");

    resources.clear();

    auto twoDa2 = twoDas.get("sample");

    // then

    EXPECT_TRUE(static_cast<bool>(twoDa1));
    EXPECT_TRUE(static_cast<bool>(twoDa2));
    EXPECT_EQ(twoDa1.get(), twoDa2.get());
}
