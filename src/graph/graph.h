#ifndef GRAPH_H
#define GRAPH_H

#include <cstdlib>
#include <string>
#include <vector>

#include "fstream"

class Graph {
 private:
  int LoadMatrixFromFile(std::ifstream* file);
  void PrintVertexName(FILE* file, int i);

 public:
  Graph() = default;
  ~Graph() = default;

  int LoadGraphFromFile(std::string filename);
  int ExportGraphToDot(std::string filename);

  std::vector<std::vector<int>> adjacencyMatrix;
  int verticesCount;
};

#endif  // GRAPH_H