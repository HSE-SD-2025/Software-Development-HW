#include "AStarAlgorithm.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>

double AStarAlgorithm::heuristic(const Vertex& a, const Vertex& b) {
    // Используем разницу в идентификаторах как простую эвристику
    return std::abs(a.get_id() - b.get_id());
}

std::vector<Vertex> AStarAlgorithm::find_shortest_path(const Graph& graph, const Vertex& start, const Vertex& end) {
    std::unordered_map<Vertex, double> g_score;
    std::unordered_map<Vertex, double> f_score;
    std::unordered_map<Vertex, Vertex> came_from;
    std::unordered_set<Vertex> openSet;
    std::unordered_set<Vertex> closedSet;

    for (const auto& vertex : graph.get_vertices()) {
        g_score[vertex] = std::numeric_limits<double>::infinity();
        f_score[vertex] = std::numeric_limits<double>::infinity();
    }
    g_score[start] = 0.0;
    f_score[start] = heuristic(start, end);
    openSet.insert(start);

    auto cmp = [&f_score](const Vertex& left, const Vertex& right) {
        return f_score.at(left) > f_score.at(right);
    };

    std::priority_queue<Vertex, std::vector<Vertex>, decltype(cmp)> priorityQueue(cmp);
    priorityQueue.push(start);

    while (!priorityQueue.empty()) {
        Vertex current = priorityQueue.top();
        priorityQueue.pop();
        openSet.erase(current);

        if (current == end) {
            std::vector<Vertex> path;
            while (current != start) {
                path.push_back(current);
                current = came_from.at(current);  // Используем .at для безопасности доступа
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        closedSet.insert(current);

        for (const auto& edge : graph.get_neighbor_edges(current)) {
            Vertex neighbor = edge.get_destination();

            if (closedSet.count(neighbor)) {
                continue;  // Если сосед уже обработан, пропускаем
            }

            double tentative_g_score = g_score.at(current) + edge.get_weight();

            if (!openSet.count(neighbor)) {
                openSet.insert(neighbor);
                priorityQueue.push(neighbor);
            } else if (tentative_g_score >= g_score.at(neighbor)) {
                continue;
            }

            // Обновляем пути для лучшего пути
            came_from[neighbor] = current;
            g_score[neighbor] = tentative_g_score;
            f_score[neighbor] = tentative_g_score + heuristic(neighbor, end);
        }
    }

    return {};  // Путь не найден
}