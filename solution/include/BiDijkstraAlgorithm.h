#ifndef BIDIJKSTRAALGORITHM_H
#define BIDIJKSTRAALGORITHM_H
// TODO: change to pragma once across the whole project

#include "GraphAlgorithm.h"
#include <queue>
#include <unordered_map>

class BiDijkstraAlgorithm : public GraphAlgorithm {
  public:
  std::vector<Vertex> find_shortest_path(const Graph& graph, const Vertex& start, const Vertex& end) override;
};

#endif