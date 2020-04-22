cmake_minimum_required(VERSION 3.14)
project(PSU_2019_malloc C)
set(CMAKE_C_STANDARD 99)

######################################
# CPPFLAGS and CFLAGS
include_directories(include tests/include)
add_compile_options(-std=c99 -Wall -Wextra)


######################################
# Project Configuration
set(SRC         ${CMAKE_SOURCE_DIR}/src)
set(TESTS       ${CMAKE_SOURCE_DIR}/tests)


######################################
# Malloc Library
add_subdirectory(${SRC})
link_libraries(my_malloc)



######################################
# DEBUG MAIN TEST
add_executable(
        PSU_2019_malloc
        ${TESTS}/main_test_malloc.c
)
target_compile_definitions(
        my_malloc PUBLIC
        _DEBUG_
)