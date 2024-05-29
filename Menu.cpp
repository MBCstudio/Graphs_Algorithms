//
// Created by cinek on 29.05.2024.
//

#include "Menu.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

Menu::Menu() : graph(nullptr), currentProblem(NONE) {}

Menu::~Menu() {
    delete graph;
}

void Menu::displayMainMenu() {
    std::cout << "Wybierz problem do rozwiazania:" << std::endl;
    std::cout << "1. Wyznaczanie minimalnego drzewa rozpinajacego (MST)" << std::endl;
    std::cout << "2. Wyznaczanie najkrotszej sciezki w grafie" << std::endl;
    std::cout << "3. Wyjdz" << std::endl;
}

void Menu::displayAlgorithmMenu() {
    std::cout << "1. Wczytaj dane z pliku." << std::endl;
    std::cout << "2. Wygeneruj graf losowo." << std::endl;
    std::cout << "3. Wyswietl graf." << std::endl;
    std::cout << "4. Uruchom Algorytm 1 (Prim/Dijkstra)." << std::endl;
    std::cout << "5. Uruchom Algorytm 2 (Kruskal/Forda-Bellman)." << std::endl;
    std::cout << "6. Powrot do wyboru problemu." << std::endl;
}

void Menu::selectProblem() {
    int choice;
    displayMainMenu();
    std::cin >> choice;

    switch (choice) {
        case 1:
            currentProblem = MST;
            break;
        case 2:
            currentProblem = SHORTEST_PATH;
            break;
        case 3:
            currentProblem = NONE;
            std::cout << "Wychodzenie..." << std::endl;
            break;
        default:
            std::cout << "Nieprawidlowy wybor. Sprobuj ponownie." << std::endl;
            selectProblem();
            break;
    }
}

void Menu::readFromFile() {
    std::string filename;
    std::cout << "Podaj nazwe pliku: ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Nie mozna otworzyc pliku!" << std::endl;
        return;
    }

    int E, V;
    file >> E >> V;

    if (graph) delete graph;
    graph = new AdjacencyListGraph(V); // Change to AdjacencyMatrixGraph if needed

    int u, v, weight;
    for (int i = 0; i < E; ++i) {
        file >> u, v, weight;
        graph->addEdge(u, v, weight);
    }

    file.close();
}

void Menu::generateRandomGraph() {
    int V, density;
    std::cout << "Podaj liczbe wierzcholkow: ";
    std::cin >> V;
    std::cout << "Podaj gestosc grafu (w procentach): ";
    std::cin >> density;

    if (graph) delete graph;
    graph = new AdjacencyListGraph(V); // Change to AdjacencyMatrixGraph if needed

    srand(time(nullptr));

    // Ensure the graph is initially a spanning tree
    std::vector<int> connected(V, 0);
    connected[0] = 1;
    int edgesAdded = 0;
    for (int i = 1; i < V; ++i) {
        int u = rand() % i;
        int v = i;
        int weight = rand() % 100 + 1;
        graph->addEdge(u, v, weight);
        connected[v] = 1;
        edgesAdded++;
    }

    // Calculate additional edges to add based on the desired density
    int maxEdges = V * (V - 1) / 2;
    int desiredEdges = maxEdges * density / 100;
    int additionalEdges = desiredEdges - edgesAdded;

    while (additionalEdges > 0) {
        int u = rand() % V;
        int v = rand() % V;
        if (u != v && !graph->edgeExists(u, v)) {
            int weight = rand() % 100 + 1;
            graph->addEdge(u, v, weight);
            additionalEdges--;
        }
    }
}

void Menu::displayGraph() {
    if (graph) {
        graph->display();
    } else {
        std::cout << "Graf nie jest zdefiniowany." << std::endl;
    }
}

void Menu::runAlgorithm1() {
    if (currentProblem == MST) {
        // Placeholder for Prim's algorithm
        std::cout << "Uruchomiono Algorytm Prim." << std::endl;
    } else if (currentProblem == SHORTEST_PATH) {
        // Placeholder for Dijkstra's algorithm
        std::cout << "Uruchomiono Algorytm Dijkstry." << std::endl;
    }
}

void Menu::runAlgorithm2() {
    if (currentProblem == MST) {
        // Placeholder for Kruskal's algorithm
        std::cout << "Uruchomiono Algorytm Kruskal." << std::endl;
    } else if (currentProblem == SHORTEST_PATH) {
        // Placeholder for Bellman-Ford algorithm
        std::cout << "Uruchomiono Algorytm Forda-Bellmana." << std::endl;
    }
}

void Menu::start() {
    while (currentProblem == NONE) {
        selectProblem();
    }

    int choice;
    do {
        displayAlgorithmMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: readFromFile(); break;
            case 2: generateRandomGraph(); break;
            case 3: displayGraph(); break;
            case 4: runAlgorithm1(); break;
            case 5: runAlgorithm2(); break;
            case 6: selectProblem(); break;
            default: std::cout << "Nieprawidlowy wybor. Sprobuj ponownie." << std::endl; break;
        }
    } while (choice != 6 || currentProblem != NONE);
}
