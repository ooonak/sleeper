FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
  URL_HASH SHA256=b4870bf121ff7795ba20d20bcdd8627b8e088f2d1dab299a031c1034eddc93d5
)
FetchContent_MakeAvailable(googletest)

add_executable(sleeperunittests sleepertests.cpp)

target_include_directories(sleeperunittests PUBLIC ${CMAKE_SOURCE_DIR}/src ${googletest_SOURCE_DIR})

target_link_libraries(sleeperunittests
  PRIVATE
  sleeper::sleeper
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(sleeperunittests)

