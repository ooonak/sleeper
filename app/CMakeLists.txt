add_executable(sleeperapp main.cpp)
target_link_libraries(sleeperapp PRIVATE sleeper::sleeper)
install(TARGETS sleeperapp DESTINATION bin)

