#pragma once

#include <../graph/Graph.hpp>

class GraphAlgorithms {
public:
  static long long GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                  int vertex2);
  static std::vector<std::vector<int>>
  GetShortestPathsBetweenAllVertices(Graph &graph);

private:
  GraphAlgorithms() = default;
  ~GraphAlgorithms() = default;
};