cmake_minimum_required(VERSION 3.13)

project(ll_InventorySystem_utest)

add_executable(${PROJECT_NAME}
    ${ALL_SOURCES}
)
AddDefaultFlags(${PROJECT_NAME})

enable_testing()
add_test(
    NAME ${PROJECT_NAME} 
    COMMAND ${PROJECT_NAME} 
)
