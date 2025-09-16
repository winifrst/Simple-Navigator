#include "GraphAlgorithms.hpp"

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

std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                     int start_vertex) {
  std::vector<int> result;

  if (start_vertex < 0 || start_vertex >= graph.GetVerticesCount() ||
      graph.GetAdjacencyMatrix().empty() || graph.GetVerticesCount() <= 0) {
    return result;
  }

  std::vector<bool> visited(graph.GetVerticesCount(), false);
  Queue<int> grays;

  grays.Push(start_vertex);
  visited[start_vertex] = true;

  while (!grays.Empty()) {
    int current_vertex = grays.Pop();
    result.push_back(current_vertex);

    GetBreadthNeighbors(graph.GetAdjacencyMatrix(), current_vertex, grays,
                        visited);
  }

  return result;
}

void GraphAlgorithms::GetBreadthNeighbors(
    const std::vector<std::vector<int>> &adjacencyMatrix, int current_vertex,
    Queue<int> &grays, std::vector<bool> &visited) {
  int size = adjacencyMatrix.size();
  if (current_vertex < 0 || current_vertex >= size) {
    return;
  }

  for (int j = 0; j < size; j++) {
    if (adjacencyMatrix[current_vertex][j] != 0 && !visited[j]) {
      grays.Push(j);
      visited[j] = true;
    }
  }
}

std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph,
                                                   int start_vertex) {
  std::vector<int> result;
  if (start_vertex < 0 || start_vertex >= graph.GetVerticesCount() ||
      graph.GetAdjacencyMatrix().empty() || graph.GetVerticesCount() <= 0) {
    return result;
  }

  std::vector<bool> visited(graph.GetVerticesCount(), false);
  Stack<int> grays;

  grays.Push(start_vertex);

  while (!grays.Empty()) {
    int current_vertex = grays.Pop();

    if (!visited[current_vertex]) {
      visited[current_vertex] = true;
      result.push_back(current_vertex);

      GetDepthNeighbors(graph.GetAdjacencyMatrix(), current_vertex, grays,
                        visited);
    }
  }

  return result;
}

void GraphAlgorithms::GetDepthNeighbors(
    const std::vector<std::vector<int>> &adjacencyMatrix, int current_vertex,
    Stack<int> &grays, std::vector<bool> &visited) {
  int size = adjacencyMatrix.size();
  if (current_vertex < 0 || current_vertex >= size) {
    return;
  }

  for (int j = size - 1; j >= 0; j--) {
    if (adjacencyMatrix[current_vertex][j] != 0 && !visited[j]) {
      grays.Push(j);
    }
  }
}