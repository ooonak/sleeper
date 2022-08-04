#include "sleeper/sleeper.hpp"

#include <sodium.h>
#include "nlohmann/json.hpp"
#include "sleeperconfig.hpp"
#include "spdlog/spdlog.h"
#include "toml.hpp"
#include <boost/asio.hpp>
#include <openssl/opensslv.h>

void slpr::Sleeper::version(std::tuple<int, int, int> &version)
{
  version = {sleeper_VERSION_MAJOR, sleeper_VERSION_MINOR,
             sleeper_VERSION_PATCH};
}

void slpr::Sleeper::version()
{
  spdlog::info("libSleeper v{}.{}.{} uses the following libraries:",
               sleeper_VERSION_MAJOR, sleeper_VERSION_MINOR, sleeper_VERSION_PATCH);
  spdlog::info("spdlog {}.{}.{} [MIT License, header only] {}",
               SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH,
               "https://github.com/gabime/spdlog");
  spdlog::info("toml11 {}.{}.{} [MIT License, header only] {}",
               TOML11_VERSION_MAJOR, TOML11_VERSION_MINOR, TOML11_VERSION_PATCH,
               "https://github.com/ToruNiina/toml11");
  spdlog::info("libsodium {} [ISC license, dynamically linked] {}",
               sodium_version_string(),
               "https://github.com/jedisct1/libsodium");
  spdlog::info("Boost (v{}.{}.{}) Asio v{}.{}.{}", BOOST_VERSION / 100000, BOOST_VERSION / 100 % 1000, BOOST_VERSION % 100, BOOST_ASIO_VERSION / 100000, BOOST_ASIO_VERSION / 100 % 1000, BOOST_ASIO_VERSION % 100); // NOLINT
  spdlog::info("nlohmann json v{}.{}.{}", NLOHMANN_JSON_VERSION_MAJOR, NLOHMANN_JSON_VERSION_MINOR, NLOHMANN_JSON_VERSION_PATCH);
  spdlog::info(OPENSSL_VERSION_TEXT);
}
