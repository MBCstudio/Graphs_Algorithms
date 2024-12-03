//
// Created by cinek on 03.06.2024.
//

#ifndef GRAFY_1_DIJKSTRAALGORITHM_H
#define GRAFY_1_DIJKSTRAALGORITHM_H

#include "Graph.h"
#include <vector>

class DijkstraAlgorithm {
public:
    // Metoda znajdująca najkrótszą ścieżkę w grafie
    // Parametry:
    // - graph: wskaźnik do obiektu klasy Graph reprezentującego graf
    // - startVertex: wierzchołek startowy
    // - endVertex: wierzchołek końcowy
    // - totalCost: referencja do zmiennej przechowującej całkowity koszt najkrótszej ścieżki
    // - verbose: flaga określająca, czy mają być wyświetlane komunikaty diagnostyczne
    // Zwraca:
    // - wektor zawierający wierzchołki na najkrótszej ścieżce od startVertex do endVertex
    std::vector<int> findShortestPath(Graph* graph, int startVertex, int endVertex, int& totalCost, bool verbose);
};


#endif //GRAFY_1_DIJKSTRAALGORITHM_H
