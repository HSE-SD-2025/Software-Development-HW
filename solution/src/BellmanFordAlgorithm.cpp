#include "BellmanFordAlgorithm.h"
#include <vector>
#include <limits>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>

std::vector<Vertex> BellmanFordAlgorithm::find_shortest_path(const Graph& graph, const Vertex& start, const Vertex& end) {
    std::unordered_map<Vertex, int> distances;
    std::unordered_map<Vertex, Vertex> previous;

    for (const auto& vertex : graph.get_vertices()) {
        distances[vertex] = std::numeric_limits<int>::max();
    }
    distances[start] = 0;

    for (size_t i = 1; i < graph.get_vertices().size(); ++i) {
        for (const auto& edge : graph.get_edges()) {
            Vertex u = edge.get_source();
            Vertex v = edge.get_destination();
            int weight = edge.get_weight();

            if (distances[u] != std::numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
            }
        }
    }

    for (const auto& edge : graph.get_edges()) {
        Vertex u = edge.get_source();
        Vertex v = edge.get_destination();
        int weight = edge.get_weight();

        if (distances[u] != std::numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
            throw std::runtime_error("Graph contains a negative-weight cycle");
        }
    }

    if (distances[end] == std::numeric_limits<int>::max()) {
        return {};
    }

    std::vector<Vertex> path;
    for (Vertex at = end; at != start; at = previous[at]) {
        path.push_back(at);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return path;
}