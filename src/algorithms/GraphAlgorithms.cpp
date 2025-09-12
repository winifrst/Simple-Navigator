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
  int vertices_count = graph.GetVerticesCount();
  std::vector<std::vector<int>> dist = graph.GetAdjacencyMatrix();

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
std::vector<std::vector<int>>
GraphAlgorithms::GetLeastSpanningTree(Graph &graph) {
  int vertices_count = graph.GetVerticesCount();
  std::vector<std::vector<int>> adj_matrix = graph.GetAdjacencyMatrix();

  std::vector<bool> in_mst(vertices_count, false);

  std::vector<int> min_edge_weight(vertices_count, INF_INT);
  min_edge_weight[0] = 0;

  std::vector<int> parent(vertices_count, -1);

  for (int i = 0; i < vertices_count - 1; ++i) {
    int min_dist = INF_INT;
    int min_index = -1;
    for (int j = 0; j < vertices_count; ++j) {
      if (!in_mst[j] && min_edge_weight[j] < min_dist) {
        min_dist = min_edge_weight[j];
        min_index = j;
      }
    }
    if (min_index == -1) {
      break;
    }

    in_mst[min_index] = true;
    for (int k = 0; k < vertices_count; ++k) {
      if (adj_matrix[min_index][k] != 0 && !in_mst[k] &&
          adj_matrix[min_index][k] < min_edge_weight[k]) {
        min_edge_weight[k] = adj_matrix[min_index][k];
        parent[k] = min_index;
      }
    }
  }

  std::vector<std::vector<int>> mst_matrix(vertices_count,
                                           std::vector<int>(vertices_count, 0));

  for (int i = 1; i < vertices_count; ++i) {
    if (parent[i] != -1) {
      int weight = adj_matrix[i][parent[i]];
      mst_matrix[i][parent[i]] = weight;
      mst_matrix[parent[i]][i] = weight;
    }
  }
  return mst_matrix;
}
