cmake_minimum_required(VERSION 3.15)
project(decellulator CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/lib/include)

file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/src/*.c" "${CMAKE_SOURCE_DIR}/src/*.cc")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_SOURCE_DIR}/include/*.hpp" "${CMAKE_SOURCE_DIR}/lib/include/*.h")

add_library(decellulator ${SRC_FILES} ${HEADER_FILES})
target_include_directories(decellulator PUBLIC include)

set_target_properties(decellulator PROPERTIES PUBLIC_HEADER "include/decellulator.h")
install(TARGETS decellulator)
