cmake_minimum_required(VERSION 3.16)

project(lab5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenMP REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cc"
)

add_executable(lab5 ${SOURCES})

target_link_libraries(lab5 PRIVATE OpenMP::OpenMP_CXX)

target_include_directories(lab5 PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)

target_compile_options(lab5 PRIVATE
    -O3                  # maximum optimization level
    -march=native        # vectorizes code
    -mtune=native        # tune pipeline scheduling
    -funroll-loops       # unrolls loops
    -fomit-frame-pointer # frees up an extra CPU register
    -flto                # LTO
)
# LTO for linker
target_link_options(lab5 PRIVATE -flto -O3)
