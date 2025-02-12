#ifndef BELLMANFORDALGORITHM_H
#define BELLMANFORDALGORITHM_H

#include "GraphAlgorithm.h"
#include <queue>
#include <unordered_map>

class BellmanFordAlgorithm : public GraphAlgorithm {
  public:
  std::vector<Vertex> find_shortest_path(const Graph& graph, const Vertex& start, const Vertex& end) override;
};

#endif // BELLMANFORDALGORITHM_H
