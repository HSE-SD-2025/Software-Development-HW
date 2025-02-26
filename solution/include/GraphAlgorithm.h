#ifndef GRAPHALGORITHM_H
#define GRAPHALGORITHM_H

#include "Graph.h"
#include <vector>

class GraphAlgorithm {
  public:
  virtual ~GraphAlgorithm() = default;
  virtual std::vector<Vertex> find_shortest_path(const Graph& graph, const Vertex& start, const Vertex& end) = 0;
};

#endif