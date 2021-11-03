cmake_minimum_required(VERSION 3.0.0)
project(server-from-scratch VERSION 0.1.0)


include_directories(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

enable_testing()
add_subdirectory(${PROJECT_SOURCE_DIR}/googletest)
add_subdirectory(tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
