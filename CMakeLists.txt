cmake_minimum_required (VERSION 3.1)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

project(era)

set (CMAKE_C_STANDART 11) # Use C11

if (CMAKE_BUILD_TYPE MATCHES Debug)
	message("===============================")
	message("Debug enabled, will build tests")
	message("===============================")

	# enable testing and add test target
	enable_testing()
	add_subdirectory(test)

endif()

include_directories(include)

# Build all files as library so that they can be re-used for tests
add_library(lib_era
		src/era_interpreter.c
		src/era_util.c
        	src/branch_operators.c
		src/math_operators.c
		src/memory_operators.c
		src/logic_operators.c
		src/file_reading.c
		)

add_executable(${PROJECT_NAME} src/main.c)
target_link_libraries(${PROJECT_NAME} lib_era)
