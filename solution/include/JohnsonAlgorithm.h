#ifndef JOHNSONALGORITHM_H
#define JOHNSONALGORITHM_H
#include "GraphAlgorithm.h"


class JohnsonAlgorithm: public GraphAlgorithm {
  public:
  std::vector<Vertex> find_shortest_path(const Graph& graph, const Vertex& start, const Vertex& end) override;
};



#endif //JOHNSONALGORITHM_H
