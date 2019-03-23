cmake_minimum_required(VERSION 3.10)
project(task1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie")

set(CMAKE_CXX_STANDARD 11)

add_executable(task1 main.cpp IGraph.cpp IGraph.h CListGraph.cpp CListGraph.h CMatrixGraph.cpp CMatrixGraph.h CSetGraph.cpp CSetGraph.h CArcGraph.cpp CArcGraph.h)