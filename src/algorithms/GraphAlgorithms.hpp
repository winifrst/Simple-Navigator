#pragma once

#include <iostream>
#include <limits>
#include <vector>

#include "../containers/Queue.hpp"
#include "../containers/Stack.hpp"
#include "../graph/Graph.hpp"

class GraphAlgorithms {
 public:
  static long long GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                  int vertex2);
  static std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices(
      Graph &graph);
  static std::vector<int> BreadthFirstSearch(Graph &graph, int start_vertex);
  static std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);

 private:
  GraphAlgorithms() = default;
  ~GraphAlgorithms() = default;

  static void GetBreadthNeighbors(
      const std::vector<std::vector<int>> &adjacency_matrix, int current_vertex,
      Queue<int> &grays, std::vector<bool> &visited);
  static void GetDepthNeighbors(
      const std::vector<std::vector<int>> &adjacency_matrix, int current_vertex,
      Stack<int> &grays, std::vector<bool> &visited);
};