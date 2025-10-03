#pragma once

#include <sys/time.h>

#include <algorithm>
#include <climits>
#include <random>
#include <vector>

#include "../containers/Queue.hpp"
#include "../containers/Stack.hpp"
#include "../graph/Graph.hpp"

typedef struct TsmResult {
  std::vector<int> vertices;
  double distance;
} TsmResult;

class GraphAlgorithms {
 public:
  static long long GetShortestPathBetweenVertices(Graph& graph, int vertex1,
                                                  int vertex2);
  static std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices(
      Graph& graph);
  static std::vector<int> BreadthFirstSearch(Graph& graph, int start_vertex);
  static std::vector<int> DepthFirstSearch(Graph& graph, int start_vertex);
  static std::vector<std::vector<int>> GetLeastSpanningTree(Graph& graph);
  static TsmResult SolveTravelingSalesmanProblem(Graph* graph);
  static TsmResult SolveSalesmanWithBruteForce(Graph* graph);

 private:
  GraphAlgorithms() = default;
  ~GraphAlgorithms() = default;

  static void GetBreadthNeighbors(
      const std::vector<std::vector<int>>& adjacency_matrix, int current_vertex,
      Queue& grays, std::vector<bool>& visited);
  static void GetDepthNeighbors(
      const std::vector<std::vector<int>>& adjacency_matrix, int current_vertex,
      Stack& grays, std::vector<bool>& visited);
  static long long GetTime();
  static void BruteForce(Graph* graph, TsmResult* result,
                         std::vector<int>& current_path,
                         std::vector<int>& visited, int current_dist, int depth,
                         long long int t);

  static bool IsStronglyConnected(Graph& graph);
};