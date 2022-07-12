#include "gtest/gtest.h"
#include "sleeper/sleeper.hpp"

TEST(Sleeper, TestVersion) { EXPECT_FALSE(slpr::Sleeper::version().empty()); }
