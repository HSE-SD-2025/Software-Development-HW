#include "doctest.h"
#include "Graph.h"

TEST_CASE("Graph Class") {
  Graph graph;

  Vertex v1(1, "A");
  Vertex v2(2, "B");
  Vertex v3(3, "C");

  graph.add_vertex(v1);
  graph.add_vertex(v2);
  graph.add_vertex(v3);

  graph.add_edge(Edge(v1, v2, 1));
  graph.add_edge(Edge(v2, v3, 2));

  SUBCASE("Vertex Count") {
    CHECK(graph.get_vertices().size() == 3);
  }

  SUBCASE("Edge Count") {
    CHECK(graph.get_edges().size() == 2);
  }

  SUBCASE("Neighbors") {
    auto neighbors = graph.get_neighbors(v1);
    CHECK(neighbors.size() == 1);
    CHECK(neighbors[0] == v2);
  }
}