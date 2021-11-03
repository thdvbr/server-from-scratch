include_directories(${PROJECT_SOURCE_DIR}/src/client)
include_directories(${PROJECT_SOURCE_DIR}/src/server)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/server)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/client)