cmake_minimum_required(VERSION 3.13)

project(ll_InventorySystem_utest)


include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}
    ${ALL_SOURCES}
)
AddDefaultFlags(${PROJECT_NAME})


target_link_libraries(${PROJECT_NAME}
PRIVATE
    gtest gtest_main gmock
)


enable_testing()
add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)
