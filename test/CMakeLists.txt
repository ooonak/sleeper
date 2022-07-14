cmake_minimum_required(VERSION 3.16)

project(sleeper LANGUAGES CXX)

add_executable(sleeperunittests sleepertests.cpp)

target_include_directories(sleeperunittests PUBLIC ${CMAKE_SOURCE_DIR}/src ${googletest_SOURCE_DIR})

target_link_libraries(sleeperunittests
  PRIVATE
  sleeper::sleeper
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(sleeperunittests)
