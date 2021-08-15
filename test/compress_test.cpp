#include "compress.hpp"
#include <vector>

#include "gtest/gtest.h"

TEST(compress, idx) {
    vector<int> data = {1, 100, 2, 300, 1, 2, 500, 100000, 300};
    auto cp = Compress<int>(data);
    ASSERT_EQ(cp[1], 0);
    ASSERT_EQ(cp[2], 1);
    ASSERT_EQ(cp[100], 2);
    ASSERT_EQ(cp[100000], 5);
}
