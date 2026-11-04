cmake_minimum_required(VERSION 3.16)

project(lab5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cc"
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(lab5 ${SOURCES})

target_include_directories(lab5 PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)
