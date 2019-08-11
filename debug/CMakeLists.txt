cmake_minimum_required(VERSION 2.8.12)

file(GLOB_RECURSE project_headers
               "*.h"
               "*.hpp")

file(GLOB_RECURSE project_sources
               "*.cc"
               "*.cpp")

set(SRC_LISTS ${project_headers} ${project_sources})
set(OUTPUT_NAME "debug")

message(STATUS "This is Binary dir " ${PROJECT_BINARY_DIR})
message(STATUS "This is Source dir " ${PROJECT_SOURCE_DIR})

message(STATUS "Python Header dir" ${PYTHON_INCLUDE_DIRS})
message(STATUS "Python Library dir" ${PYTHON_LIBRARIES})
# source_group("source" FILES ${SRC_LISTS})

include_directories(
	.
	${PYTHON_INCLUDE_DIRS}
	${PROJECT_SOURCE_DIR}/include
)
add_executable(${OUTPUT_NAME} ${SRC_LISTS})
target_link_libraries(${OUTPUT_NAME} ${PYTHON_LIBRARIES})