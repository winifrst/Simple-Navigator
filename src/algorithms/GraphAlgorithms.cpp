#include "GraphAlgorithms.hpp"

#include <limits>

const long long INF = std::numeric_limits<long long>::max();
const int INF_INT = std::numeric_limits<int>::max();

long long GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph,
                                                          int vertex1,
                                                          int vertex2) {
  int vertices_count = graph.GetVerticesCount();

  if (vertex1 < 1 || vertex2 < 1 || vertex1 > vertices_count ||
      vertex2 > vertices_count) {
    throw std::out_of_range("Vertex index is out of range.");
  }
  std::vector<std::vector<int>> adj_matrix = graph.GetAdjacencyMatrix();

  std::vector<long long> dist(vertices_count, INF);
  dist[vertex1 - 1] = 0;
  std::vector<bool> visited(vertices_count, false);

  while (true) {
    int min_vertex = -1;
    long long min_dist = INF;

    for (int i = 0; i < vertices_count; ++i) {
      if (!visited[i] && dist[i] < min_dist) {
        min_dist = dist[i];
        min_vertex = i;
      }
    }
    if (min_vertex == -1) {
      break;
    }
    if (min_vertex == vertex2 - 1) {
      break;
    }

    visited[min_vertex] = true;
    for (int i = 0; i < vertices_count; ++i) {
      if (adj_matrix[min_vertex][i] != 0 && !visited[i]) {
        long long new_dist = dist[min_vertex] + adj_matrix[min_vertex][i];
        if (new_dist < dist[i]) {
          dist[i] = new_dist;
        }
      }
    }
  }
  if (dist[vertex2 - 1] == INF) {
    throw std::runtime_error("No path exists between the vertices.");
  }

  return dist[vertex2 - 1];
}

std::vector<std::vector<int>>
GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph) {
  std::vector<std::vector<int>> adj_matrix = graph.GetAdjacencyMatrix();
  int vertices_count = graph.GetVerticesCount();
  std::vector<std::vector<int>> dist = adj_matrix;

  for (int k = 0; k < vertices_count; ++k) {
    for (int i = 0; i < vertices_count; ++i) {
      for (int j = 0; j < vertices_count; ++j) {
        if (i == j) {
          dist[i][j] = 0;
        } else if (dist[i][k] < INF_INT / 2 && dist[k][j] < INF_INT / 2) {
          dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }
  return dist;
}