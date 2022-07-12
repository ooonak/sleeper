#pragma once

#include <string>
#include <tuple>

namespace slpr
{

class Sleeper
{
 public:
  static void version(std::tuple<int, int, int> &version);

  static void version();
};

}  // namespace slpr
