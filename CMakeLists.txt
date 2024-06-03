cmake_minimum_required(VERSION 3.13)

project(ll_InventorySystem)

include(cmake/fileLists.cmake)

add_library(${PROJECT_NAME}
    ${MAIN_SOURCES}
)


enable_testing()
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/utest
)
