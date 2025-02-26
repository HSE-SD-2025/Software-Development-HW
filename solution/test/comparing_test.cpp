#include <iostream>
#include <chrono>
#include <vector>
#include <limits>
#include "AStarAlgorithm.h"
#include "DijkstraAlgorithm.h"
#include "BellmanFordAlgorithm.h"
#include "BruteForceAlgorithm.h"
#include <typeinfo>

#define time_point std::chrono::time_point<std::chrono::high_resolution_clock>

struct Benchmark {
    std::pair<time_point, time_point> track_execution_time(Graph graph, Vertex source, Vertex destination, GraphAlgorithm& algo) {
        auto start_time = std::chrono::high_resolution_clock::now();

        std::vector<Vertex> path = algo.find_shortest_path(graph, source, destination);
        
        auto end_time = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end_time - start_time;

        std::cout << typeid(algo).name();

        std::cout << "\nExecution time: " << duration.count() << " seconds" << std::endl;

        return {start_time, end_time};
    }
};

int main() {
    Graph graph;

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

    DijkstraAlgorithm dijkstra;

    benchmark.track_execution_time(graph, vertex0, vertex3, dijkstra);

    AStarAlgorithm astar;

    benchmark.track_execution_time(graph, vertex0, vertex3, astar);

    BruteForceAlgorithm bruteForce;

    benchmark.track_execution_time(graph, vertex0, vertex3, bruteForce);

    BellmanFordAlgorithm bellmanford;

    benchmark.track_execution_time(graph, vertex0, vertex3, bellmanford);

    

    return 0;
}
