cmake_minimum_required(VERSION 3.27)
project(grafy_1)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(grafy_1 main.cpp
        Graph.cpp
        Graph.h
        Menu.cpp
        Menu.h
        MSTAlgorithm.cpp
        MSTAlgorithm.h
        DijkstraAlgorithm.cpp
        DijkstraAlgorithm.h
        FordBellmanAlgorithm.cpp
        FordBellmanAlgorithm.h
        TestAlgorithmPerformance.cpp
        TestAlgorithmPerformance.h)
