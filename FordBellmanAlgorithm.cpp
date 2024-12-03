//
// Created by cinek on 03.06.2024.
//

#include "FordBellmanAlgorithm.h"
#include <limits>
#include <algorithm>

// Implementacja metody findShortestPath
std::vector<int> FordBellmanAlgorithm::findShortestPath(Graph* graph, int startVertex, int endVertex, int& totalCost, bool verbose) {
    int V = graph->getVertexCount();  // Pobranie liczby wierzchołków w grafie
    std::vector<int> dist(V, std::numeric_limits<int>::max());  // Inicjalizacja odleglosci na nieskonczonosc
    std::vector<int> parent(V, -1);  // Tablica przechowująca rodzicow wierzchołkow na najkrotszej sciezce
    dist[startVertex] = 0;  // Odległość do startVertex ustawiona na 0

    // Wykonanie relaksacji krawędzi V-1 razy
    for (int i = 1; i <= V - 1; ++i) {
        // Iteracja po wszystkich krawędziach (u, v) w grafie
        for (int u = 0; u < V; ++u) {
            for (int v = 0; v < V; ++v) {
                if (graph->edgeExists(u, v)) {  // Sprawdzenie istnienia krawędzi (u, v)
                    int weight = graph->getEdgeWeight(u, v);  // Pobranie wagi krawędzi (u, v)
                    // Jeśli znaleziono krótszą ścieżkę do v to zaktualizuje odleglosc i rodzica
                    if (dist[u] != std::numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;  // Aktualizacja odległości do v
                        parent[v] = u;  // Ustawienie u jako rodzica v na najkrótszej ścieżce
                    }
                }
            }
        }
    }

    std::vector<int> path;
    // Odtworzenie najkrótszej ścieżki od endVertex do startVertex
    for (int v = endVertex; v != -1; v = parent[v]) {
        path.push_back(v);  // Dodanie wierzchołka do ścieżki
    }
    std::reverse(path.begin(), path.end());  // Odwrócenie wektora uzyskujemy sciezke

    totalCost = dist[endVertex];  // Ustawienie całkowitego kosztu najkrótszej ścieżki

    return path;  // Zwrócenie znalezionej ścieżki
}