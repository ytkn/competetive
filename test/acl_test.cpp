#include <atcoder/modint>

#include "gtest/gtest.h"

using mint = atcoder::modint998244353;

TEST(acl, simple) {
    ASSERT_EQ((mint(2)/mint(2)).val(), 1);
}