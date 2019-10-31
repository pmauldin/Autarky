cmake_minimum_required(VERSION 3.15)
project(Autarky)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(GLFW3 REQUIRED)

link_directories("Z:/Dev/Libraries/OpenGL/Libs")
include_directories("Z:/Dev/Libraries/OpenGL/Include")
file(GLOB_RECURSE SRC_FILES "src/*.h" "src/*.cpp" "src/*.c")

add_executable(Autarky ${SRC_FILES})

target_link_libraries(Autarky glfw3)
