//
// Created by cinek on 29.05.2024.
//

#include "Menu.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

// Konstruktor inicjalizujący wskaźniki i ustawiający bieżący problem na NONE
Menu::Menu() : graph(nullptr), primAlgorithm(new PrimAlgorithm()), kruskalAlgorithm(new KruskalAlgorithm()),
               dijkstraAlgorithm(new DijkstraAlgorithm()), fordBellmanAlgorithm(new FordBellmanAlgorithm()), currentProblem(NONE) {}

// Destruktory, zwalnajace pamiec
Menu::~Menu() {
    delete graph;
    delete primAlgorithm;
    delete kruskalAlgorithm;
    delete dijkstraAlgorithm;
    delete fordBellmanAlgorithm;
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
    std::cout << "4. Uruchom Algorytm 1." << std::endl;
    std::cout << "5. Uruchom Algorytm 2." << std::endl;
    std::cout << "6. Powrot do wyboru problemu." << std::endl;
}

// Funkcja do wyboru porbleum, ktory ma być obsługiwany
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
            return;
            //break;
        default:
            std::cout << "Nieprawidlowy wybor. Sprobuj ponownie." << std::endl;
            selectProblem();
            break;
    }

    // Wybieranie czy graf jest skierowny, jeżeli jest wybor najkrotszej drogi
    if (graph) {
        graph->setDirected(currentProblem == SHORTEST_PATH);
    }
}

// Funkcja do czytania z pliku
void Menu::readFromFile() {
    std::string filename;
    std::cout << "Podaj nazwe pliku: ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Nie mozna otworzyc pliku!" << std::endl;
        return;
    }

    // Zapisywanie krawiedzi i wierzchołkow
    int E, V;
    file >> E >> V;

    //Jezeli graf jest juz stworzony to go usuwa, tworzy nowy
    if (graph) delete graph;
    graph = new AdjacencyListGraph(V, currentProblem == SHORTEST_PATH);

    // Wczytywawnie poszczegolnych karawiedzi
    int u, v, weight;
    for (int i = 0; i < E; ++i) {
        file >> u >> v >> weight;
        graph->addEdge(u, v, weight);
    }

    file.close();
}

// Generowanie losowego grafu
void Menu::generateRandomGraph() {
    int V, density;
    std::cout << "Podaj liczbe wierzcholkow: ";
    std::cin >> V;
    std::cout << "Podaj gestosc grafu (w procentach): ";
    std::cin >> density;

    if (graph) delete graph;
    graph = new AdjacencyListGraph(V, currentProblem == SHORTEST_PATH);

    srand(time(nullptr));

    // Tworzenie początkowego drzewa spinającego
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

    // Dodwanie kolenych krawedzi po utworzeniu drzewa spinajacego
    int maxEdges = V * (V - 1) / 2;
    int desiredEdges = maxEdges * density / 100;
    int additionalEdges = desiredEdges - edgesAdded;

    // Dodawanie 'dodatkowych' krawiedzi do grafu z losowa waga do 100
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

// Wybranie ktora reprezentacja ma byc wybierana
void Menu::displayGraph() {
    std::cout << "Wybierz sposob wyswietlania grafu:" << std::endl;
    std::cout << "1. Listowo" << std::endl;
    std::cout << "2. Macierzowo" << std::endl;

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            graph->displayList();
            break;
        case 2:
            graph->displayMatrix();
            break;
        default:
            std::cout << "Nieprawidlowy wybor." << std::endl;
            break;
    }
}

// Uruchamienie 1 algorytmu (Prim lub Dijkstra)
void Menu::runAlgorithm1() {
    if (currentProblem == MST) {
        //std::cout << "Podaj wierzcholek startowy: ";
        int startVertex = 0;
        //std::cin >> startVertex;

        auto result = primAlgorithm->findMST(graph, startVertex);
        std::cout << "Algorytm Prima wyznaczyl nastepujace krawedzie MST (Reprezentacja macierzowa):" << std::endl;
        for (const auto& edge : result) {
            std::cout << edge.first << " - " << edge.second <<std::endl;
        }

        std::cout << "Algorytm Prima wyznaczyl nastepujace krawedzie MST (Reprezentacja listowa):" << std::endl;
        for (const auto& edge : result) {
            std::cout << edge.first << " - " << edge.second << std::endl;
        }
    } else if (currentProblem == SHORTEST_PATH) {
        std::cout << "Podaj wierzcholek startowy: ";
        int startVertex;
        std::cin >> startVertex;
        std::cout << "Podaj wierzcholek koncowy: ";
        int endVertex;
        std::cin >> endVertex;

        int totalCost;
        auto path = dijkstraAlgorithm->findShortestPath(graph, startVertex, endVertex, totalCost, true);
        std::cout << "Algorytm Dijkstry wyznaczyl najkrotsza sciezke (Reprezentacja listowa):" << std::endl;
        for (int vertex : path) {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
        std::cout << "Calkowity koszt: " << totalCost << std::endl;

        path = dijkstraAlgorithm->findShortestPath(graph, startVertex, endVertex, totalCost, false);
        std::cout << "Algorytm Dijkstry wyznaczyl najkrotsza sciezke (Reprezentacja macierzowa):" << std::endl;
        for (int vertex : path) {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
        std::cout << "Calkowity koszt: " << totalCost << std::endl;
    }
}

// Uruchamienie 2 algorytmu (Kruskal lub Ford-Bellman)
void Menu::runAlgorithm2() {
    if (currentProblem == MST) {
        //std::cout << "Podaj wierzcholek startowy: ";
        int startVertex = 0;
        //std::cin >> startVertex;

        auto result = kruskalAlgorithm->findMST(graph, startVertex);
        std::cout << "Algorytm Kruskala wyznaczyl nastepujace krawedzie MST (Reprezentacja macierzowa):" << std::endl;
        for (const auto& edge : result) {
            std::cout << edge.first << " - " << edge.second << std::endl;
        }

        std::cout << "Algorytm Kruskala wyznaczyl nastepujace krawedzie MST (Reprezentacja listowa):" << std::endl;
        for (const auto& edge : result) {
            std::cout << edge.first << " - " << edge.second << std::endl;
        }

    } else if (currentProblem == SHORTEST_PATH) {
        std::cout << "Podaj wierzcholek startowy: ";
        int startVertex;
        std::cin >> startVertex;
        std::cout << "Podaj wierzcholek koncowy: ";
        int endVertex;
        std::cin >> endVertex;

        int totalCost;
        auto path = fordBellmanAlgorithm->findShortestPath(graph, startVertex, endVertex, totalCost, true);
        std::cout << "Algorytm Forda-Bellmana wyznaczyl najkrotsza sciezke (Reprezentacja listowa):" << std::endl;
        for (int vertex : path) {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
        std::cout << "Calkowity koszt: " << totalCost << std::endl;

        path = fordBellmanAlgorithm->findShortestPath(graph, startVertex, endVertex, totalCost, false);
        std::cout << "Algorytm Forda-Bellmana wyznaczyl najkrotsza sciezke (Reprezentacja macierzowa):" << std::endl;
        for (int vertex : path) {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
        std::cout << "Calkowity koszt: " << totalCost << std::endl;
    }
}

// Petla głowna programu
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
