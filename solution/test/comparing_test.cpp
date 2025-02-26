#include <iostream>
#include <chrono>
#include <vector>
#include <limits>
#include "AStarAlgorithm.h"
#include "DijkstraAlgorithm.h"
#include "BellmanFordAlgorithm.h"
#include "BruteForceAlgorithm.h"
#include <typeinfo>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <random>

struct Benchmark {
    void track_execution_time(Graph graph, Vertex source, Vertex destination, GraphAlgorithm& algo) {
        auto start_time = std::chrono::high_resolution_clock::now();

        std::vector<Vertex> path = algo.find_shortest_path(graph, source, destination);
        
        auto end_time = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

        std::string algo_name = typeid(algo).name();
        std::cout << algo_name.substr(2);

        if (algo_name.substr(2) == "AStarAlgorithm") std::cout << '\t';

        std::cout << "\t\texecution time: " << duration.count() << "ms" << std::endl;
    }
};

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

Graph generate_random_graph(int num_vertices, int num_edges, int max_weight = 10) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> weight_dist(1, max_weight);
    std::uniform_int_distribution<> vertex_dist(0, num_vertices - 1);

    Graph graph;
    
    for (int i = 0; i < num_vertices; ++i) {
        graph.add_vertex(Vertex(i, "Vertex_" + std::to_string(i)));
    }

    std::unordered_set<std::pair<int, int>, pair_hash> existing_edges;

    while (graph.get_edges().size() < num_edges) {
        int src_index = vertex_dist(gen);
        int dest_index = vertex_dist(gen);

        if (src_index != dest_index) {
            auto edge_pair = std::minmax(src_index, dest_index);

            if (existing_edges.find(edge_pair) == existing_edges.end()) {
                int weight = weight_dist(gen);
                Vertex src = graph.get_vertices()[src_index];
                Vertex dest = graph.get_vertices()[dest_index];

                graph.add_edge(Edge(src, dest, weight));
                existing_edges.insert(edge_pair);
            }
        }
    }

    return graph;
}

void run_algorithms(Benchmark benchmark, DijkstraAlgorithm& dijkstra, AStarAlgorithm& astar, BruteForceAlgorithm& bruteForce, BellmanFordAlgorithm& bellmanFord) {
    Graph graph = generate_random_graph(15, 15);

    auto source_vertex = graph.get_vertices().front();

    auto target_vertex = graph.get_vertices().back();

    benchmark.track_execution_time(graph, source_vertex, target_vertex, dijkstra);

    benchmark.track_execution_time(graph, source_vertex, target_vertex, astar);

    benchmark.track_execution_time(graph, source_vertex, target_vertex, bruteForce);

    benchmark.track_execution_time(graph, source_vertex, target_vertex, bellmanFord);
}

int main() {
    Benchmark benchmark;

    DijkstraAlgorithm dijkstra;
    AStarAlgorithm astar;
    BruteForceAlgorithm bruteForce;
    BellmanFordAlgorithm bellmanFord;

    std::cout << "Starting comparison test...\n";

    std::cout << "Comparing algorithms: Dijkstra, AStar, BruteForce, BellmanFord\n\n";

    std::cout << "Running algorithms on the first random graph:\n";

    run_algorithms(benchmark, dijkstra, astar, bruteForce, bellmanFord);

    std::cout << "\n\n";

    std::cout << "Running algorithms on the second random graph:\n";

    run_algorithms(benchmark, dijkstra, astar, bruteForce, bellmanFord);

    std::cout << "\n\n";


    std::cout << "Running algorithms on the third random graph:\n";

    run_algorithms(benchmark, dijkstra, astar, bruteForce, bellmanFord);

    std::cout << "Finished comparison test.\n\n";

    return 0;
}
