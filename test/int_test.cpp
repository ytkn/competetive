#include "int.hpp"
#include <vector>

#include "gtest/gtest.h"

TEST(Int, pow) {
    ASSERT_EQ(1024, pow<int>(2, 10));
    ASSERT_EQ(244, pow<int>(3, 5));
}

TEST(Int, divs) {
	vector<int> v = divs<int>(60);
	for(int d : v) ASSERT_TRUE(60%d == 0);
}