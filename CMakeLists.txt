cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SpyralMenu CXX ASM_MASM)
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=1)

message("Fetching Modules")
include(cmake/g3log.cmake)
include(cmake/imgui.cmake)
include(cmake/minhook.cmake)

file(GLOB_RECURSE SOURCE_FILES
    "${SRC_DIR}/*.asm"
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/*.hpp")

add_library(${PROJECT_NAME} MODULE ${SOURCE_FILES})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

add_compile_definitions(${PROJECT_NAME}
    "_CRT_SECURE_NO_WARNINGS"
    "NOMINMAX"
    "WIN32_LEAN_AND_MEAN")

target_include_directories(${PROJECT_NAME} PRIVATE
    "${SRC_DIR}"
    "${minhook_SOURCE_DIR}/include"
    "${imgui_SOURCE_DIR}")

target_precompile_headers(${PROJECT_NAME} PRIVATE "${SRC_DIR}/common.hpp")
target_link_libraries(${PROJECT_NAME} PRIVATE g3log imgui minhook)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
