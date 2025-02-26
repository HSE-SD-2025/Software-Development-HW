#ifndef DIJKSTRAALGORITHM_H
#define DIJKSTRAALGORITHM_H

#include "GraphAlgorithm.h"
#include <queue>
#include <unordered_map>

class DijkstraAlgorithm : public GraphAlgorithm {
  public:
  std::vector<Vertex> find_shortest_path(const Graph& graph, const Vertex& start, const Vertex& end) override;
};

#endif // DIJKSTRAALGORITHM_H