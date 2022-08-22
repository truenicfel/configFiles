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

FetchContent_Declare(nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG bc889afb4c5bf1c0d8ee29ef35eaaf4c8bef8a5d # v3.11.2
        )
FetchContent_MakeAvailable(nlohmann_json)
printGitRepoInfo(${nlohmann_json_SOURCE_DIR})

message(STATUS "Done fetching content.")

add_executable(configFiles main.cpp)

#target_link_libraries(configFiles PRIVATE nlohmann_json::nlohmann_json)
