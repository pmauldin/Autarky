cmake_minimum_required(VERSION 3.15)
project(Autarky)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES "src/*.h" "src/*.cpp" "src/*.c")
add_executable(Autarky ${SRC_FILES})

target_link_libraries(Autarky GL GLU glfw3 X11 Xxf86vm Xrandr pthread Xi dl Xinerama Xcursor assimp)
