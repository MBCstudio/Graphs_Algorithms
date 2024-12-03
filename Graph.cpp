//
// Created by cinek on 29.05.2024.
//

#include "Graph.h"
#include <iostream>

// Implemantacja AdjacencyMatrixGraph

// Konstruktor
AdjacencyMatrixGraph::AdjacencyMatrixGraph(int V, bool directed) : V(V), directed(directed), matrix(V, std::vector<int>(V, 0)) {}

// Konstruowanie krawedzi
void AdjacencyMatrixGraph::addEdge(int u, int v, int weight) {
    matrix[u][v] = weight;
    if (!directed) {
        matrix[v][u] = weight; // Jeżeli graf jest nieskierowny
    }
}

// Wyswietalanie krawiedzi
void AdjacencyMatrixGraph::displayList() {
    std::cout << "Lisat sasiedztwa (utworzona z reprezentacji macierzowej):" << std::endl;
    for (int u = 0; u < V; ++u) {
        std::cout << u << ":";
        for (int v = 0; v < V; ++v) {
            if (matrix[u][v] != 0) {
                std::cout << " (" << v << ", " << matrix[u][v] << ")";
            }
        }
        std::cout << std::endl;
    }
}

// Wyswietalanie krawiedzi
void AdjacencyMatrixGraph::displayMatrix() {
    std::cout << "Macierz sasiedztwa" << std::endl;
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

// Sprawdzenie czy krawiedz pomiedzy u i v istnieje
bool AdjacencyMatrixGraph::edgeExists(int u, int v) const {
    return matrix[u][v] != 0;
}

// Sprawdzanie czy graf jest skierowny
void AdjacencyMatrixGraph::setDirected(bool directed) {
    this->directed = directed;
}

// Pobranie wierzchołków
int AdjacencyMatrixGraph::getVertexCount() const {
    return V;
}
// Pobieranie wag karwiedzi
int AdjacencyMatrixGraph::getEdgeWeight(int u, int v) const {
    return matrix[u][v];
}

// Implementacja AdjacencyListGraph

// Konstruktor inicjalizujący liczbę wierzchołków i czy graf jest skierowany
AdjacencyListGraph::AdjacencyListGraph(int V, bool directed) : V(V), directed(directed), adjList(V) {}

// Dodawanie krawedzi
void AdjacencyListGraph::addEdge(int u, int v, int weight) {
    adjList[u].emplace_back(v, weight);
    if (!directed) {
        adjList[v].emplace_back(u, weight); // Jeżeli graf jest nieskierowny
    }
}

// Wyswietalnie listy
void AdjacencyListGraph::displayList() {
    std::cout << "Lista sasiedzwtwa:" << std::endl;
    for (int u = 0; u < V; ++u) {
        std::cout << "Wierzcholki " << u << ":";
        for (const auto& edge : adjList[u]) {
            std::cout << " -> (" << edge.first << ", " << edge.second << ")";
        }
        std::cout << std::endl;
    }
}

// Wyswietalnie matrixa
void AdjacencyListGraph::displayMatrix() {
    std::vector<std::vector<int>> matrix(V, std::vector<int>(V, 0));
    for (int u = 0; u < V; ++u) {
        for (const auto& edge : adjList[u]) {
            int v = edge.first;
            int weight = edge.second;
            matrix[u][v] = weight;
            if (!directed) {
                matrix[v][u] = weight; // If the graph is undirected
            }
        }
    }

    std::cout << "Macierz sasiedztwa:" << std::endl;
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

// Sprawdzanie czy karedz istnieje
bool AdjacencyListGraph::edgeExists(int u, int v) const {
    for (const auto& edge : adjList[u]) {
        if (edge.first == v) return true;
    }
    return false;
}

// Sprawdzanie czy jest spierawany
void AdjacencyListGraph::setDirected(bool directed) {
    this->directed = directed;
}

// Pobieranie krawedzi
int AdjacencyListGraph::getVertexCount() const {
    return V;
}

// Pobieranie wartosci karedzi
int AdjacencyListGraph::getEdgeWeight(int u, int v) const {
    for (const auto& edge : adjList[u]) {
        if (edge.first == v) {
            return edge.second;
        }
    }
    return 0;
}