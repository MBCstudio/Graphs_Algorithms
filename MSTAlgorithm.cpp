//
// Created by cinek on 02.06.2024.
//

#include "MSTAlgorithm.h"
#include <iostream>
#include <queue>
#include <algorithm>

// Struktura reprezentująca krawędź
struct Edge {
    int u, v, weight;

    // Operator porównania dla sortowania krawędzi według wagi
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Implementacja algorytmu Prima
std::vector<std::pair<int, int>> PrimAlgorithm::findMST(Graph* graph, int startVertex) {
    int V = graph->getVertexCount();
    std::vector<bool> inMST(V, false); // Tablica zaznaczająca wierzchołki w MST
    std::vector<int> key(V, INT_MAX);  // Tablica przechowująca najniższe koszty połączeń
    std::vector<int> parent(V, -1);    // Tablica przechowująca rodziców w MST
    std::vector<std::pair<int, int>> mstEdges; // Wynikowy wektor krawędzi MST

    auto compare = [](std::pair<int, int> left, std::pair<int, int> right) { return left.second > right.second; };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(compare)> pq(compare);

    key[startVertex] = 0;
    pq.push({startVertex, 0});

    while (!pq.empty()) {
        int u = pq.top().first;
        pq.pop();

        inMST[u] = true;

        for (int v = 0; v < V; ++v) {
            if (graph->edgeExists(u, v) && !inMST[v] && graph->getEdgeWeight(u, v) < key[v]) {
                key[v] = graph->getEdgeWeight(u, v);
                pq.push({v, key[v]});
                parent[v] = u;
            }
        }
    }

    for (int v = 1; v < V; ++v) {
        if (parent[v] != -1) {
            mstEdges.emplace_back(parent[v], v);
        }
    }

    return mstEdges;
}

// Klasa pomocnicza do implementacji algorytmu Kruskala
class DisjointSet {
public:
    // Konstruktor inicjalizujący struktury rodziców i rang
    DisjointSet(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    // Znajdowanie reprezentanta zbioru z kompresją ścieżki
    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    // Łączenie dwóch zbiorów
    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else {
                parent[rootV] = rootU;
                ++rank[rootU];
            }
        }
    }

private:
    std::vector<int> parent; // Rodzic każdego elementu
    std::vector<int> rank;   // Ranga każdego elementu
};

// Implementacja algorytmu Kruskala
std::vector<std::pair<int, int>> KruskalAlgorithm::findMST(Graph* graph, int /*startVertex*/) {
    int V = graph->getVertexCount();
    std::vector<Edge> edges;

    // Zbieranie wszystkich krawędzi grafu
    for (int u = 0; u < V; ++u) {
        for (int v = u + 1; v < V; ++v) {
            if (graph->edgeExists(u, v)) {
                edges.push_back({u, v, graph->getEdgeWeight(u, v)});
            }
        }
    }

    // Sortowanie krawędzi według wagi
    std::sort(edges.begin(), edges.end());

    DisjointSet ds(V);
    std::vector<std::pair<int, int>> mstEdges;

    // Iterowanie przez posortowane krawędzie i dodawanie ich do MST jeśli nie tworzą cyklu
    for (const auto& edge : edges) {
        if (ds.find(edge.u) != ds.find(edge.v)) {
            mstEdges.emplace_back(edge.u, edge.v);
            ds.unite(edge.u, edge.v);
        }
    }

    return mstEdges;
}

