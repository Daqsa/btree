cmake_minimum_required(VERSION 3.25.2)
set (CMAKE_CXX_STANDARD 20)

project(binary_search_tree)

add_executable(binary_search_tree 
    binary_search_tree.cpp 
    main.cpp 
    ../include/binary_search_tree.hpp)

target_include_directories(binary_search_tree PRIVATE ${PROJECT_SOURCE_DIR}/../include)