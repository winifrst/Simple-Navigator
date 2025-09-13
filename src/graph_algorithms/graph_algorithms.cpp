#include "graph_algorithms.h"

std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                     int start_vertex) {
  std::vector<int> result;
  if (start_vertex < 0 || start_vertex >= graph.verticesCount ||
      graph.adjacencyMatrix.empty() || graph.verticesCount <= 0) {
    return result;
  }

  std::vector<bool> visited(graph.verticesCount, false);
  Queue<int> grays;

  grays.Push(start_vertex);
  visited[start_vertex] = true;

  while (!grays.Empty()) {
    int current_vertex = grays.Pop();
    result.push_back(current_vertex);

    GetBreadthNeighbors(graph.adjacencyMatrix, current_vertex, grays, visited);
  }

  return result;
}

void GraphAlgorithms::GetBreadthNeighbors(
    std::vector<std::vector<int>> &adjacencyMatrix, int current_vertex,
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
  if (start_vertex < 0 || start_vertex >= graph.verticesCount ||
      graph.adjacencyMatrix.empty() || graph.verticesCount <= 0) {
    return result;
  }

  std::vector<bool> visited(graph.verticesCount, false);
  Stack<int> grays;

  grays.Push(start_vertex);

  while (!grays.Empty()) {
    int current_vertex = grays.Pop();

    if (!visited[current_vertex]) {
      visited[current_vertex] = true;
      result.push_back(current_vertex);

      GetDepthNeighbors(graph.adjacencyMatrix, current_vertex, grays, visited);
    }
  }

  return result;
}

void GraphAlgorithms::GetDepthNeighbors(
    std::vector<std::vector<int>> &adjacencyMatrix, int current_vertex,
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