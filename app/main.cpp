#include <iostream>

#include "sleeper/sleeper.hpp"

int main()
{
  std::cout << "libsleeper v" << slpr::Sleeper::version() << std::endl;

  return 0;
}
