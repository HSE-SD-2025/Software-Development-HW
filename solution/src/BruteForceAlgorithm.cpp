#include "BruteForceAlgorithm.h"

std::vector<Vertex> BruteForceAlgorithm::find_shortest_path(const Graph& graph, const Vertex& start, const Vertex& end) {
  std::vector<std::vector<Vertex>> allPaths;
  std::vector<Vertex> currentPath;
  std::unordered_map<Vertex, bool> visited;
  for (const auto& vertex : graph.get_vertices()) {
    visited[vertex] = false;
  }
  findAllPaths(graph, start, end, currentPath, visited, allPaths);
  if (allPaths.empty()) {
    return {};
  }
  std::vector<Vertex> shortestPath = allPaths[0];
  for (const auto& path : allPaths) {
    if (path.size() < shortestPath.size()) {
      shortestPath = path;
    }
  }
  return shortestPath;
}

void BruteForceAlgorithm::findAllPaths(const Graph& graph, const Vertex& current, const Vertex& end,
                                         std::vector<Edge>& currentPath, std::unordered_map<Vertex, bool>& visited,
                                         std::vector<std::vector<Edge>>& allPaths) {
  visited[current] = true;
  if (current == end) {
    allPaths.push_back(currentPath);
  } else {
    std::vector<Edge> neighbor_edges = graph.get_neighbor_edges(current);
    for (const auto& neighbor : neighbor_edges) {
      if (!visited[neighbor.get_destination()]) {
        findAllPaths(graph, neighbor.get_destination(), end, currentPath, visited, allPaths);
      }
    }
  }
  visited[current] = false;
  currentPath.pop_back();
}

std::vector<Vertex> BruteForceAlgorithm::getNeighbors(const Graph& graph, const Vertex& vertex) const {
  return
}