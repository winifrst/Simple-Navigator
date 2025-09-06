#include "graph_algorithms.h"

#include "../containers/queue.h"

std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                     int start_vertex) {
  //   std::vector<std::vector<int>> graph;
  size_t size = graph.grid.size();  // его мы принимаем
  std::vector<int> result;
  std::vector<bool> visited(size, false);
  Queue<int> grays;

  grays.Push(start_vertex - 1);
  visited[start_vertex - 1] = true;

  while (!grays.Empty()) {
    int current_vertex = grays.Pop();
    result.push_back(current_vertex + 1);

    GetNeighbors(graph.grid, current_vertex, grays, visited);
  }

  return result;
}

void GraphAlgorithms::GetNeighbors(std::vector<std::vector<int>> &grid,
                                   int current_vertex, Queue<int> &grays,
                                   std::vector<bool> &visited) {
  size_t size = grid.size();

  for (int j = 0; j < size; j++) {
    if (grid[current_vertex][j] != 0 && !visited[j]) {
      grays.Push(j);
      visited[j] = true;
    }
  }
}