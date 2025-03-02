#pragma once

#include <vector>
#include <Graph.h>
#include <BellmanFordAlgorithm.h>
#include <DijkstraAlgorithm.h>

class JohnsonAlgorithm : public GraphAlgorithm {
public:
    std::vector<Vertex> find_shortest_path(const Graph& graph, const Vertex& start, const Vertex& finish) override;
};