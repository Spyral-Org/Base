cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SpyralMenu)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=1)

set(G3_SHARED_LIB OFF)
set(CHANGE_G3LOG_DEBUG_TO_DBUG ON)
set(ENABLE_FATAL_SIGNALHANDLING OFF)
set(ENABLE_VECTORED_EXCEPTIONHANDLING OFF)
add_subdirectory(vendor/g3log)
include_directories(vendor/g3log/src)

add_subdirectory(vendor/minhook)
include_directories(vendor/minhook/include)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} g3log minhook)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
