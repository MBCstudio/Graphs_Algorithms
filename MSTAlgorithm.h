//
// Created by cinek on 02.06.2024.
//

#ifndef GRAFY_1_MSTALGORITHM_H
#define GRAFY_1_MSTALGORITHM_H


#include "Graph.h"
#include <vector>
#include <utility>

// Klasa abstrakcyjna dla algorytmów wyznaczania minimalnego drzewa rozpinającego (MST)
class MSTAlgorithm {
public:
    // Czysto wirtualna funkcja do znalezienia MST
    virtual std::vector<std::pair<int, int>> findMST(Graph* graph, int startVertex) = 0;
    virtual ~MSTAlgorithm() = default; // Destruktor
};

// Klasa dla Prim Algorytmu
class PrimAlgorithm : public MSTAlgorithm {
public:
    // Nadpisanie funkcji findMST dla algorytmu Prima
    std::vector<std::pair<int, int>> findMST(Graph* graph, int startVertex) override;
};

// Klasa dla algorytmu Kruskala
class KruskalAlgorithm : public MSTAlgorithm {
public:
    // Nadpisanie funkcji findMST dla algorytmu Kruskala
    std::vector<std::pair<int, int>> findMST(Graph* graph, int startVertex) override;
};


#endif //GRAFY_1_MSTALGORITHM_H
