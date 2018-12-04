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
	logic_tests.c
	file_reading_tests.c
	)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(era_base_tests base_tests.c)
add_executable(era_math_tests math_tests.c)
add_executable(era_logic_tests logic_tests.c)
add_executable(era_file_reading_tests file_reading_tests.c)

target_link_libraries(era_base_tests era_interpreter cmocka)
target_link_libraries(era_math_tests era_interpreter cmocka)
target_link_libraries(era_logic_tests era_interpreter cmocka)
target_link_libraries(era_file_reading_tests era_interpreter cmocka)

add_test(NAME base_tests COMMAND ${EXECUTABLE_OUTPUT_PATH}/era_base_tests WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test")
add_test(NAME math_tests COMMAND ${EXECUTABLE_OUTPUT_PATH}/era_math_tests WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test")
add_test(NAME logic_tests COMMAND ${EXECUTABLE_OUTPUT_PATH}/era_logic_tests WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test")
add_test(NAME file_reading_tests COMMAND ${EXECUTABLE_OUTPUT_PATH}/era_file_reading_tests WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test")

# add more test in similar manner
