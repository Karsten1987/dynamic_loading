cmake_minimum_required(VERSION 3.5)
project(my_c_project)

set (CMAKE_EXE_LINKER_FLAGS "-ldl")
add_definitions(-std=c11)

add_executable(class_loader class_loader.c)
target_link_libraries(class_loader "-ldl")

add_library(interface SHARED change_state.c)
