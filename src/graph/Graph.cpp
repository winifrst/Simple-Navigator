#include "Graph.hpp"

std::vector<std::vector<int>> Graph::GetAdjacencyMatrix() const {
  return adjacencyMatrix;
}

void Graph::SetAdjacencyMatrix(const std::vector<std::vector<int>> &matrix) {
  adjacencyMatrix = matrix;
  verticesCount = matrix.size();
}