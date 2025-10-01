#include "MenuHandlers.hpp"

#include <sys/time.h>

#include <climits>

#include "../algorithms/GraphAlgorithms.hpp"
#include "UserInterface.hpp"

/**
 * Запуск загрузки графа
 * @param data указатель на граф
 */
void LoadGraph(Data *data) {
  char filename[256] = {0};
  printf("\nEnter graph filename:\n> ");
  scanf("%s", filename);
  FILE *file = NULL;
  if ((file = fopen(filename, "r")) != NULL) {
    fclose(file);
  } else {
    printf("%s: %s\n", filename, strerror(errno));
    filename[0] = '\0';
    printf("\033[1;36m");
    printf("The following graph will be loaded: "
           "../data-samples/true_graph_3.txt\n");
    printf("\033[0m");
  }

  int load_result = data->graph.LoadGraphFromFile(
      filename[0] ? filename : "../data-samples/true_graph_3.txt");
  if (load_result == EXIT_SUCCESS) {
    data->state = 0;

    PrintHeader("Graph loaded successfully");
    PrintMatrix(data->graph.GetAdjacencyMatrix());
    PrintResultFooter();
  } else {
    printf("\033[1;31m");
    printf("An error occurred while loading the graph from a file.\n");
    printf("\033[0m");
    data->state = 0;
  }
}

/**
 * Запуск экспорта графа
 * @param data указатель на граф
 */
void ExportGraph(Data *data) {
  if (!data->graph.GetAdjacencyMatrix().empty()) {
    if ((data->error = data->graph.ExportGraphToDot("export.dot")) ==
        EXIT_SUCCESS) {
      PrintHeader("Graph exported successfully in export.dot");

    } else {
      PrintHeader("An error occurred while ExportGraph a graph from a file.");
    }
  } else {
    printf("\033[1;31m");
    printf("\nThe graph is not initialized. Please load the graph from file "
           "first.\n");
    printf("\033[0m");
  }
  data->state = 0;
}

/**
 * Запуск BFS
 * @param data указатель на граф
 */
void BFS(Data *data) {
  if (!data->graph.GetAdjacencyMatrix().empty()) {
    std::vector<int> result;
    printf("\033[1;36m");
    printf("Enter START vertex:\n");
    printf("\033[0m> ");
    int start_vertex = GetUserInputInt(1, data->graph.GetVerticesCount()) - 1;
    result = GraphAlgorithms::BreadthFirstSearch(data->graph, start_vertex);

    PrintHeader("BFS traversal result");
    putchar('\n');
    PrintVector(result);
  } else {
    printf("\033[1;31m");
    printf("\nThe graph is not initialized. Please load the graph from file "
           "first.\n");
    printf("\033[0m");
  }
  data->state = 0;
}

/**
 * Запуск DFS
 * @param data указатель на граф
 */
void DFS(Data *data) {
  if (!data->graph.GetAdjacencyMatrix().empty()) {
    std::vector<int> result;

    printf("\033[1;36m");
    printf("Enter START vertex:\n");
    printf("\033[0m> ");
    int start_vertex = GetUserInputInt(1, data->graph.GetVerticesCount()) - 1;
    result = GraphAlgorithms::DepthFirstSearch(data->graph, start_vertex);
    PrintHeader("DFS traversal result");
    putchar('\n');
    PrintVector(result);

  } else {
    printf("\033[1;31m");
    printf("\nThe graph is not initialized. Please load the graph from file "
           "first.\n");
    printf("\033[0m");
  }
  data->state = 0;
}

/**
 * Применяет алгоритм Дэйкстры
 * @param data Указатель на набор данных
 */
void Dijkstra(Data *data) {
  std::vector<std::vector<int>> adjacencyMatrix =
      data->graph.GetAdjacencyMatrix();
  if (!adjacencyMatrix.empty()) {
    printf("\033[1;36m");
    printf("Enter START vertex and END vertex:\n");
    printf("\033[0m> ");
    int vertex_1 = GetUserInputInt(1, data->graph.GetVerticesCount());
    int vertex_2 = GetUserInputInt(1, data->graph.GetVerticesCount());

    PrintHeader("Shortest path distance");
    printf("\033[1;32m");
    printf("\n%lld\n", GraphAlgorithms::GetShortestPathBetweenVertices(
                           data->graph, vertex_1, vertex_2));

    printf("\033[0m");
  } else {
    printf("\033[1;31m");
    printf("\nThe graph is not initialized. Please load the graph from file "
           "first.\n");
  }
  printf("\033[0m");

  data->state = 0;
}

/**
 * Применяет алгоритм Флойда-Уоршалла
 * @param data Указатель на набор данных
 */
void Floyd(Data *data) {
  std::vector<std::vector<int>> adjacencyMatrix =
      data->graph.GetAdjacencyMatrix();
  if (!adjacencyMatrix.empty()) {
    std::vector<std::vector<int>> result =
        GraphAlgorithms::GetShortestPathsBetweenAllVertices(data->graph);

    PrintHeader("Shortest paths between all pairs of vertices in the graph");
    PrintMatrix(result);
    PrintResultFooter();
  } else {
    printf("\033[1;31m");
    printf("\nThe graph is not initialized. Please load the graph from file "
           "first.\n");
    printf("\033[0m");
  }
  data->state = 0;
}

/**
 * Применяет алгоритм Прима
 * @param data Указатель на набор данных
 */
