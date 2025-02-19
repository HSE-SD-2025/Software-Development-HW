#include "JohnsonAlgorithm.h"
#include "Graph.h"
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

    JohnsonAlgorithm johnson;

    SUBCASE("Shortest Path A to D") {
        auto path = johnson.find_shortest_path(graph, v1, v4);
        REQUIRE(path.size() > 0);
        CHECK(path.size() == 3);
        CHECK(path[0].get_name() == "A");
        CHECK(path[1].get_name() == "B");
        CHECK(path[2].get_name() == "D");
    }

    SUBCASE("Shortest Path A to C") {
        auto path = johnson.find_shortest_path(graph, v1, v3);
        REQUIRE(path.size() > 0);
        CHECK(path.size() == 3);
        CHECK(path[0].get_name() == "A");
        CHECK(path[1].get_name() == "B");
        CHECK(path[2].get_name() == "C");
    }

    SUBCASE("Shortest Path B to D") {
        auto path = johnson.find_shortest_path(graph, v2, v4);
        REQUIRE(path.size() > 0);
        CHECK(path.size() == 2);
        CHECK(path[0].get_name() == "B");
        CHECK(path[1].get_name() == "D");
    }

    SUBCASE("No Path Test (D to A)") {
        auto path = johnson.find_shortest_path(graph, v4, v1);
        CHECK(path.empty());
    }

    SUBCASE("Graph with Negative Weights (No Negative Cycles)") {
        Graph graphWithNegWeights;
        graphWithNegWeights.add_vertex(v1);
        graphWithNegWeights.add_vertex(v2);
        graphWithNegWeights.add_vertex(v3);

        graphWithNegWeights.add_edge(Edge(v1, v2, 1));
        graphWithNegWeights.add_edge(Edge(v2, v3, -2));
        graphWithNegWeights.add_edge(Edge(v1, v3, 4));

        auto path = johnson.find_shortest_path(graphWithNegWeights, v1, v3);
        REQUIRE(path.size() > 0);
        CHECK(path.size() == 3);
        CHECK(path[0].get_name() == "A");
        CHECK(path[1].get_name() == "B");
        CHECK(path[2].get_name() == "C");
    }

    SUBCASE("Graph with Negative Weight Cycle (Should Throw Exception)") {
        Graph graphWithNegCycle;
        graphWithNegCycle.add_vertex(v1);
        graphWithNegCycle.add_vertex(v2);
        graphWithNegCycle.add_vertex(v3);

        graphWithNegCycle.add_edge(Edge(v1, v2, 1));
        graphWithNegCycle.add_edge(Edge(v2, v3, -2));
        graphWithNegCycle.add_edge(Edge(v3, v1, -1));

        CHECK_THROWS_AS(johnson.find_shortest_path(graphWithNegCycle, v1, v3), std::runtime_error);
    }

    SUBCASE("Disconnected Graph") {
        Graph disconnectedGraph;
        disconnectedGraph.add_vertex(v1);
        disconnectedGraph.add_vertex(v2);
        disconnectedGraph.add_vertex(v3);
        disconnectedGraph.add_vertex(v4);

        disconnectedGraph.add_edge(Edge(v1, v2, 1));
        disconnectedGraph.add_edge(Edge(v3, v4, 2));

        auto path = johnson.find_shortest_path(disconnectedGraph, v1, v4);
        CHECK(path.empty());
    }

    SUBCASE("Single Vertex Graph") {
        Graph singleVertexGraph;
        singleVertexGraph.add_vertex(v1);

        auto path = johnson.find_shortest_path(singleVertexGraph, v1, v1);
        REQUIRE(path.size() == 1);
        CHECK(path[0].get_name() == "A");
    }
}