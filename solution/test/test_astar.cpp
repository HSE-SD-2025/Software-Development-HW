#include "doctest.h"
#include "AStarAlgorithm.h"
#include "Graph.h"

Graph create_test_graph() {
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

    return graph;
}

TEST_CASE("A* Algorithm Tests") {
    Graph graph = create_test_graph();
    AStarAlgorithm astar;

    SUBCASE("Shortest Path A to C") {
        auto path = astar.find_shortest_path(graph, Vertex(1, "A"), Vertex(3, "C"));
        REQUIRE(path.size() == 3);
        CHECK(path[0].get_name() == "A");
        CHECK(path[1].get_name() == "B");
        CHECK(path[2].get_name() == "C");
    }

    SUBCASE("No Path Test (D to A)") {
        auto path = astar.find_shortest_path(graph, Vertex(4, "D"), Vertex(1, "A"));
        CHECK(path.empty());
    }

    SUBCASE("Start equals End (A to A)") {
        auto path = astar.find_shortest_path(graph, Vertex(1, "A"), Vertex(1, "A"));
        REQUIRE(path.size() == 1);
        CHECK(path[0].get_name() == "A");
    }
}