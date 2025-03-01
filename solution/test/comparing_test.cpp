#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <cstring>
#include "AStarAlgorithm.h"
#include "DijkstraAlgorithm.h"
#include "BellmanFordAlgorithm.h"
#include "BruteForceAlgorithm.h"
#include "JohnsonAlgorithm.h"
#include <typeinfo>
#include <mimalloc.h>
#include <string>

#define time_point std::chrono::time_point<std::chrono::high_resolution_clock>

struct Benchmark {
  std::pair<time_point, time_point > track_execution_time(Graph graph,
                                                          Vertex source,
                                                          Vertex destination,
                                                          GraphAlgorithm &algo) {
    auto start_time = std::chrono::high_resolution_clock::now();

    std::vector<Vertex> path = algo.find_shortest_path(graph, source, destination);

    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end_time - start_time;

    std::string algorithmName = static_cast<std::string>(typeid(algo).name()).substr(2);
    std::cout << algorithmName << '\n';

    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;

    return {start_time, end_time};
  }
};

Graph create_large_graph() {
    Graph graph;
    std::vector<Vertex> vertices;
    for (int i = 0; i < 30; ++i) {
        vertices.emplace_back(i, "V" + std::to_string(i));
        graph.add_vertex(vertices[i]);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> weight_dist(1, 100);

    for (int i = 0; i < 30; ++i) {
        for (int j = i + 1; j < 30; ++j) {
            if (weight_dist(gen) % 4 == 0) { // Randomly connect vertices
                graph.add_edge(Edge(vertices[i], vertices[j], weight_dist(gen)));
            }
        }
    }

    return graph;
}

int main(int argc, char *argv[]) {
  Graph graph;
  bool use_big_graph = false;

  if (argc > 2 && std::strcmp(argv[2], "--big") == 0) {
    use_big_graph = true;
  }

  if (use_big_graph) {
    graph = create_large_graph();
  } else {
    Vertex vertex0(0, "A"), vertex1(1, "B"), vertex2(2, "C"), vertex3(3, "D"), vertex4(4, "E"),
        vertex5(5, "F"), vertex6(6, "G"), vertex7(7, "H");

    graph.add_vertex(vertex0);
    graph.add_vertex(vertex1);
    graph.add_vertex(vertex2);
    graph.add_vertex(vertex3);
    graph.add_vertex(vertex4);
    graph.add_vertex(vertex5);
    graph.add_vertex(vertex6);
    graph.add_vertex(vertex7);

    graph.add_edge(Edge(vertex0, vertex1, 1));
    graph.add_edge(Edge(vertex1, vertex2, 1));
    graph.add_edge(Edge(vertex2, vertex3, 2));
    graph.add_edge(Edge(vertex0, vertex3, 4));
    graph.add_edge(Edge(vertex0, vertex4, 5));
    graph.add_edge(Edge(vertex1, vertex5, 5));
    graph.add_edge(Edge(vertex2, vertex6, 123));
    graph.add_edge(Edge(vertex7, vertex6, 123));
    graph.add_edge(Edge(vertex0, vertex3, 1));
    graph.add_edge(Edge(vertex6, vertex5, 12));
    graph.add_edge(Edge(vertex6, vertex1, 12));
  }

  Benchmark benchmark;

  if (std::strcmp(argv[1], "Dijkstra") == 0) {
    DijkstraAlgorithm dijkstra;
    benchmark.track_execution_time(graph, graph.get_vertices()[0], graph.get_vertices()[3], dijkstra);
  } else if (std::strcmp(argv[1], "AStar") == 0) {
    AStarAlgorithm astar;
    benchmark.track_execution_time(graph, graph.get_vertices()[0], graph.get_vertices()[3], astar);
  } else if (std::strcmp(argv[1], "BruteForce") == 0) {
    BruteForceAlgorithm bruteForce;
    benchmark.track_execution_time(graph, graph.get_vertices()[0], graph.get_vertices()[3], bruteForce);
  } else if (std::strcmp(argv[1], "BellmanFord") == 0) {
    BellmanFordAlgorithm bellmanford;
    benchmark.track_execution_time(graph, graph.get_vertices()[0], graph.get_vertices()[3], bellmanford);
  } else if (std::strcmp(argv[1], "Johnson") == 0) {
    JohnsonAlgorithm johnson;
    benchmark.track_execution_time(graph, graph.get_vertices()[0], graph.get_vertices()[3], johnson);
  } else if (argc > 1) {
    std::cout << "Undefined algorithm with name: " << argv[1];
  } else {
    std::cout << "Need to specify algorithm name";
  }
  mi_stats_print(nullptr);
  return 0;
}