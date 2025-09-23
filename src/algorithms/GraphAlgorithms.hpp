#pragma once

#include <random>
#include <vector>

#include "../containers/Queue.hpp"
#include "../containers/Stack.hpp"

// ToDo Здесь нужно подумать! "При этом сам класс GraphAlgorithms не должен
// ничего знать о внутреннем представлении графа из класса Graph." Мб
// использовать абстрактный класс ??? Скорее всего его не исключить.
#include "../graph/Graph.hpp"

// ToDo Добавить doxygen документацию

typedef struct TsmResult {
  int *vertices;
  double distance;
} TsmResult;

// ToDo Вынести namespace
class GraphAlgorithms {
 public:
  static long long GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                  int vertex2);
  static std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices(
      Graph &graph);
  static std::vector<int> BreadthFirstSearch(Graph &graph, int start_vertex);
  static std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);
  static std::vector<std::vector<int>> GetLeastSpanningTree(Graph &graph);
  static TsmResult solve_traveling_salesman_problem(Graph *graph);

 private:
  GraphAlgorithms() = default;
  ~GraphAlgorithms() = default;

  static void GetBreadthNeighbors(
      const std::vector<std::vector<int>> &adjacency_matrix, int current_vertex,
      Queue &grays, std::vector<bool> &visited);
  static void GetDepthNeighbors(
      const std::vector<std::vector<int>> &adjacency_matrix, int current_vertex,
      Stack &grays, std::vector<bool> &visited);
};