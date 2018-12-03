cmake_minimum_required(VERSION 3.10)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

project(era_tests)

find_package(CMocka REQUIRED)

# Needed in case CMocka is run in config mode instead of module mode
if(${CMOCKA_FOUND})
    include_directories(${CMOCKA_INCLUDE_DIR})
endif()

set(TEST_SOURCES
	base_tests.c
	math_tests.c
	)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(era_base_tests base_tests.c)
add_executable(era_math_tests math_tests.c)

target_link_libraries(era_base_tests lib_era cmocka)
target_link_libraries(era_math_tests lib_era cmocka)

add_test(base_tests ${EXECUTABLE_OUTPUT_PATH}/era_base_tests)
add_test(math_tests ${EXECUTABLE_OUTPUT_PATH}/era_math_tests)

# add more test in similar manner
