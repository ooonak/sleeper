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

# find_package()

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
)

#target_link_libraries(sleeper
#    PRIVATE
#)

add_library(sleeper::sleeper ALIAS sleeper)

#set_target_properties(sleeper PROPERTIES PUBLIC_HEADER
#    include/sleeper/sleeper.hpp
#)

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

