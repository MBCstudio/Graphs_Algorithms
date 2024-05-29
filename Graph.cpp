//
// Created by cinek on 29.05.2024.
//

#include "Graph.h"
#include <iostream>
#include <iomanip>

// AdjacencyMatrixGraph implementation
AdjacencyMatrixGraph::AdjacencyMatrixGraph(int V) : V(V), matrix(V, std::vector<int>(V, 0)) {}

void AdjacencyMatrixGraph::addEdge(int u, int v, int weight) {
    matrix[u][v] = weight;
    // Uncomment the next line for undirected graphs
    // matrix[v][u] = weight;
}

void AdjacencyMatrixGraph::display() {
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << std::setw(5) << val;
        }
        std::cout << std::endl;
    }
}

// AdjacencyListGraph implementation
AdjacencyListGraph::AdjacencyListGraph(int V) : V(V), adjList(V) {}

void AdjacencyListGraph::addEdge(int u, int v, int weight) {
    adjList[u].emplace_back(v, weight);
    // Uncomment the next line for undirected graphs
    // adjList[v].emplace_back(u, weight);
}

void AdjacencyListGraph::display() {
    for (int u = 0; u < V; ++u) {
        std::cout << u << ": ";
        for (const auto& [v, weight] : adjList[u]) {
            std::cout << "(" << v << ", " << weight << ") ";
        }
        std::cout << std::endl;
    }
}

bool AdjacencyListGraph::edgeExists(int u, int v) const {
    for (const auto& edge : adjList[u]) {
        if (edge.first == v) return true;
    }
    return false;
}
