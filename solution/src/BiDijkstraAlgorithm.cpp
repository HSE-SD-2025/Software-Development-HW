#include "BiDijkstraAlgorithm.h"

#include <limits>
#include <queue>
#include <stdexcept>
#include <algorithm>

struct CompareDistance {
    bool operator()(const std::pair<int, Vertex> &a, const std::pair<int, Vertex> &b) {
        return a.first > b.first;
    }
};

std::vector<Vertex> BiDijkstraAlgorithm::find_shortest_path(const Graph &graph, const Vertex &start, const Vertex &end)
{
    for (const Edge &edge: graph.get_edges()) {
        if (edge.get_weight() < 0) {
            throw std::invalid_argument("Weight cannot be negative");
        }
    }

    std::unordered_map<Vertex, int[2]> distances;
    std::unordered_map<Vertex, Vertex[2]> previous;
    std::priority_queue<std::pair<int, Vertex>, std::vector<std::pair<int, Vertex> >, CompareDistance>
        pq[2];

    for (const auto &vertex: graph.get_vertices()) {
        distances[vertex][0] = std::numeric_limits<int>::max();
        distances[vertex][1] = std::numeric_limits<int>::max();
    }
    distances[start][0] = 0;
    distances[end][1] = 0;

    pq[0].emplace(0, start);
    pq[1].emplace(0, end);

    Vertex middle;

    while (!pq[0].empty() && !pq[1].empty()) {
        Vertex current[2];
        std::vector<int> inds = {0, 1};
        for (size_t i: inds) {
            current[i] = pq[i].top().second;
            pq[i].pop();
        }

        if (current[0].get_id() != -1 && current[0] == current[1]) {
            middle = current[0];
            break;
        }

        std::vector<Vertex> middle_possibilities;
        if (previous[current[0]][1].get_id() != -1) {
            middle_possibilities.push_back(current[0]);
        }
        if (previous[current[1]][0].get_id() != -1) {
            middle_possibilities.push_back(current[1]);
        }
        if (!middle_possibilities.empty()) {
            std::sort(middle_possibilities.begin(), middle_possibilities.end(), [&distances](const auto& lhs, const auto& rhs){
                return distances[lhs][0] + distances[lhs][1] < distances[rhs][0] + distances[rhs][1];
            });
            middle = middle_possibilities.front();
            break;
        }


        for (const auto &neighbor_edge: graph.get_outgoing_edges(current[0])) {
            Vertex neighbor = neighbor_edge.get_destination();
            int weight = neighbor_edge.get_weight();
            int alt = distances[current[0]][0] + weight;
            if (alt < distances[neighbor][0]) {
                distances[neighbor][0] = alt;
                previous[neighbor][0] = current[0];
                pq[0].emplace(alt, neighbor);
            }
        }

        for (const auto &neighbor_edge: graph.get_incoming_edges(current[1])) {
            Vertex neighbor = neighbor_edge.get_source();
            int weight = neighbor_edge.get_weight();
            int alt = distances[current[1]][1] + weight;
            if (alt < distances[neighbor][1]) {
                distances[neighbor][1] = alt;
                previous[neighbor][1] = current[1];
                pq[1].emplace(alt, neighbor);
            }
        }

    }

    if (middle.get_id() == -1) {
        return {};
    }

    std::vector<Vertex> path;

    if (start != middle) {
        for (Vertex at = middle; at != start; at = previous[at][0]) {
            path.push_back(at);
        }
    }
    path.push_back(start); // at this point path == {middle, ..., start}
    std::reverse(path.begin(), path.end());
    if (end != middle) {
        for (Vertex at = previous[middle][1]; at != end; at = previous[at][1]) {
            path.push_back(at);
        }
    }

    path.push_back(end);

    return path;
}