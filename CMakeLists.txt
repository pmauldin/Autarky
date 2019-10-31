cmake_minimum_required(VERSION 3.15)
project(Autarky)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(ZLIB_ROOT Z:/Dev/MinGW/bin)
set(ZLIB_INCLUDE_DIR Z:/Dev/MinGW/bin)

find_package(GLFW3 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(irrXML REQUIRED)
find_package(assimp REQUIRED)

link_directories("Z:/Dev/Libraries/OpenGL/Libs")
include_directories("Z:/Dev/Libraries/OpenGL/Include" ${ZLIB_INCLUDE_DIRS})
file(GLOB_RECURSE SRC_FILES "src/*.h" "src/*.cpp" "src/*.c")

add_executable(Autarky ${SRC_FILES})

MESSAGE(STATUS "Found ASSIMP: ${ASSIMP_LIBRARY}")
MESSAGE(STATUS "Found IRRXML: ${IRRXML_LIBRARY}")
target_link_libraries(Autarky glfw3 ${ASSIMP_LIBRARY} ${ZLIB_LIBRARIES} ${IRRXML_LIBRARY})
