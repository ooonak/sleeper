#include <tuple>

#include "gtest/gtest.h"
#include "sleeper/sleeper.hpp"

TEST(Sleeper, TestVersion)
{
  std::tuple<int, int, int> ver;
  slpr::Sleeper::version(ver);
  EXPECT_EQ(std::get<0>(ver), 0);
}
