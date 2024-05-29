//
// Created by cinek on 29.05.2024.
//

#ifndef GRAFY_1_GRAPH_H
#define GRAFY_1_GRAPH_H


#include <vector>

class Graph {
public:
    virtual void addEdge(int u, int v, int weight) = 0;
    virtual void display() = 0;
    virtual ~Graph() = default;
    virtual bool edgeExists(int u, int v) const = 0;
};

class AdjacencyMatrixGraph : public Graph {
private:
    int V;
    std::vector<std::vector<int>> matrix;
public:
    AdjacencyMatrixGraph(int V);
    void addEdge(int u, int v, int weight) override;
    void display() override;
};

class AdjacencyListGraph : public Graph {
private:
    int V;
    std::vector<std::vector<std::pair<int, int>>> adjList;
public:
    AdjacencyListGraph(int V);
    void addEdge(int u, int v, int weight) override;
    void display() override;
    bool edgeExists(int u, int v) const override;
};


#endif //GRAFY_1_GRAPH_H
