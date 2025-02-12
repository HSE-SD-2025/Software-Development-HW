#ifndef ASTAR_ALGORITHM_H
#define ASTAR_ALGORITHM_H

#include "Graph.h"
#include <vector>

class AStarAlgorithm {
public:
    std::vector<Vertex> find_shortest_path(const Graph& graph, const Vertex& start, const Vertex& end);
private:
    double heuristic(const Vertex& a, const Vertex& b);
};

#endif // ASTAR_ALGORITHM_H