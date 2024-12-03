//
// Created by cinek on 29.05.2024.
//

#ifndef GRAFY_1_MENU_H
#define GRAFY_1_MENU_H


#include "Graph.h"
#include "MSTAlgorithm.h"
#include "DijkstraAlgorithm.h"
#include "FordBellmanAlgorithm.h"
#include <string>

class Menu {
private:
    Graph* graph; // Tworzenie nowego grtafu (wskaznik)
    // Wskażniki do algorytmów
    MSTAlgorithm* primAlgorithm;
    MSTAlgorithm* kruskalAlgorithm;
    DijkstraAlgorithm* dijkstraAlgorithm;
    FordBellmanAlgorithm* fordBellmanAlgorithm;
    enum Problem { NONE, MST, SHORTEST_PATH } currentProblem;

    // Deklaracja funkcji
    void displayMainMenu();
    void displayAlgorithmMenu();
    void selectProblem();
    void readFromFile();
    void generateRandomGraph();
    void displayGraph();
    void runAlgorithm1();
    void runAlgorithm2();
public:
    // Konstruktory i destruktory
    Menu();
    ~Menu();
    void start();
};

#endif //GRAFY_1_MENU_H
