cmake_minimum_required(VERSION 3.10)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

project(era_tests)

find_package(CMocka REQUIRED)

set(TEST_SOURCES
	base_tests.c
	math_tests.c
	)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(era_base_tests base_tests.c)
add_executable(era_math_tests math_tests.c)

target_link_libraries(era_base_tests era_interpreter cmocka)
target_link_libraries(era_math_tests era_interpreter cmocka)

add_test(base_tests ${EXECUTABLE_OUTPUT_PATH}/era_base_tests)
add_test(math_tests ${EXECUTABLE_OUTPUT_PATH}/era_math_tests)

# add more test in similar manner
