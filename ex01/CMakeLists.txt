cmake_minimum_required(VERSION 2.8)
project(ex01)
add_executable(hanoi hanoi.c)
add_executable(hanoi_static_array hanoi_static_array.c)

# enable gtest
find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})
# target: test_*.cpp
file(GLOB TEST_ALL test_*.cpp)
if(NOT "${TEST_ALL}" STREQUAL "")
  add_executable(run_test ${TEST_ALL})
  target_link_libraries(run_test
    ${GTEST_BOTH_LIBRARIES}
    -pthread
    )
endif()
