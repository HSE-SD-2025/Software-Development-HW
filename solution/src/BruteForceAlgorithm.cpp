#include "BruteForceAlgorithm.h"
#include <climits>

std::vector<Vertex> BruteForceAlgorithm::find_shortest_path(
  const Graph &graph,
  const Vertex &start,
  const Vertex &end) {
  std::vector<std::vector<Edge> > allPaths;
  std::vector<Edge> currentPath;
  std::unordered_map<Vertex, bool> visited;
  for (const auto &vertex: graph.get_vertices()) {
    visited[vertex] = false;
  }
  findAllPaths(graph, start, end, currentPath, visited, allPaths);
  if (allPaths.empty()) {
    return {};
  }
  int minDist = INT_MAX;
  std::vector<Vertex> minPath;
  for (const auto &path: allPaths) {
    int currentDist = 0;
    for (const auto &edge: path) {
      currentDist += edge.get_weight();
    }
    if (currentDist < minDist) {
      minDist = currentDist;
      minPath.clear();
      minPath.push_back(path[0].get_source());
      for (const auto &edge: path) {
        minPath.push_back(edge.get_destination());
      }
    }
  }
  return minPath;
}

void BruteForceAlgorithm::findAllPaths(const Graph &graph,
                                       const Vertex &current,
                                       const Vertex &end,
                                       std::vector<Edge> &currentPath,
                                       std::unordered_map<Vertex, bool> &visited,
                                       std::vector<std::vector<Edge> > &allPaths) {
  visited[current] = true;
  if (current == end) {
    allPaths.push_back(currentPath);
  } else {
    std::vector<Edge> neighbor_edges = graph.get_outgoing_edges(current);
    for (const auto &neighbor: neighbor_edges) {
      if (!visited[neighbor.get_destination()]) {
        currentPath.push_back(neighbor);
        findAllPaths(graph, neighbor.get_destination(), end, currentPath, visited, allPaths);
        currentPath.pop_back();
      }
    }
  }
  visited[current] = false;
}
