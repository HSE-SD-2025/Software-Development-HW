#include <iostream>
#include <chrono>
#include <vector>
#include <limits>
#include <random>  // Необходимо для генерации случайных чисел
#include <cstring>
#include "AStarAlgorithm.h"
#include "DijkstraAlgorithm.h"
#include "BellmanFordAlgorithm.h"
#include "BruteForceAlgorithm.h"
#include "JohnsonAlgorithm.h"
#include <typeinfo>

#define time_point std::chrono::time_point<std::chrono::high_resolution_clock>

struct Benchmark {
    std::pair<time_point, time_point> track_execution_time(Graph graph, Vertex source, Vertex destination, GraphAlgorithm& algo) {
        auto start_time = std::chrono::high_resolution_clock::now();

        std::vector<Vertex> path = algo.find_shortest_path(graph, source, destination);
        
        auto end_time = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end_time - start_time;

        std::string algorithmName = static_cast<std::string>(typeid(algo).name()).substr(2);
        std::cout << algorithmName;

        std::cout << "\nExecution time: " << duration.count() << " seconds" << std::endl;

        return {start_time, end_time};
    }
};

Graph generate_large_graph(int num_vertices, int num_edges, int max_weight) {
    Graph graph;
    std::random_device rd;  // Используется для инициализации генератора
    std::default_random_engine generator(rd());  // Генератор случайных чисел
    std::uniform_int_distribution<int> vertex_distribution(0, num_vertices - 1);
    std::uniform_int_distribution<int> weight_distribution(1, max_weight);

    std::vector<Vertex> vertices;
    for (int i = 0; i < num_vertices; ++i) {
        vertices.emplace_back(i, "Vertex" + std::to_string(i));
        graph.add_vertex(vertices.back());
    }

    for (int i = 0; i < num_edges; ++i) {
        int src_index = vertex_distribution(generator);  // Использование генератора
        int dest_index = vertex_distribution(generator);
        int weight = weight_distribution(generator);

        // Ensure no self-loop
        if (src_index != dest_index) {
            graph.add_edge(Edge(vertices[src_index], vertices[dest_index], weight));
        }
    }

    return graph;
}


int main(int argc, char* argv[]) {
    Graph graph;

    Graph largeGraph = generate_large_graph(1000, 5000, 10);

    Graph veryLargeGraph = generate_large_graph(100000, 500000, 100);

    Vertex vertex0(0, "A"), vertex1(1, "B"), vertex2(2, "C"), vertex3(3, "D");

    graph.add_vertex(vertex0);
    graph.add_vertex(vertex1);
    graph.add_vertex(vertex2);
    graph.add_vertex(vertex3);

    graph.add_edge(Edge(vertex0, vertex1, 1));
    graph.add_edge(Edge(vertex1, vertex2, 1));
    graph.add_edge(Edge(vertex2, vertex3, 2));
    graph.add_edge(Edge(vertex0, vertex3, 4));

    
    Benchmark benchmark;

    if (std::strcmp(argv[1], "Dijkstra") == 0) {
        DijkstraAlgorithm dijkstra;
        benchmark.track_execution_time(graph, vertex0, vertex3, dijkstra);
    } else if (std::strcmp(argv[1], "AStar") == 0) {
        AStarAlgorithm astar;
        benchmark.track_execution_time(graph, vertex0, vertex3, astar);
    } else if (std::strcmp(argv[1], "BruteForce") == 0) {
        BruteForceAlgorithm bruteForce;
        benchmark.track_execution_time(graph, vertex0, vertex3, bruteForce);
    } else if (std::strcmp(argv[1], "BellmanFord") == 0) {
        BellmanFordAlgorithm bellmanford;
        benchmark.track_execution_time(graph, vertex0, vertex3, bellmanford);
    } else if (std::strcmp(argv[1], "Johnson") == 0) {
        JohnsonAlgorithm johnson;
        benchmark.track_execution_time(graph, vertex0, vertex3, johnson);
    } else if (argc > 1) {
        std::cout << "Undefined algorithm with name: " << argv[1];
    } else {
        std::cout << "Need to specify algorithm name";
    }
    return 0;
}
