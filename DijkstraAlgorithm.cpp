//
// Created by cinek on 03.06.2024.
//

#include "DijkstraAlgorithm.h"

#include <queue>
#include <limits>
#include <algorithm>

// Implementacja algorytmu Dijkstry
std::vector<int> DijkstraAlgorithm::findShortestPath(Graph* graph, int startVertex, int endVertex, int& totalCost, bool verbose) {
    int V = graph->getVertexCount();  // Pobranie liczby wierzchołków w grafie
    std::vector<int> dist(V, std::numeric_limits<int>::max());  // Inicjalizacja odległości na nieskończoność
    std::vector<int> parent(V, -1);  // Tablica przechowująca rodziców wierzchołków na najkrótszej ścieżce
    dist[startVertex] = 0;  // Odległość do startVertex ustawiona na 0

    // Definicja funkcji porównującej do kolejki priorytetowej
    auto compare = [](std::pair<int, int> left, std::pair<int, int> right) {
        return left.second > right.second;
    };
    // Kolejka priorytetowa, przechowująca pary (wierzchołek, koszt), posortowane względem kosztu
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(compare)> pq(compare);
    pq.push({startVertex, 0});  // Wstawienie startVertex do kolejki z kosztem 0

    // Główna pętla algorytmu Dijkstry
    while (!pq.empty()) {
        int u = pq.top().first;  // Pobranie wierzchołka z najmniejszym kosztem
        pq.pop();

        // Iteracja po wszystkich wierzchołkach v sąsiadujących z u
        for (int v = 0; v < V; ++v) {
            if (graph->edgeExists(u, v)) {  // Sprawdzenie istnienia krawędzi (u, v)
                int weight = graph->getEdgeWeight(u, v);  // Pobranie wagi krawędzi (u, v)
                // Jeśli znaleziono krótszą ścieżkę do v, zaktualizuj odległość i dodaj do kolejki priorytetowej
                if (dist[u] != std::numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;  // Aktualizacja odległości do v
                    pq.push({v, dist[v]});  // Dodanie v do kolejki priorytetowej z nowym kosztem
                    parent[v] = u;  // Ustawienie u jako rodzica v na najkrótszej ścieżce
                }
            }
        }
    }

    std::vector<int> path;
    // Odtworzenie najkrótszej ścieżki od endVertex do startVertex
    for (int v = endVertex; v != -1; v = parent[v]) {
        path.push_back(v);  // Dodanie wierzchołka do ścieżki
    }
    std::reverse(path.begin(), path.end());  // Odwrócenie wektora, aby uzyskać ścieżkę od startVertex do endVertex

    totalCost = dist[endVertex];  // Ustawienie całkowitego kosztu najkrótszej ścieżki

    return path;  // Zwrócenie znalezionej ścieżki
}