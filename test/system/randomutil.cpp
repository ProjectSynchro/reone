/*
 * Copyright (c) 2026 The reone project contributors
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

#include "reone/system/randomutil.h"

using namespace reone;

TEST(RandomUtil, the_render_stream_leaves_the_shared_one_where_it_was) {
    setRandomSeed(1);
    const float expected = randomFloat(0.0f, 1.0f);

    setRandomSeed(1);
    renderRandomFloat(0.0f, 1.0f);
    renderRandomFloat(0.0f, 1.0f);

    EXPECT_EQ(randomFloat(0.0f, 1.0f), expected);
}
