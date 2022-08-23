cmake_minimum_required(VERSION 3.22)
project(configFiles LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
message(STATUS "Fetching content...")

FetchContent_Declare(cmake_helpers
        GIT_REPOSITORY https://github.com/truenicfel/cmakeHelpers
        GIT_TAG e5d9b0448fd785dcebc0f1e43820ebcc75954bfe # v1.1.1
        )
FetchContent_MakeAvailable(cmake_helpers)
printGitRepoInfo(${cmake_helpers_SOURCE_DIR})

FetchContent_Declare(toml11
        GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
        GIT_TAG dcfe39a783a94e8d52c885e5883a6fbb21529019 # v3.7.1
)
set(toml11_INSTALL OFF CACHE INTERNAL "Install CMake targets during install step.")
FetchContent_MakeAvailable(toml11)
printGitRepoInfo(${toml11_SOURCE_DIR})

FetchContent_Declare(date_src
        GIT_REPOSITORY https://github.com/HowardHinnant/date.git
        GIT_TAG        6e921e1b1d21e84a5c82416ba7ecd98e33a436d0 # v3.0.1
        )
set(BUILD_TZ_LIB ON CACHE INTERNAL "build/install of TZ library")
FetchContent_MakeAvailable(date_src)
printGitRepoInfo(${date_src_SOURCE_DIR})

message(STATUS "Done fetching content.")

add_subdirectory(configuration)
add_subdirectory(tomlParser)

add_executable(configFiles main.cpp)

target_link_libraries(configFiles PRIVATE toml11::toml11 tomlParser)
