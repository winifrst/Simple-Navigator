#include "Graph.hpp"

using namespace std;

/**
 * Загрузка графа из файла
 * @param c_filename имя файла с матрицей смежности
 * @return EXIT_SUCCESS при успешной загрузке, EXIT_FAILURE при ошибке
 */
int Graph::LoadGraphFromFile(string c_filename) {
  int error = EXIT_SUCCESS;
  ifstream file;

  file.open(c_filename, ios::in);

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

/**
 * Загрузка матрицы смежности из открытого файла
 * @param file указатель на открытый файловый поток
 * @return EXIT_SUCCESS при успешной загрузке, EXIT_FAILURE при ошибке формата
 */
int Graph::LoadMatrixFromFile(ifstream* file) {
  int error = EXIT_SUCCESS;

  this->adjacencyMatrix.resize(this->verticesCount,
                               vector<int>(this->verticesCount, 0));

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

/**
 * Экспорт графа в формат DOT
 * @param filename имя выходного файла
 * @return EXIT_SUCCESS при успешном экспорте, EXIT_FAILURE при ошибке
 */
int Graph::ExportGraphToDot(string filename) {
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

/**
 * Генерация имени вершины для формата DOT
 * @param file указатель на файловый поток
 * @param i индекс вершины
 */
void Graph::PrintVertexName(FILE* file, int i) {
  fprintf(file, "%c", i % 26 + 'a');
  if (i / 26 > 0) {
    fprintf(file, "%d", i / 26);
  }
}

/**
 * Получение матрицы смежности графа
 * @return константная ссылка на матрицу смежности
 */
const vector<vector<int>>& Graph::GetAdjacencyMatrix() const {
  return adjacencyMatrix;
}

/**
 * Получение количества вершин в графе
 * @return количество вершин
 */
int Graph::GetVerticesCount() const { return verticesCount; }

/**
 * Установка матрицы смежности графа
 * @param matrix новая матрица смежности
 */
void Graph::SetAdjacencyMatrix(const vector<vector<int>>& matrix) {
  adjacencyMatrix = matrix;
  verticesCount = matrix.size();
}