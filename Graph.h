//
// Created by cinek on 29.05.2024.
//

#ifndef GRAFY_1_GRAPH_H
#define GRAFY_1_GRAPH_H


#include <vector>
#include <list>

// Abstrakcyjna klasa bazowa dla reprezentacji grafu
class Graph {
public:
    // Metoda do dodawania krawiedzi
    virtual void addEdge(int u, int v, int weight) = 0;
    virtual void displayList() = 0;
    virtual void displayMatrix() = 0;
    virtual ~Graph() = default; // Wirtualny destruktor
    virtual bool edgeExists(int u, int v) const = 0; // Sprawdzanie czy karwedz istniejie
    virtual void setDirected(bool directed) = 0; // Metoda do sprawdzania czy jest skierownay
    virtual int getVertexCount() const = 0;
    virtual int getEdgeWeight(int u, int v) const = 0;
};

// Klasa do reprezentacji grafu jako macierz incydencji
class AdjacencyMatrixGraph : public Graph {
private:
    int V; // Liczba wierzchołków
    bool directed; // Czy graf jest skierowany
public:
    AdjacencyMatrixGraph(int V, bool directed); // Konstruktor
    void addEdge(int u, int v, int weight) override;
    void displayList() override;
    void displayMatrix() override;
    bool edgeExists(int u, int v) const override;
    void setDirected(bool directed) override;
    int getVertexCount() const override;
    int getEdgeWeight(int u, int v) const override;

    // Macierz sasiedztwa
    std::vector<std::vector<int>> matrix;
};

// Klasa do reprezentacji grafu jako lista sąsiedztwa
class AdjacencyListGraph : public Graph {
private:
    int V;
    bool directed;
public:
    AdjacencyListGraph(int V, bool directed);
    void addEdge(int u, int v, int weight) override;
    void displayList() override;
    void displayMatrix() override;
    bool edgeExists(int u, int v) const override;
    void setDirected(bool directed) override;
    int getVertexCount() const override;
    int getEdgeWeight(int u, int v) const override;

    std::vector<std::vector<std::pair<int, int>>> adjList;
};


#endif //GRAFY_1_GRAPH_H
