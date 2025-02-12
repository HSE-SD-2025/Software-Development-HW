#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <unordered_map>

class Vertex {
  int id;
  std::string name;

  public:
    Vertex() : id(-1) {
    }

    Vertex(int id, const std::string &name);
    Vertex(const Vertex &other) = default;
    bool operator==(const Vertex &other) const;
    [[nodiscard]] int get_id() const;
    [[nodiscard]] std::string get_name() const;
    bool operator!=(const Vertex &other) const;
};

class Edge {
  Vertex source;
  Vertex destination;
  int weight;

  public:
    Edge(Vertex source, Vertex destination, int weight);

    [[nodiscard]] Vertex get_source() const;
    [[nodiscard]] Vertex get_destination() const;
    [[nodiscard]] int get_weight() const;
};

class Graph {
  std::vector<Vertex> vertices;
  std::vector<Edge> edges;
  std::unordered_map<Vertex, std::vector<Edge>> vertex_map;

  public:
    [[nodiscard]] const std::vector<Vertex> &get_vertices() const;
    [[nodiscard]] const std::vector<Edge> &get_edges() const;

    void add_vertex(const Vertex &vertex);
    void add_edge(const Edge &edge);
    [[nodiscard]] std::vector<Vertex> get_neighbors(const Vertex &vertex) const;
    [[nodiscard]] std::vector<Edge> get_neighbor_edges(const Vertex &vertex) const;
};
template<>
struct std::hash<Vertex> {
  size_t operator()(const Vertex &v) const noexcept {
    return hash<int>()(v.get_id()) ^ hash<string>()(v.get_name());
  }
};
#endif // GRAPH_H
