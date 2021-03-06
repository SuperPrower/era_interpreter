cmake_minimum_required (VERSION 3.1)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

project(erric)

set (CMAKE_C_STANDART 11) # Use C11
option(Coverage "Enable Coverage" OFF)

if (CMAKE_BUILD_TYPE MATCHES Debug)
	message("===============================")
	message("Debug enabled, will build tests")
	message("===============================")

	# enable testing and add test target
	enable_testing()
	add_subdirectory(test)

	# if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
	if (Coverage)
		message("Will generate code coverage report")

		include(CodeCoverage)
		APPEND_COVERAGE_COMPILER_FLAGS()

		set (COVERAGE_LCOV_EXCLUDES
			"src/main.c"
		)

		SETUP_TARGET_FOR_COVERAGE_LCOV(
			NAME erric_coverage
			EXECUTABLE ctest
			DEPENDENCIES erric
		)

	endif()

endif()

include_directories(include)

if(${MSVC})
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)
endif()

# Build all files as library so that they can be re-used for tests
add_library(erric_interpreter SHARED
		src/erric_interpreter.c
		src/erric_util.c
		src/branch_operators.c
		src/math_operators.c
		src/memory_operators.c
		src/logic_operators.c
		src/file_reading.c
		src/reverse_translation.c
		)

add_executable(${PROJECT_NAME} src/main.c)

target_link_libraries(${PROJECT_NAME} erric_interpreter)

if(${CMAKE_HOST_WIN32})
	# This command will put the .dll file into the /bin folder under Windows.
	# The .dll is always needed for the example .exe and the tests.
	# Also saves a lot of nerves during testing - tests didn't fetch the newly compiled .dll-s
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy
			"$<TARGET_FILE_DIR:erric_interpreter>/${CMAKE_SHARED_LIBRARY_PREFIX}erric_interpreter.dll"
			"${EXECUTABLE_OUTPUT_PATH}/${CMAKE_SHARED_LIBRARY_PREFIX}erric_interpreter.dll")
endif()