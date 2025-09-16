#include "Graph.hpp"

int Graph::LoadGraphFromFile(std::string c_filename) {
  int error = EXIT_SUCCESS;
  std::ifstream file;

  file.open(c_filename, std::ios::in);

  if (!file.is_open()) {
    return EXIT_FAILURE;
  }

  if (!(file >> verticesCount) || verticesCount <= 0) {
    file.close();
    return EXIT_FAILURE;
  }

  error = LoadMatrixFromFile(&file);

  return error;
}

int Graph::LoadMatrixFromFile(std::ifstream* file) {
  int error = EXIT_SUCCESS;

  this->adjacencyMatrix.resize(this->verticesCount,
                               std::vector<int>(this->verticesCount, 0));

  for (int i = 0; i < this->verticesCount && error == EXIT_SUCCESS; ++i) {
    for (int j = 0; j < this->verticesCount && error == EXIT_SUCCESS; ++j) {
      if (!(*file >> this->adjacencyMatrix[i][j]) ||
          this->adjacencyMatrix[i][j] < 0) {
        error = EXIT_FAILURE;
      }
    }
  }

  char c;
  if (*file >> c) {
    error = EXIT_FAILURE;
  }

  if (error == EXIT_FAILURE) {
    this->adjacencyMatrix.clear();
    this->verticesCount = 0;
  }

  return error;
}

int Graph::ExportGraphToDot(std::string filename) {
  int error = EXIT_SUCCESS;
  const char* c_filename = filename.c_str();

  if (this->verticesCount <= 0 || this->adjacencyMatrix.empty() ||
      this->adjacencyMatrix.size() != (size_t)this->verticesCount ||
      (this->adjacencyMatrix.size() > 0 &&
       this->adjacencyMatrix[0].size() != (size_t)this->verticesCount)) {
    return EXIT_FAILURE;
  }

  if (this->verticesCount > 0 && !this->adjacencyMatrix.empty()) {
    FILE* file = NULL;
    if ((file = fopen(c_filename, "wt")) != NULL) {
      bool digraph = false;
      for (int i = 0; i < this->verticesCount; i++) {
        for (int j = i; j < this->verticesCount; j++) {
          if (this->adjacencyMatrix[i][j] != this->adjacencyMatrix[j][i]) {
            digraph = true;
            break;
          }
        }
        if (digraph) break;
      }

      fprintf(file, "%s%s", digraph ? "di" : "", "graph graphname {\n");
      for (int i = 0; i < this->verticesCount; i++) {
        fprintf(file, "    ");
        PrintVertexName(file, i);
        fprintf(file, ";\n");
      }

      for (int i = 0; i < this->verticesCount; i++) {
        for (int j = digraph ? 0 : i; j < this->verticesCount; j++) {
          if (this->adjacencyMatrix[i][j]) {
            fprintf(file, "    ");
            PrintVertexName(file, i);
            fprintf(file, " %s ", digraph ? "->" : "--");
            PrintVertexName(file, j);
            fprintf(file, ";\n");
          }
        }
      }
      fprintf(file, "}");
      fclose(file);
    }
  } else {
    error = EXIT_FAILURE;
  }
  return error;
}

void Graph::PrintVertexName(FILE* file, int i) {
  fprintf(file, "%c", i % 26 + 'a');
  if (i / 26 > 0) {
    fprintf(file, "%d", i / 26);
  }
}

// std::vector<std::vector<int>> Graph::GetAdjacencyMatrix() const {
//   return adjacencyMatrix;
// }

const std::vector<std::vector<int>>& Graph::GetAdjacencyMatrix() const {
  return adjacencyMatrix;
}

void Graph::SetAdjacencyMatrix(const std::vector<std::vector<int>>& matrix) {
  adjacencyMatrix = matrix;
  verticesCount = matrix.size();
}