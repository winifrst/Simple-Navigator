#include "graph_algorithms.h"

#include <iostream>

// std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph,
//                                                      int start_vertex) {
//   size_t size = graph.adjacencyMatrix.size();
//   std::vector<int> result;
//   std::vector<bool> visited(size, false);
//   Queue<int> grays;

//   grays.Push(start_vertex);
//   visited[start_vertex] = true;

//   while (!grays.Empty()) {
//     int current_vertex = grays.Pop();
//     result.push_back(current_vertex);

//     GetNeighbors(graph.adjacencyMatrix, current_vertex, grays, visited);
//   }

//   return result;
// }

std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                     int start_vertex) {
  size_t size = graph.adjacencyMatrix.size();
  if (start_vertex < 0 || start_vertex >= (int)size) {
    std::cerr << "Ошибка: start_vertex " << start_vertex
              << " вне диапазона [0, " << size - 1 << "]" << std::endl;
    return {};
  }

  std::vector<int> result;
  std::vector<bool> visited(size, false);
  Queue<int> grays;

  grays.Push(start_vertex);
  visited[start_vertex] = true;

  std::cout << "Начальная вершина: " << start_vertex << std::endl;

  while (!grays.Empty()) {
    int current_vertex = grays.Pop();
    std::cout << "Обрабатываем вершину: " << current_vertex << std::endl;
    result.push_back(current_vertex);

    GetNeighbors(graph.adjacencyMatrix, current_vertex, grays, visited);
  }

  std::cout << "Результат BFS: ";
  for (int v : result) std::cout << v << " ";
  std::cout << std::endl;

  return result;
}

void GraphAlgorithms::GetNeighbors(
    std::vector<std::vector<int>> &adjacencyMatrix, int current_vertex,
    Queue<int> &grays, std::vector<bool> &visited) {
  int size = adjacencyMatrix.size();
  if (current_vertex < 0 || current_vertex >= size) {
    // std::cerr << "Ошибка: некорректный индекс вершины: " << current_vertex
    //           << std::endl;
    return;
  }

  for (int j = 0; j < size; j++) {
    if (adjacencyMatrix[current_vertex][j] != 0 && !visited[j]) {
      grays.Push(j);
      visited[j] = true;
    }
  }
}