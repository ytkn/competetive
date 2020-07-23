#include "offset_vec.hpp"

#include "gtest/gtest.h"

TEST(offset_vec, run) {
    OffsetVec<int> v(10);
    v[-10] = 9; v[3] = 2;
    ASSERT_EQ(v[-10], 9);
    ASSERT_EQ(v[3], 2);
    v[-10] = 8;
    ASSERT_EQ(v[-10], 8);
}
