#include "DijkstraAlgorithm.h"
#include <limits>
#include <queue>
#include <unordered_map>
#include <algorithm>

struct CompareDistance {
  bool operator()(const std::pair<int, Vertex>& a, const std::pair<int, Vertex>& b) {
    return a.first > b.first;
  }
};

std::vector<Vertex> DijkstraAlgorithm::find_shortest_path(const Graph& graph, const Vertex& start, const Vertex& end) {
  std::unordered_map<Vertex, int> distances;
  std::unordered_map<Vertex, Vertex> previous;
  std::priority_queue<std::pair<int, Vertex>, std::vector<std::pair<int, Vertex>>, CompareDistance> pq;

  for (const auto& vertex : graph.get_vertices()) {
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

    for (const auto& neighbor_edge : graph.get_neighbor_edges(current)) {
      int weight = -1;
      int alt = distances[current] + weight;
      if (alt < distances[neighbor_edge.get_destination()]) {
        distances[neighbor_edge.get_destination()] = alt;
        previous[neighbor_edge.get_destination()] = current;
        pq.emplace(alt, neighbor_edge.get_destination());
      }
    }
  }

  std::vector<Vertex> path;
  for (Vertex at = end; at != start; at = previous[at]) {
    path.push_back(at);
  }
  path.push_back(start);
  std::reverse(path.begin(), path.end());

  return path;
}