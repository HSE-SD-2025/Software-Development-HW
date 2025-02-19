#include "DijkstraAlgorithm.h"
#include <limits>
#include <queue>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>

struct CompareDistance {
  bool operator()(const std::pair<int, Vertex> &a, const std::pair<int, Vertex> &b) {
    return a.first > b.first;
  }
};

std::vector<Vertex> DijkstraAlgorithm::find_shortest_path(const Graph &graph,
                                                          const Vertex &start,
                                                          const Vertex &end) {
  for (const Edge &edge: graph.get_edges()) {
    if (edge.get_weight() < 0) {
      throw std::invalid_argument("Weight cannot be negative");
    }
  }

  std::unordered_map<Vertex, int> distances;
  std::unordered_map<Vertex, Vertex> previous;
  std::priority_queue<std::pair<int, Vertex>, std::vector<std::pair<int, Vertex> >, CompareDistance>
      pq;

  for (const auto &vertex: graph.get_vertices()) {
    distances[vertex] = std::numeric_limits<int>::max();
  }
  distances[start] = 0;
  pq.emplace(0, start);

  while (!pq.empty()) {
    Vertex current = pq.top().second;
    pq.pop();

    if (current == end) {
      break;
    }

    for (const auto &neighbor_edge: graph.get_neighbor_edges(current)) {
      Vertex neighbor = neighbor_edge.get_destination();
      int weight = neighbor_edge.get_weight();
      int alt = distances[current] + weight;
      if (alt < distances[neighbor]) {
        distances[neighbor] = alt;
        previous[neighbor] = current;
        pq.emplace(alt, neighbor);
      }
    }
  }

  std::vector<Vertex> path;
  for (Vertex at = end; at != start; at = previous[at]) {
    path.push_back(at);
    if (previous.find(at) == previous.end()) {
      return {};
    }
  }
  path.push_back(start);
  std::reverse(path.begin(), path.end());

  return path;
}
