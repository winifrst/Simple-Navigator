#pragma once
#include <vector>

class Graph {
private:
  std::vector<std::vector<int>> adjacencyMatrix;
  int verticesCount;

public:
  Graph() = default;
  ~Graph() = default;

  int GetVerticesCount() const { return verticesCount; }
  std::vector<std::vector<int>> GetAdjacencyMatrix() const;

  void SetAdjacencyMatrix(const std::vector<std::vector<int>> &matrix);
};
