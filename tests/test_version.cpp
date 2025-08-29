#include "lib.h"
#include <gtest/gtest.h>

TEST(TestVersion, IsVersionGreaterThatZero) { EXPECT_TRUE(version() > 0); }