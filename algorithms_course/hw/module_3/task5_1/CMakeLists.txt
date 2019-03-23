cmake_minimum_required(VERSION 3.10)
project(task5_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie")

set(CMAKE_CXX_STANDARD 11)

add_executable(task5_1 main.cpp DSU.cpp DSU.h KruskalsAlgorithm.cpp Graph.cpp Graph.h RandomPointsGenerator.cpp TravellingSalesmanProblem.cpp TravellingSalesmanProblem.h Tests.cpp Tests.h)