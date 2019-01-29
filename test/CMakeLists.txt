cmake_minimum_required(VERSION 3.10)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

project(erric_tests)

find_package(CMocka REQUIRED)

# Needed in case CMocka is run in config mode instead of module mode
if(${CMOCKA_FOUND})
    include_directories(${CMOCKA_INCLUDE_DIR})
endif()

set(TEST_SOURCES
	base_tests.c
	branch_tests.c
	file_reading_tests.c
	logic_tests.c
	math_tests.c
	memory_tests.c
	util_tests.c
	)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(erric_base_tests base_tests.c)
add_executable(erric_math_tests math_tests.c)
add_executable(erric_logic_tests logic_tests.c)
add_executable(erric_file_reading_tests file_reading_tests.c)
add_executable(erric_memory_tests memory_tests.c)
add_executable(erric_branch_tests branch_tests.c)
add_executable(erric_util_tests util_tests.c)

target_link_libraries(erric_base_tests erric_interpreter cmocka)
target_link_libraries(erric_math_tests erric_interpreter cmocka)
target_link_libraries(erric_logic_tests erric_interpreter cmocka)
target_link_libraries(erric_file_reading_tests erric_interpreter cmocka)
target_link_libraries(erric_memory_tests erric_interpreter cmocka)
target_link_libraries(erric_branch_tests erric_interpreter cmocka)
target_link_libraries(erric_util_tests erric_interpreter cmocka)

add_test(NAME base_tests COMMAND ${EXECUTABLE_OUTPUT_PATH}/erric_base_tests WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test")
add_test(NAME math_tests COMMAND ${EXECUTABLE_OUTPUT_PATH}/erric_math_tests WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test")
add_test(NAME logic_tests COMMAND ${EXECUTABLE_OUTPUT_PATH}/erric_logic_tests WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test")
add_test(NAME file_reading_tests COMMAND ${EXECUTABLE_OUTPUT_PATH}/erric_file_reading_tests WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test")
add_test(NAME memory_tests COMMAND ${EXECUTABLE_OUTPUT_PATH}/erric_memory_tests WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test")
add_test(NAME branch_tests COMMAND ${EXECUTABLE_OUTPUT_PATH}/erric_branch_tests WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test")
add_test(NAME util_tests COMMAND ${EXECUTABLE_OUTPUT_PATH}/erric_util_tests WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test")

# add more test in similar manner