cmake_minimum_required(VERSION 3.24)

project(pwe_core CXX C)

find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

file(GLOB_RECURSE source_files
    "*.c"
    "*.cpp"
    "*.h"
    "*.hpp"
)

add_library(pwe_core ${source_files})

target_compile_features(pwe_core PRIVATE cxx_std_23)

target_include_directories(pwe_core
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/..>
        ${CMAKE_CURRENT_SOURCE_DIR}
        OpenGL
)

target_link_libraries(
    pwe_core
    libcommon
    nod
    lzokay
    OpenGL::GL
    assimp::assimp
    fmt::fmt
    spdlog::spdlog
    Threads::Threads
    ${ZLIB_LIBRARY}
)

target_compile_definitions(
    pwe_core
    PRIVATE
        USE_LZOKAY
    PUBLIC
        UNICODE
        GLEW_STATIC
)
