#include <vector>

#include "../containers/queue.h"
#include "../containers/stack.h"
#include "../graph/graph.h"

class GraphAlgorithms {
 public:
  static std::vector<int> BreadthFirstSearch(Graph &graph, int start_vertex);
  static std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);

 private:
  static void GetBreadthNeighbors(std::vector<std::vector<int>> &grid,
                                  int current_vertex, Queue<int> &grays,
                                  std::vector<bool> &visited);

  static void GetDepthNeighbors(std::vector<std::vector<int>> &grid,
                                int current_vertex, Stack<int> &grays,
                                std::vector<bool> &visited);
};
