cmake_minimum_required(VERSION 2.8)
project(ex11)
add_executable(hello hello.c)
add_executable(HanoiMsgQueueSolve ./HanoiMsgQueueSolve.c)
add_executable(HanoiMsgQueueDisplay ./HanoiMsgQueueDisplay.c)

# enable gtest
find_package(GTest)
if(GTEST_FOUND)
  include_directories(${GTEST_INCLUDE_DIRS})
  # target: *_test.cpp
  file(GLOB TEST_ALL *_test.cpp)
  add_executable(run_test ${TEST_ALL})
  target_link_libraries(run_test
    ${GTEST_BOTH_LIBRARIES}
    -pthread
    )
endif()
