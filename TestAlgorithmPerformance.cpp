//
// Created by cinek on 16.06.2024.
//

#include "TestAlgorithmPerformance.h"

#include <random>

TestAlgorithmPerformance::TestAlgorithmPerformance() {}

void TestAlgorithmPerformance::runTests() {
    std::vector<int> vertexCounts = {40, 60, 80, 100, 120, 140, 160};
    std::vector<double> densities = {0.25, 0.50, 0.99};
    std::ofstream outFile("results.txt");

    for (int V : vertexCounts) {
        for (double density : densities) {
            runMSTTests(V, density, outFile);
            runShortestPathTests(V, density, outFile);
        }
    }
}

void TestAlgorithmPerformance::runMSTTests(int V, double density, std::ofstream& outFile) {
    std::cout << "Running MST tests for V = " << V << " and density = " << density * 100 << "%" << std::endl;

    double totalTimeMatrixPrim = 0;
    double totalTimeListPrim = 0;
    double totalTimeMatrixKruskal = 0;
    double totalTimeListKruskal = 0;

    for (int i = 0; i < 20; ++i) {
        auto matrixGraph = generateRandomMatrixGraph(V, density);
        auto listGraph = generateRandomListGraph(V, density);

        totalTimeMatrixPrim += measureExecutionTime([&]() { primAlgorithm.findMST(matrixGraph, 0); });
        totalTimeListPrim += measureExecutionTime([&]() { primAlgorithm.findMST(listGraph, 0); });
        totalTimeMatrixKruskal += measureExecutionTime([&]() { kruskalAlgorithm.findMST(matrixGraph, 0); });
        totalTimeListKruskal += measureExecutionTime([&]() { kruskalAlgorithm.findMST(listGraph, 0); });

        delete matrixGraph;
        delete listGraph;
    }

    outFile << "MST Prim (Matrix) for V = " << V << ", density = " << density * 100 << "%: " << (totalTimeMatrixPrim / 20) << " ms\n";
    outFile << "MST Prim (List) for V = " << V << ", density = " << density * 100 << "%: " << (totalTimeListPrim / 20) << " ms\n";
    outFile << "MST Kruskal (Matrix) for V = " << V << ", density = " << density * 100 << "%: " << (totalTimeMatrixKruskal / 20) << " ms\n";
    outFile << "MST Kruskal (List) for V = " << V << ", density = " << density * 100 << "%: " << (totalTimeListKruskal / 20) << " ms\n";
}

void TestAlgorithmPerformance::runShortestPathTests(int V, double density, std::ofstream& outFile) {
    std::cout << "Running Shortest Path tests for V = " << V << " and density = " << density * 100 << "%" << std::endl;

    double totalTimeMatrixDijkstra = 0;
    double totalTimeListDijkstra = 0;
    double totalTimeMatrixFordBellman = 0;
    double totalTimeListFordBellman = 0;

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < 20; ++i) {
        auto matrixGraph = generateRandomMatrixGraph(V, density);
        auto listGraph = generateRandomListGraph(V, density);

        std::uniform_int_distribution<> dis(0, V - 1);
        int startVertex = dis(gen);
        int endVertex = dis(gen);

        while (startVertex == endVertex) {
            endVertex = dis(gen);
        }

        int totalCost;
        totalTimeMatrixDijkstra += measureExecutionTime([&]() { dijkstraAlgorithm.findShortestPath(matrixGraph, startVertex, endVertex, totalCost, false); });
        totalTimeListDijkstra += measureExecutionTime([&]() { dijkstraAlgorithm.findShortestPath(listGraph, startVertex, endVertex, totalCost, false); });
        totalTimeMatrixFordBellman += measureExecutionTime([&]() { fordBellmanAlgorithm.findShortestPath(matrixGraph, startVertex, endVertex, totalCost, false); });
        totalTimeListFordBellman += measureExecutionTime([&]() { fordBellmanAlgorithm.findShortestPath(listGraph, startVertex, endVertex, totalCost, false); });

        delete matrixGraph;
        delete listGraph;
    }

    outFile << "Shortest Path Dijkstra (Matrix) for V = " << V << ", density = " << density * 100 << "%: " << (totalTimeMatrixDijkstra / 20) << " ms\n";
    outFile << "Shortest Path Dijkstra (List) for V = " << V << ", density = " << density * 100 << "%: " << (totalTimeListDijkstra / 20) << " ms\n";
    outFile << "Shortest Path Ford-Bellman (Matrix) for V = " << V << ", density = " << density * 100 << "%: " << (totalTimeMatrixFordBellman / 20) << " ms\n";
    outFile << "Shortest Path Ford-Bellman (List) for V = " << V << ", density = " << density * 100 << "%: " << (totalTimeListFordBellman / 20) << " ms\n";
}

AdjacencyMatrixGraph* TestAlgorithmPerformance::generateRandomMatrixGraph(int V, double density) {
    AdjacencyMatrixGraph* graph = new AdjacencyMatrixGraph(V, true);
    int maxEdges = V * (V - 1) / 2;
    int desiredEdges = static_cast<int>(maxEdges * density);
    int edgesAdded = 0;

    srand(time(nullptr));
    while (edgesAdded < desiredEdges) {
        int u = rand() % V;
        int v = rand() % V;
        if (u != v && !graph->edgeExists(u, v)) {
            int weight = rand() % 100 + 1;
            graph->addEdge(u, v, weight);
            edgesAdded++;
        }
    }

    return graph;
}

AdjacencyListGraph* TestAlgorithmPerformance::generateRandomListGraph(int V, double density) {
    AdjacencyListGraph* graph = new AdjacencyListGraph(V, true);
    int maxEdges = V * (V - 1) / 2;
    int desiredEdges = static_cast<int>(maxEdges * density);
    int edgesAdded = 0;

    srand(time(nullptr));
    while (edgesAdded < desiredEdges) {
        int u = rand() % V;
        int v = rand() % V;
        if (u != v && !graph->edgeExists(u, v)) {
            int weight = rand() % 100 + 1;
            graph->addEdge(u, v, weight);
            edgesAdded++;
        }
    }

    return graph;
}

double TestAlgorithmPerformance::measureExecutionTime(std::function<void()> func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    return elapsed.count();
}