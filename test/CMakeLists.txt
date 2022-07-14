add_executable(sleeperunittests sleepertests.cpp)

target_include_directories(sleeperunittests PUBLIC ${CMAKE_SOURCE_DIR}/src ${googletest_SOURCE_DIR})

target_link_libraries(sleeperunittests
  PRIVATE
  sleeper::sleeper
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(sleeperunittests)

