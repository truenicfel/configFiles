cmake_minimum_required(VERSION 3.22)
project(configFiles
        VERSION 0.2.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
if(PROJECT_IS_TOP_LEVEL)
    set(VERSION_INFO_REPO_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
else()
    set(VERSION_INFO_REPO_PATH "" CACHE PATH "Path to the git repo where the version information should be taken from.")
endif()


if(NOT EXISTS ${VERSION_INFO_REPO_PATH})
    message(FATAL_ERROR "VERSION_INFO_REPO_PATH must be defined. ${VERSION_INFO_REPO_PATH}")
endif()

include(FetchContent)
message(STATUS "Fetching content...")

FetchContent_Declare(cmake_helpers
        GIT_REPOSITORY https://github.com/truenicfel/cmakeHelpers
        GIT_TAG 8cb39f37c6b1d1048e1460c3500f681b59530434 # v1.2.0
        )
FetchContent_MakeAvailable(cmake_helpers)

FetchContent_Declare(toml11
        GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
        GIT_TAG dcfe39a783a94e8d52c885e5883a6fbb21529019 # v3.7.1
)
set(toml11_INSTALL OFF CACHE INTERNAL "Install CMake targets during install step.")
FetchContent_MakeAvailable(toml11)

FetchContent_Declare(project_info
        GIT_REPOSITORY https://github.com/truenicfel/projectInfo
        GIT_TAG 3be4e88a07afdd225cfd9b11ee017b6de28be2de # v1.0.1
        )
set(USE_CMAKE_HELPERS ON CACHE INTERNAL "Set this to on if version information should be taken from parent project (does not work for branch and hash).")
set(CMAKE_HELPERS_GIT_REPOSITORY_PATH ${VERSION_INFO_REPO_PATH} CACHE INTERNAL "The path to the git repository that should be used to retrieve version information from.")
FetchContent_MakeAvailable(project_info)

printGitRepoInfo(${cmake_helpers_SOURCE_DIR})
printGitRepoInfo(${toml11_SOURCE_DIR})
printGitRepoInfo(${project_info_SOURCE_DIR})

message(STATUS "Done fetching content.")

add_subdirectory(configuration)
add_subdirectory(tomlParser)

add_executable(configFiles main.cpp)

target_link_libraries(configFiles PRIVATE toml11::toml11 tomlParser)
