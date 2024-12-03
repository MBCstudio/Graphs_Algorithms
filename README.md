# Graph Algorithms Application

This application implements and compares key graph algorithms, focusing on solving **Minimum Spanning Tree (MST)** and **Shortest Path** problems. The application offers two modes: single-use for solving specific graph problems and test mode for benchmarking algorithm efficiency under various conditions.

---

## Features

### Algorithms Implemented:
1. **Minimum Spanning Tree (MST)**:
   - **Kruskal's Algorithm**: Utilizes a union-find data structure for efficient edge management. Complexity: `O(E log E)`.
   - **Prim's Algorithm**: Employs a priority queue to iteratively build the MST. Complexity: `O(E + V log V)`.
2. **Shortest Path**:
   - **Dijkstra's Algorithm**: Calculates shortest paths from a single source with non-negative edge weights. Complexity: `O((V + E) log V)`.
   - **Bellman-Ford Algorithm**: Handles graphs with negative edge weights and detects negative weight cycles. Complexity: `O(VE)`.

### Two Operational Modes:
1. **Single Use Mode**:
   - Solve a single graph problem with a step-by-step demonstration.
   - Input graph data manually or load from a file.
2. **Test Mode**:
   - Benchmark algorithms on multiple graphs of varying sizes and densities.
   - Compare execution times and performance metrics.

---

## Graph Representation

- **Adjacency List**: Efficient for sparse graphs, offering reduced memory usage.
- **Adjacency Matrix**: Suitable for dense graphs, providing faster edge lookups.

---

## Technologies Used

- **Java**: Core programming language.
- **Swing**: For graphical user interface (GUI).

---

## How to Run

1. **Clone the Repository**:
   ```bash
   git clone <repository_url>
   cd <repository_directory>
