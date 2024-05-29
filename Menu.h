//
// Created by cinek on 29.05.2024.
//

#ifndef GRAFY_1_MENU_H
#define GRAFY_1_MENU_H


#include "Graph.h"
#include <string>

enum ProblemType {
    MST,
    SHORTEST_PATH,
    NONE
};

class Menu {
private:
    Graph* graph;
    ProblemType currentProblem;

    void displayMainMenu();
    void displayAlgorithmMenu();
    void selectProblem();
    void readFromFile();
    void generateRandomGraph();
    void displayGraph();
    void runAlgorithm1();
    void runAlgorithm2();
public:
    Menu();
    ~Menu();
    void start();
};

#endif //GRAFY_1_MENU_H