void Prim(Data *data) {
  std::vector<std::vector<int>> adjacencyMatrix =
      data->graph.GetAdjacencyMatrix();

  if (!adjacencyMatrix.empty()) {
    std::vector<std::vector<int>> result =
        GraphAlgorithms::GetLeastSpanningTree(data->graph);

    PrintHeader("The minimum spanning tree in the graph");
    PrintMatrix(result);
    PrintResultFooter();
  }

  else {
    printf("\033[1;31m");
    printf("\nThe graph is not initialized. Please load the graph from file "
           "first.\n");
    printf("\033[0m");
  }
  data->state = 0;
}

long long GetTime() {
  struct timeval t;
  gettimeofday(&t, NULL);

  return (long long)t.tv_sec * 1000 + t.tv_usec / 1000;
}

/**
 * Запуск решения задачи коммивояжёра
 * @param data указатель на граф
 */
void TSP(Data *data) {
  if (!data->graph.GetAdjacencyMatrix().empty()) {
    printf("Enter number of iterations:\n> ");
    int iter = GetUserInputInt(1, INT_MAX);

    long long int t = GetTime();
    TsmResult result_ant;
    for (int i = 0; i < ((iter > 100) ? 100 : iter); i++) {
      result_ant =
          GraphAlgorithms::solve_traveling_salesman_problem(&data->graph);
      free(result_ant.vertices);
    }
    double td =
        (double)(GetTime() - t) / 1000 * ((iter > 100) ? iter / 100 : 1);
    printf("         Ant time: %.3lf s\n", td);
    printf("      path length: %.0f\n", result_ant.distance);
  } else {
    printf("\033[1;31m");
    printf("\nThe graph is not initialized. Please load the graph from file "
           "first.\n");
    printf("\033[0m");
  }
  data->state = 0;
}

void PaintTyan(Data *data) {
  printf("\033[48;5;93m\033[1;37m  ⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⡠⢴⣴⣾⣿⡿⠓⡠⠀⠀⠀⠀⠠⢄⠁⢀\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⠀⠳⣽⡽⠀⠀⡠⢊⣴⣿⣿⣿⣡⠖⠁⣀⡤⢖⠟⠁⡠⠀⡙⢿⣷⣄\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠐⡀⠀⠀⠀⠀⢠⣾⣿⣿⢽⣿⣿⣿⣥⠖⣻⣯⡾⠃⠀⡔⡀⠀⣷⢸⢿⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⢰⠀⠀⠀⢠⢟⣿⠃⢀⣾⣿⠟⠋⢀⡾⢋⣾⠃⣠⡾⢰⡇⡇⣿⣿⡞⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⡤⣈⡀⠀⢀⠏⣼⣧⡴⣼⠟⠁⠀⠀⡾⠁⣾⡇⣰⢿⠃⢾⣿⣷⣿⣿⣇⢿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠱⠼⠊⠀⠄⡜⣿⣿⡿⠃⠈⠁⠀⢸⠁⢠⡿⣰⢯⠃⠀⠘⣿⣿⣿⣿⣿⠸\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⠀⠀⡘⡀⣸⣿⣱⡤⢴⣄⠀⠈⠀⠘⣷⠏⠌⠢⡀⠀⢿⣿⣿⣿⡟⡄\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⢀⣌⠌⣴⣿⣿⠃⣴⣿⣟⡇⠀⠀⠀⠟⠀⠀⠀⠈⠢⢈⣿⡟⣿⡗⡇\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⢀⡴⡻⣡⣾⠟⢹⡇⠀⡇⢄⢿⠇⠀⠀⠀⠀⠀⠀⣽⣶⣄⡀⠘⢷⡹⣿⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⣧⣾⡿⠋⠁⢀⡜⠙⡄⠓⠐⠁⠀⠀⠀⠀⠀⠀⡼⠛⠻⣟⠛⣆⠈⢷⣿⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⣴⣾⣟⣵⣿⣿⣿⣁⢇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡧⠠⠔⡹⠀⢸⠀⣼⣿⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠿⡽⢫⡉⠀⣠⠔⠁⡀⠕⠠⡀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠖⠊⠀⠀⢊⣾⢿⡿⠉\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠁⠀⡹⢨⠁⠐⠈⢀⡠⠐⠁⠄⠡⡀⡀⠀⠀⠀⠀⠀⠀⠀⠠⠶⢛⡨⠊⠀⠀\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⡜⠀⠈⣂⠀⠀⠀⠀⡠⠐⠉⡆⠀⣀⢀⣀⣀⣀⡀⠀⠀⣀⠴⣁⡀⠤⠀⠀\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠈⠀⠀⠀⡇⠑⢄⠀⠀⠀⠀⣲⢥⡎⠀⢰⠀⢸⠀⢀⠉⠙⣿⣧⣀⣀⣂⣤⣼\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠆⠁⠃⠀⠀⠈⠒⠒⠊⣸⠚⠁⠀⠀⠀⠀⠀⠀⠀⡜⠁⠀⠀⠀⠀⠈⠚\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⠀⠂⠀⠀⠀⠀⠀⢀⠋⢆⠀⠀⠀⠀⠀⠀⠀⡘⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠒⠂⠀⠀⠐⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
  printf("\033[42m\033[1;37m   YOU'RE AWESOME!  \\(^.^)/   \033[0m\n");
  data->state = 0;
}