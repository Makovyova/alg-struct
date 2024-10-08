#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

//using namespace std;

// Функция минимального из двух integers
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Диаметр графа
void calculateDiameter(std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                }
            }
        }
    }
    int max = graph[0][1];
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] > max) {
                max = graph[i][j];
            }
        }
    }
    std::cout << "Diameter - " << max << std::endl;
}

// Радиус графа с заданной вершиной
void calculateRadius(std::vector<std::vector<int>>& graph, int vertex) {
    int n = graph.size();
    int min = graph[vertex][vertex + 1];
    for (int j = vertex + 1; j < n; j++) {
        if (graph[vertex][j] < min) {
            min = graph[vertex][j];
        }
    }
    std::cout << "Radius for " << vertex << " - " << min << std::endl;
}
//Сортировка графа
void insertionSort(std::vector<std::vector<int>>& graph ) {
    int n = graph.size();
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && graph[j - 1] > graph[j]; j--) {
            std::swap(graph[j - 1], graph[j]);
        }       
    }
}
//Вывод графа
void printGraph(std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    std::cout << "Graph:" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == std::numeric_limits<int>::max()) {
                std::cout << "INF ";
            }
            else {
                std::cout << graph[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    int numVertices;
    std::cout << "Enter the number of vertices: ";
    std::cin >> numVertices;

    std::vector<std::vector<int>> graph(numVertices, std::vector<int>(numVertices, std::numeric_limits<int>::max()));

    for (int i = 0; i < numVertices; i++) {
        while (true) {
            int adjacentVertex;
            std::cout << "Enter the adjacent vertex for vertex " << i << " (or -1 to exit): ";
            std::cin >> adjacentVertex;
            if (adjacentVertex == -1) {
                break;
            }
            int weight;
            std::cout << "Enter the weight of the edge: ";
            std::cin >> weight;
            graph[i][adjacentVertex] = weight;
        }
    }

    calculateDiameter(graph);
    /*
    for (int i = 0; i < numVertices; i++) {
        calculateRadius(graph, i);
    }*/

    while (true) {
        int startVertex, endVertex;
        std::cout << "Enter the start vertex: ";
        std::cin >> startVertex;
        std::cout << "Enter the end vertex: ";
        std::cin >> endVertex;
        std::cout << "Shortest path from " << startVertex << " to " << endVertex << ": " << graph[startVertex][endVertex] << std::endl;
        std::cout << "Do you want to continue? (1 - yes, 0 - no): ";
        int response;
        std::cin >> response;
        if (response == 0) {
            break;
        }
    }
    printGraph(graph);
    insertionSort(graph);
    printGraph(graph);
    return 0;
}