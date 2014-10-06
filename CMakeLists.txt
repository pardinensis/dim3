cmake_minimum_required(VERSION 2.8)
set(NAME dim3)
project(${NAME})


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(OpenGL)
find_package(GLEW)
find_package(SDL2)
find_package(SDL2_image)
find_package(GLM)

configure_file (
	"${PROJECT_SOURCE_DIR}/buildconfig.h.in"
	"${PROJECT_BINARY_DIR}/buildconfig.h"
)
include_directories("${PROJECT_BINARY_DIR}")

aux_source_directory("${CMAKE_SOURCE_DIR}/source" sources)


set(warnings "-Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(${NAME} ${sources})

target_link_libraries(${NAME} GL)
target_link_libraries(${NAME} GLEW)
target_link_libraries(${NAME} SDL2)
target_link_libraries(${NAME} SDL2_image)