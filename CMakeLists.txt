cmake_minimum_required(VERSION 3.23)
project(configFiles LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
message(STATUS "Fetching content...")

FetchContent_Declare(cmake_helpers
        GIT_REPOSITORY https://github.com/truenicfel/cmakeHelpers
        GIT_TAG 3a93e28dfede98d438f797e95cf22c74743b55fb # v1.1.0
        )
FetchContent_MakeAvailable(cmake_helpers)
printGitRepoInfo(${cmake_helpers_SOURCE_DIR})

FetchContent_Declare(toml11
        GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
        GIT_TAG dcfe39a783a94e8d52c885e5883a6fbb21529019 # v3.7.1
)
set (toml11_INSTALL OFF CACHE INTERNAL "Install CMake targets during install step.")
FetchContent_MakeAvailable(toml11)
printGitRepoInfo(${toml11_SOURCE_DIR})

message(STATUS "Done fetching content.")

add_subdirectory(configuration)
add_subdirectory(tomlParser)

add_executable(configFiles main.cpp)

target_link_libraries(configFiles PRIVATE toml11::toml11 configuration)
