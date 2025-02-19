#include "Graph.h"
#include <stdexcept>
Vertex::Vertex(int id, const std::string &name) : id(id), name(name) {
}

bool Vertex::operator==(const Vertex &other) const {
  return id == other.id;
}
bool Vertex::operator!=(const Vertex &other) const {
  return id != other.id;
}
int Vertex::get_id() const {
  return id;
}

std::string Vertex::get_name() const {
  return name;
}

Edge::Edge(Vertex source, Vertex destination, int weight)
  : source(std::move(source)), destination(std::move(destination)), weight(weight) {
}

Vertex Edge::get_source() const {
  return source;
}

Vertex Edge::get_destination() const {
  return destination;
}

int Edge::get_weight() const {
  return weight;
}

void Graph::add_vertex(const Vertex &vertex) {
  vertices.push_back(vertex);
  vertex_map[vertex] = std::vector<Edge>();
}

void Graph::add_edge(const Edge &edge) {
  edges.push_back(edge);
  vertex_map[edge.get_source()].push_back(edge);
}

const std::vector<Vertex> &Graph::get_vertices() const {
  return vertices;
}

const std::vector<Edge> &Graph::get_edges() const {
  return edges;
}

std::vector<Vertex> Graph::get_neighbors(const Vertex &vertex) const {
  std::vector<Vertex> neighbors;
  for (const auto &edge: vertex_map.at(vertex)) {
    if (edge.get_source() == vertex) {
      neighbors.push_back(edge.get_destination());
    }
  }
  return neighbors;
}
std::vector<Edge> Graph::get_neighbor_edges(const Vertex &vertex) const {
  return vertex_map.at(vertex);
}

size_t std::hash<Vertex>::operator()(const Vertex &v) const noexcept {
  return hash<int>()(v.get_id()) ^ hash<string>()(v.get_name());
}
