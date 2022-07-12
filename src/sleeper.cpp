#include "sleeper/sleeper.hpp"

#include "sleeperconfig.hpp"

void slpr::Sleeper::version(std::tuple<int, int, int> &version)
{
  version = {sleeper_VERSION_MAJOR, sleeper_VERSION_MINOR,
             sleeper_VERSION_PATCH};
}

std::string slpr::Sleeper::version()
{
  return std::to_string(sleeper_VERSION_MAJOR) + "." +
         std::to_string(sleeper_VERSION_MINOR) + "." +
         std::to_string(sleeper_VERSION_PATCH);
}
