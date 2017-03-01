cmake_minimum_required(VERSION 3.6)
project(graph_isomorphic)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Graph/CGraph.cpp main.cpp)
add_executable(graph_isomorphic ${SOURCE_FILES})