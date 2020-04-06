#include "mod.hpp"
#include <vector>

#include "gtest/gtest.h"

TEST(mod, calc) {
    init();
    ASSERT_EQ((2*inv[2])%MOD, 1);
    ASSERT_EQ(comb(5, 2), 10);
}
