#ifndef BRUTEFORCEALGORITHM_H
#define BRUTEFORCEALGORITHM_H
#include "GraphAlgorithm.h"
#include <queue>

class BruteForceAlgorithm : public GraphAlgorithm {
  void findAllPaths(const Graph &graph,
                    const Vertex &current,
                    const Vertex &end,
                    std::vector<Edge> &currentPath,
                    std::unordered_map<Vertex, bool> &visited,
                    std::vector<std::vector<Edge>> &allPaths);

  public:
  std::vector<Vertex> find_shortest_path(const Graph& graph, const Vertex& start, const Vertex& end) override;
};
#endif //BRUTEFORCEALGORITHM_H
