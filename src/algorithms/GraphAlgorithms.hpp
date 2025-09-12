#pragma once

#include <../graph/Graph.hpp>

class GraphAlgorithms {
public:
  static long long GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                  int vertex2);

private:
  GraphAlgorithms() = default;
  ~GraphAlgorithms() = default;
};