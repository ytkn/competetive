#include "int.hpp"

#include "gtest/gtest.h"

TEST(sum, sum) {
  ASSERT_EQ(1024, pow<int>(2, 10));
  ASSERT_EQ(243, pow<int>(3, 5));
}