#include "UserInterface.hpp"

using namespace std;

/**
 * Считывание числа из консоли ввода пользователя в диапазоне от start до
 * end
 * @param start Начало диапазона
 * @param end Конец диапазона
 * @return введенное значение в диапазоне start < x < end
 */
int GetUserInputInt(int start, int end) {
  int user_choice = 0;
  char s[256] = {0};
  scanf("%s", s);
  while (sscanf(s, "%d", &user_choice) != 1 || user_choice < start ||
         user_choice > end) {
    printf("\033[1;31m");
    printf("Incorrect input. Try again\n");
    printf("\033[0m> ");

    scanf("%s", s);
  }
  return user_choice;
}

/**
 * Печать main menu
 * @return true
 */
int PrintMainMenu() {
  printf("\033[1;36m");
  printf("\n================= MAIN MENU =================\n");
  printf("\033[0m");
  printf("1. Load the original graph from a file\n");
  printf("2. Export graph to DOT format\n");
  printf("3. Traverse the graph in breadth (BFS)\n");
  printf("4. Traverse the graph in depth (DFS)\n");
  printf(
      "5. Find the shortest path between any two vertices (Dijkstra's "
      "algorithm)\n");
  printf(
      "6. Find the shortest paths between all pairs of vertices in the "
      "graph "
      "(Floyd-Warshall algorithm)\n");
  printf(
      "7. Search for the minimum spanning tree in the graph "
      "(Prim's "
      "algorithm)\n");
  printf("8. Solve the Salesman problem (Ant colony, Brute-Force)\n");
  printf("9. Exit\n");

  printf("> ");

  return true;
}

/**
 * Выводит размер графа и матрицу смежности на экран
 * @param adjacencyMatrix двумерный вектор
 */
void PrintMatrix(const vector<vector<int>>& adjacencyMatrix) {
  if (adjacencyMatrix.empty()) {
    return;
  }

  int size = adjacencyMatrix.size();
  printf("%+d\n", size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf(adjacencyMatrix[i][j] == -1 ? " -- " : "%3d ",
             adjacencyMatrix[i][j]);
    }
    printf("\n");
  }
}

/**
 * Печать вектора
 * @param array указатель на массив
 */
void PrintVector(const vector<int>& result) {
  int shift = 1;
  for (size_t i = 0; i < result.size(); ++i) {
    printf("%d ", result[i] + shift);
  }
  printf("\n");
}

/**
 * Печать заголовка в рамке с цветом
 * @param title строка с текстом заголовка
 */
void PrintHeader(const char* title) {
  int dashes = strlen(title) + 2;

  printf("\n\033[1;32m+");
  for (int i = 0; i < dashes; putchar('-'), i++);
  printf("+\033[0m\n");

  printf("\033[1;32m| %s |\033[0m", title);

  printf("\n\033[1;32m+");
  for (int i = 0; i < dashes; putchar('-'), i++);
  printf("+\033[0m\n");
}

/**
 * Печать нижнего колонтитула для результатов
 */
void PrintResultFooter() {
  printf("\033[1;32m+------------------------------------------+\033[0m\n\n");
}

/**
 * Перемещает курсор консоли на строку вверх и очищает эту строку
 * @param times количество строк
 */
void ClearLastLine(int times) {
  while (times--) {
    printf("\033[1A\033[2K");
  }
}