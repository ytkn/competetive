#include "int.hpp"
#include <vector>

#include "gtest/gtest.h"

TEST(Int, pow) {
    ASSERT_EQ(1024, mod_pow(2, 10, 1000000007));
    ASSERT_EQ(243, mod_pow(3, 5, 1000000007));
}

TEST(Int, divs) {
	vector<int> v = divs<int>(60);
	for(int d : v) ASSERT_TRUE(60%d == 0);
}