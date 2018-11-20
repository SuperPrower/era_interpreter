cmake_minimum_required(VERSION 3.10)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

project(era_tests)

find_package(CMocka REQUIRED)

set(TEST_SOURCES tests.c)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(era_tests ${TEST_SOURCES})
target_link_libraries(era_tests lib_era cmocka)

# add_dependencies(era_tests era_tests)
add_test(sample_test ${EXECUTABLE_OUTPUT_PATH}/era_tests)
