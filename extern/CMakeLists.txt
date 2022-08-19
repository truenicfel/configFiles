
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmakeHelpers)

include(gitHelpers)

#printSubmoduleStates()

add_subdirectory(json)
