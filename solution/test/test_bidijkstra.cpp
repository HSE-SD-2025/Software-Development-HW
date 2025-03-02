#include "BiDijkstraAlgorithm.h"
#include "doctest.h"

TEST_CASE("Bidirectional Dijkstra Algorithm") {
  Graph graph;

  Vertex v1(1, "A");
  Vertex v2(2, "B");
  Vertex v3(3, "C");
  Vertex v4(4, "D");

  graph.add_vertex(v1);
  graph.add_vertex(v2);
  graph.add_vertex(v3);
  graph.add_vertex(v4);

  graph.add_edge(Edge(v1, v2, 1));
  graph.add_edge(Edge(v2, v3, 2));
  graph.add_edge(Edge(v3, v4, 3));
  graph.add_edge(Edge(v1, v4, 10));

  BiDijkstraAlgorithm bidijkstra;

  SUBCASE("Shortest Path A to D") {
    auto path = bidijkstra.find_shortest_path(graph, v1, v4);
    CHECK(path.size() == 4);
    CHECK(path[0].get_name() == "A");
    CHECK(path[1].get_name() == "B");
    CHECK(path[2].get_name() == "C");
    CHECK(path[3].get_name() == "D");
  }

  SUBCASE("Shortest Path A to C") {
    auto path = bidijkstra.find_shortest_path(graph, v1, v3);
    CHECK(path.size() == 3);
    CHECK(path[0].get_name() == "A");
    CHECK(path[1].get_name() == "B");
    CHECK(path[2].get_name() == "C");
  }
}