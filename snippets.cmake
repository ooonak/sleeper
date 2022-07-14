macro(enable_clang_tidy)
  find_program(clang_tidy_cmd NAMES "clang-tidy")
  if(NOT clang_tidy_cmd)
    message(WARNING "Could not find clang-tidy!")
  else()
    if(NOT EXISTS "${CMAKE_SOURCE_DIR}/.clang-tidy")
      message(FATAL_ERROR "Missing config file ${CMAKE_SOURCE_DIR}/.clang-tidy!")
    endif()
    set(CMAKE_CXX_CLANG_TIDY "${clang_tidy_cmd}")
  endif()
endmacro()

macro(enable_cppcheck)
  find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
  if (CMAKE_CXX_CPPCHECK)
    list(
        APPEND CMAKE_CXX_CPPCHECK
            "--enable=all"
            "--inconclusive"
            "--force"
            "--inline-suppr"
            "--enable=information"
            "--check-config"
            "--suppressions-list=${CMAKE_SOURCE_DIR}/CppCheckSuppressions.txt"
    )
  endif()
endmacro()

macro(enable_iwyu)
  find_program(iwyu_cmd NAMES "include-what-you-use")
  if(NOT iwyu_cmd)
    message(WARNING "Could not find include-what-you-use!")
  else()
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "${iwyu_cmd}")
  endif()
endmacro()

macro(enable_coverage)
  CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/CTestCustom.cmake ${CMAKE_BINARY_DIR}/CTestCustom.cmake @ONLY)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fprofile-abs-path")
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
  else()
    message(FATAL "No coverage instrumentation in your compiler, that we support!")
  endif()
endmacro()
