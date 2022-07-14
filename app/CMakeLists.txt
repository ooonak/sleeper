add_executable(sleeperapp main.cpp)

if(SANITIZER_BUILD)
  target_compile_options(sleeperapp PRIVATE ${SAN_FLAGS})
  target_link_options(sleeperapp PRIVATE ${SAN_FLAGS})
endif()

target_link_libraries(sleeperapp PRIVATE sleeper::sleeper)
install(TARGETS sleeperapp DESTINATION bin)
