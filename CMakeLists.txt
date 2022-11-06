cmake_minimum_required(VERSION 3.12)
include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SpyralMenu)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=1)

set(G3_SHARED_LIB OFF)
set(CHANGE_G3LOG_DEBUG_TO_DBUG ON)
set(ENABLE_FATAL_SIGNALHANDLING OFF)
set(ENABLE_VECTORED_EXCEPTIONHANDLING OFF)
set(ADD_FATAL_EXAMPLE OFF)

FetchContent_Declare(
    minhook
    GIT_REPOSITORY https://github.com/Spyral-Org/minhook.git
    GIT_TAG        4a455528f61b5a375b1f9d44e7d296d47f18bb18
	GIT_PROGRESS TRUE
)
FetchContent_Declare(
    g3log
    GIT_REPOSITORY https://github.com/Spyral-Org/g3log.git
    GIT_TAG        ed91b899f07845baea0d104c7134006c138602a1
	GIT_PROGRESS TRUE
)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/Spyral-Org/imgui.git
    GIT_TAG        1dd964f87dc1ea0a76b137baf3401bd201fc2012
	GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(minhook g3log imgui)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} g3log imgui minhook)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
