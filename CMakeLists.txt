cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(voronoi LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
include_directories(include)

option(ENABLE_COVERAGE "Enable coverage" false)
set(CMAKE_VERBOSE_MAKEFILE true)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
if(ENABLE_COVERAGE)
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Set the build type. " FORCE)
	include(CodeCoverage.cmake)
	append_coverage_compiler_flags()
endif()
add_executable(main ./app/main.cpp)
if(ENABLE_COVERAGE)
	setup_target_for_coverage_lcov(
		NAME coverage
		EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/main
		LCOV_ARGS --rc lcov_branch_coverage=1
		GENHTML_ARGS --legend --branch-coverage
		DEPENDENCIES main
	)
endif()


