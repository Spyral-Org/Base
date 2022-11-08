include(FetchContent)

set(LIB_NAME "g3log")
message("Setting up ${LIB_NAME}")

set(ADD_FATAL_EXAMPLE OFF CACHE INTERNAL "")
set(INSTALL_G3LOG OFF CACHE INTERNAL "")
set(G3_SHARED_LIB OFF CACHE INTERNAL "")
set(G3_SHARED_RUNTIME OFF CACHE INTERNAL "")

FetchContent_Declare(
    ${LIB_NAME}
    GIT_REPOSITORY https://github.com/Spyral-Org/g3log.git
    GIT_TAG        6ccf93c2e966e9ae13df75496a88e7b45214f7f8
	GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(${LIB_NAME})