cmake_minimum_required(VERSION 3.16)

project(sleeper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    spdlog
    URL https://github.com/gabime/spdlog/archive/refs/tags/v1.10.0.tar.gz
    URL_HASH SHA256=697f91700237dbae2326b90469be32b876b2b44888302afbc7aceb68bcfe8224
)

FetchContent_Declare(
    toml
    URL https://github.com/ToruNiina/toml11/archive/refs/tags/v3.7.1.tar.gz
    URL_HASH SHA256=afeaa9aa0416d4b6b2cd3897ca55d9317084103077b32a852247d8efd4cf6068
)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

FetchContent_MakeAvailable(googletest spdlog toml)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")
include(snippets)

enable_clang_tidy()
enable_cppcheck()
enable_iwyu()

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnull-dereference")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wunused -Wnon-virtual-dtor -Woverloaded-virtual")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast -Wcast-qual -Wcast-align -Wsign-conversion")

if (${CMAKE_BUILD_TYPE} MATCHES "^[a-zA-Z]+san" AND NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  message(FATAL_ERROR "${CMAKE_BUILD_TYPE} build type requires Clang compiler.")
else()
  set(SANITIZER_BUILD ON)
endif()

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O1")
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  # Nothing

elseif(${CMAKE_BUILD_TYPE} STREQUAL "Coverage")
    CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/CTestCustom.cmake ${CMAKE_BINARY_DIR}/CTestCustom.cmake @ONLY)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
    else()
      message(FATAL "No coverage instrumentation in your compiler, that we support!")
    endif()

elseif(${CMAKE_BUILD_TYPE} STREQUAL "Asan")
  # https://clang.llvm.org/docs/AddressSanitizer.html
  # leak detection is enabled by default on Linux.
  set(SAN_FLAGS -fsanitize=address -fsanitize=address -fno-omit-frame-pointer -fsanitize-address-use-after-scope)

elseif(${CMAKE_BUILD_TYPE} STREQUAL "Tsan")
  # https://clang.llvm.org/docs/ThreadSanitizer.html
  set(SAN_FLAGS -fsanitize=thread)

elseif(${CMAKE_BUILD_TYPE} STREQUAL "Memsan")
  # https://clang.llvm.org/docs/MemorySanitizer.html
  set(SAN_FLAGS -fsanitize=memory -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize-memory-track-origins)

elseif(${CMAKE_BUILD_TYPE} STREQUAL "Ubsan")
  # https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
  set(SAN_FLAGS -fsanitize=undefined,integer,nullability -fno-omit-frame-pointer -fsanitize-undefined-strip-path-components=2)

endif()

message(STATUS "CXX flags: ${CMAKE_CXX_FLAGS}")

add_subdirectory(src)
add_subdirectory(app)

include(CTest)
enable_testing()
add_subdirectory(test)
