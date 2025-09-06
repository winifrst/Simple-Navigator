#include <vector>

#include "../graph/graph.h"

class GraphAlgorithms {
 public:
  std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);
  std::vector<int> BreadthFirstSearch(Graph &graph, int start_vertex);
  void GetNeighbors(std::vector<std::vector<int>> &grid, int current_vertex,
                    Queue<int> &grays, std::vector<bool> &visited);
};
