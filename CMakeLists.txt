cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(voronoi LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
find_package(CGAL)
option(ENABLE_COVERAGE "Enable coverage" false)
set(CMAKE_VERBOSE_MAKEFILE true)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
if(ENABLE_COVERAGE)
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Set the build type. " FORCE)
	include(CodeCoverage.cmake)
	append_coverage_compiler_flags()
endif()
include_directories(include)
add_executable(test_voronoi ./app/tests/test_voronoi.cpp)
target_link_libraries(test_voronoi CGAL::CGAL)
add_executable(gen_points ./app/utilities/gen_points.cpp)
if(ENABLE_COVERAGE)
	setup_target_for_coverage_lcov(
		NAME coverage
		EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/test_voronoi
		EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/gen_points
		LCOV_ARGS --rc lcov_branch_coverage=1
		GENHTML_ARGS --legend --branch-coverage
		DEPENDENCIES test_voronoi gen_points)
endif()


