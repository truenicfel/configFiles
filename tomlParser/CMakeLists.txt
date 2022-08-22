set(LIBRARY_NAME tomlParser)

add_library(${LIBRARY_NAME} source/TOMLParser.cpp)

target_include_directories(${LIBRARY_NAME} PUBLIC include/)

target_link_libraries(${LIBRARY_NAME} PUBLIC configuration)

target_link_libraries(${LIBRARY_NAME} PRIVATE toml11::toml11)