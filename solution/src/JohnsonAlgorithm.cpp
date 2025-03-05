#include "JohnsonAlgorithm.h"
#include "DijkstraAlgorithm.h"
#include "BellmanFordAlgorithm.h"
#include <limits>
#include <unordered_map>
#include <algorithm>
#include <iostream>

std::vector<Vertex> JohnsonAlgorithm::find_shortest_path(const Graph &graph,
                                                         const Vertex &start,
                                                         const Vertex &end) {
  Graph modifiedGraph = graph;
  Vertex newVertex(-1, "NewVertex");
  modifiedGraph.add_vertex(newVertex);
  for (const auto &vertex: graph.get_vertices()) {
    modifiedGraph.add_edge(Edge(newVertex, vertex, 0));
  }
  BellmanFordAlgorithm bellmanFord;
  std::unordered_map<Vertex, int> potentials;

  for (const auto &vertex: modifiedGraph.get_vertices()) {
    auto path = bellmanFord.find_shortest_path(modifiedGraph, newVertex, vertex);
    if (!path.empty()) {
      potentials[vertex] = 0;
      for (size_t i = 0; i < path.size() - 1; ++i) {
        const auto &edge = modifiedGraph.get_edge_between(path[i], path[i + 1]);
        potentials[vertex] += edge.get_weight();
      }
    } else {
      potentials[vertex] = std::numeric_limits<int>::max();
    }
  }
  Graph reweightedGraph;
  for (const auto &vertex: graph.get_vertices()) {
    reweightedGraph.add_vertex(vertex);
  }
  for (const auto &edge: graph.get_edges()) {
    int reweightedWeight = edge.get_weight() + potentials[edge.get_source()] - potentials[edge.
      get_destination()];
    reweightedGraph.add_edge(Edge(edge.get_source(), edge.get_destination(), reweightedWeight));
  }
  DijkstraAlgorithm dijkstra;
  std::vector<Vertex> path = dijkstra.find_shortest_path(reweightedGraph, start, end);
  return path;
}
