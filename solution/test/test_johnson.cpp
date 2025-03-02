#include "JohnsonAlgorithm.h"
#include "doctest.h"

TEST_CASE("Johnson Algorithm") {
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
  graph.add_edge(Edge(v1, v3, 5));
  graph.add_edge(Edge(v2, v4, 1));

  JohnsonAlgorithm johnsonAlgorithm;

  SUBCASE("Shortest Path A to D") {
    auto path = johnsonAlgorithm.find_shortest_path(graph, v1, v4);
    REQUIRE(path.size() > 0);
    CHECK(path.size() == 3);
    CHECK(path[0].get_name() == "A");
    CHECK(path[1].get_name() == "B");
    CHECK(path[2].get_name() == "D");
}

SUBCASE("Shortest Path A to C") {
    auto path = johnsonAlgorithm.find_shortest_path(graph, v1, v3);
    REQUIRE(path.size() > 0);
    CHECK(path.size() == 3);
    CHECK(path[0].get_name() == "A");
    CHECK(path[1].get_name() == "B");
    CHECK(path[2].get_name() == "C");
}

SUBCASE("Shortest Path B to D") {
    auto path = johnsonAlgorithm.find_shortest_path(graph, v2, v4);
    REQUIRE(path.size() > 0);
    CHECK(path.size() == 2);
    CHECK(path[0].get_name() == "B");
    CHECK(path[1].get_name() == "D");
  }

  SUBCASE("No Path Test (D to A)") {
    auto path = johnsonAlgorithm.find_shortest_path(graph, v4, v1);
    CHECK(path.empty());
  }
}
