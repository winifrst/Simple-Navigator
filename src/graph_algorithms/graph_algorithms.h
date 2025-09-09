#include <vector>

#include "../containers/queue.h"
#include "../graph/graph.h"

class GraphAlgorithms {
 public:
  static std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);
  static std::vector<int> BreadthFirstSearch(Graph &graph, int start_vertex);
  static void GetNeighbors(std::vector<std::vector<int>> &grid,
                           int current_vertex, Queue<int> &grays,
                           std::vector<bool> &visited);
};
