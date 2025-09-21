#pragma once

#include <cstdlib>
#include <string>
#include <vector>

#include "fstream"

// ToDo Добавить doxygen документацию

// ToDo Вынесте namespace
class Graph {
 private:
  std::vector<std::vector<int>> adjacencyMatrix;
  int verticesCount;

 public:
  Graph() = default;
  ~Graph() = default;
  int LoadGraphFromFile(std::string filename);
  int ExportGraphToDot(std::string filename);

  int GetVerticesCount() const { return verticesCount; }
  // ToDo Удалить неискользуемые комменты
  // std::vector<std::vector<int>> GetAdjacencyMatrix() const;
  const std::vector<std::vector<int>>& GetAdjacencyMatrix() const;

  // ToDo Удалить неискользуемые комменты
  // void SetVerticesCount(const int newCount) { verticesCount = newCount; }
  void SetAdjacencyMatrix(const std::vector<std::vector<int>>& matrix);

 private:
  int LoadMatrixFromFile(std::ifstream* file);
  void PrintVertexName(FILE* file, int i);
};
