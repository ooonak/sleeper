#include <tuple>

#include "gtest/gtest.h"
#include "sleeper/sleeper.hpp"

TEST(Sleeper, TestVersion)
{
  std::tuple<int, int, int> v;
  slpr::Sleeper::version(v);
  EXPECT_EQ(std::get<0>(v), 0);
}
