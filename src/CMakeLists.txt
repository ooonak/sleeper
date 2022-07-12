cmake_minimum_required(VERSION 3.16)

project(sleeper VERSION 0.0.1)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")
include(snippets)
enable_clang_tidy()

file(WRITE ${PROJECT_BINARY_DIR}/sleeperconfig.hpp.in "
#pragma once

#define sleeper_VERSION_MAJOR @sleeper_VERSION_MAJOR@
#define sleeper_VERSION_MINOR @sleeper_VERSION_MINOR@
#define sleeper_VERSION_PATCH @sleeper_VERSION_PATCH@
")

# https://raw.githubusercontent.com/facebookincubator/fizz/main/build/fbcode_builder/CMake/FindSodium.cmake
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR};${CMAKE_MODULE_PATH}")
find_package(Sodium REQUIRED)

add_library(sleeper
    include/sleeper/sleeper.hpp
    sleeper.cpp
)

target_compile_features(sleeper PUBLIC cxx_std_20)

target_include_directories(sleeper
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include>
    ${spdlog_SOURCE_DIR}/include
    ${toml_SOURCE_DIR}
    ${sodium_INCLUDE_DIR}
)

target_link_libraries(sleeper
    PRIVATE
    spdlog::spdlog
    ${sodium_LIBRARY_RELEASE}
)

add_library(sleeper::sleeper ALIAS sleeper)

configure_file("${PROJECT_BINARY_DIR}/sleeperconfig.hpp.in" sleeperconfig.hpp)

install(TARGETS sleeper
        EXPORT ${CMAKE_PROJECT_NAME}Targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/sleeper
        DESTINATION include
        COMPONENT Devel
)

