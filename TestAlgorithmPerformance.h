//
// Created by cinek on 16.06.2024.
//

#ifndef GRAFY_1_TESTALGORITHMPERFORMANCE_H
#define GRAFY_1_TESTALGORITHMPERFORMANCE_H


#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <memory>
#include <functional>
#include "Graph.h"
#include "MSTAlgorithm.h"
#include "DijkstraAlgorithm.h"
#include "FordBellmanAlgorithm.h"

class TestAlgorithmPerformance {
public:
    TestAlgorithmPerformance();
    void runTests();

private:
    void runMSTTests(int V, double density, std::ofstream& outFile);
    void runShortestPathTests(int V, double density, std::ofstream& outFile);
    AdjacencyMatrixGraph* generateRandomMatrixGraph(int V, double density);
    AdjacencyListGraph* generateRandomListGraph(int V, double density);
    double measureExecutionTime(std::function<void()> func);

    PrimAlgorithm primAlgorithm;
    KruskalAlgorithm kruskalAlgorithm;
    DijkstraAlgorithm dijkstraAlgorithm;
    FordBellmanAlgorithm fordBellmanAlgorithm;
};

#endif //GRAFY_1_TESTALGORITHMPERFORMANCE_H
