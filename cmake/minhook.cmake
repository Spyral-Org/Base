include(FetchContent)

set(LIB_NAME "minhook")
message("Setting up ${LIB_NAME}")

FetchContent_Declare(
    ${LIB_NAME}
    GIT_REPOSITORY https://github.com/Spyral-Org/minhook.git
    GIT_TAG        4a455528f61b5a375b1f9d44e7d296d47f18bb18
	GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(${LIB_NAME})