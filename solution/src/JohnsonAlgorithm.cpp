#include <JohnsonAlgorithm.h>
#include <climits>

std::vector<Vertex> JohnsonAlgorithm::find_shortest_path(const Graph& graph_, const Vertex& start, const Vertex& finish) {
    Graph graph = graph_;
    const auto& vertixes = graph.get_vertices();
    
    BellmanFordAlgorithm bellmanFordAlgorithm;
    std::vector<std::vector<Vertex>> paths;
    for (const auto& v : vertixes)
    paths.push_back(bellmanFordAlgorithm.find_shortest_path(graph, start, v));

    std::unordered_map<Vertex, int> path_distances;
    for (const auto& path : paths) {
        long long int sum = 0;
        for (int i = 0; i < (int) path.size() - 1; ++i)
            sum += graph.get_edge_between(path[i], path[i + 1]).get_weight();
        if (!path.empty()) path_distances[path.back()] = sum;
    }
    
    Graph new_graph;
    const auto& edges = graph.get_edges();
    for (const auto& v : vertixes) {
        for (const auto& edge : graph.get_neighbor_edges(v)) {
            int new_weight = edge.get_weight() + path_distances[v] - path_distances[edge.get_destination()];
            new_graph.add_edge(Edge(v, edge.get_destination(), edge.get_weight()));
        }
    }

    DijkstraAlgorithm dijkstraAlgorithm;
    return dijkstraAlgorithm.find_shortest_path(graph, start, finish);
}