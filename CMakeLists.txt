cmake_minimum_required(VERSION 3.16)

project(sleeper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")
include(snippets)
enable_cppcheck()
enable_iwyu()

include(FetchContent)

# MIT License
FetchContent_Declare(
    spdlog
    URL https://github.com/gabime/spdlog/archive/refs/tags/v1.10.0.tar.gz
    URL_HASH SHA256=697f91700237dbae2326b90469be32b876b2b44888302afbc7aceb68bcfe8224
)

# MIT License
FetchContent_Declare(
    toml
    URL https://github.com/ToruNiina/toml11/archive/refs/tags/v3.7.1.tar.gz
    URL_HASH SHA256=afeaa9aa0416d4b6b2cd3897ca55d9317084103077b32a852247d8efd4cf6068
)

FetchContent_MakeAvailable(spdlog toml)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O1")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnull-dereference")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wunused -Wnon-virtual-dtor -Woverloaded-virtual")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast -Wcast-qual -Wcast-align -Wsign-conversion")

message(STATUS "Using CXX flags: ${CMAKE_CXX_FLAGS}")

add_subdirectory(src)
add_subdirectory(app)

include(CTest)
enable_testing()
add_subdirectory(test)

