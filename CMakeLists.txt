cmake_minimum_required (VERSION 3.1)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

project(era)

set (CMAKE_C_STANDART 11) # Use C11

if (CMAKE_BUILD_TYPE MATCHES Debug)
	message("===============================")
	message("Debug enabled, will build tests")
	message("===============================")

	# enable testing and add gtest target
	add_subdirectory(tests)
	enable_testing()

endif()

include_directories(include)

add_executable(${PROJECT_NAME}
	src/main.c
	src/era_interpreter.c
	)
