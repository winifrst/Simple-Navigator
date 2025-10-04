#include "GraphAlgorithms.hpp"

using namespace std;

const long long INF = numeric_limits<long long>::max();
const int INF_INT = numeric_limits<int>::max();

/**
 * Реализация алгоритма Дейкстры для поиска кратчайшего пути между двумя
 * вершинами
 * @param graph ссылка на объект графа
 * @param vertex1 начальная вершина (нумерация с 1)
 * @param vertex2 конечная вершина (нумерация с 1)
 * @return длина кратчайшего пути между vertex1 и vertex2
 */
long long GraphAlgorithms::GetShortestPathBetweenVertices(Graph& graph,
                                                          int vertex1,
                                                          int vertex2) {
  int vertices_count = graph.GetVerticesCount();

  if (vertex1 < 1 || vertex2 < 1 || vertex1 > vertices_count ||
      vertex2 > vertices_count) {
    throw out_of_range("Vertex index is out of range.");
  }
  vector<vector<int>> adj_matrix = graph.GetAdjacencyMatrix();

  vector<long long> dist(vertices_count, INF);
  dist[vertex1 - 1] = 0;
  vector<bool> visited(vertices_count, false);

  while (true) {
    int min_vertex = -1;
    long long min_dist = INF;

    for (int i = 0; i < vertices_count; ++i) {
      if (!visited[i] && dist[i] < min_dist) {
        min_dist = dist[i];
        min_vertex = i;
      }
    }
    if (min_vertex == -1) {
      break;
    }
    if (min_vertex == vertex2 - 1) {
      break;
    }

    visited[min_vertex] = true;
    for (int i = 0; i < vertices_count; ++i) {
      if (adj_matrix[min_vertex][i] != 0 && !visited[i]) {
        long long new_dist = dist[min_vertex] + adj_matrix[min_vertex][i];
        if (new_dist < dist[i]) {
          dist[i] = new_dist;
        }
      }
    }
  }

  // if (dist[vertex2 - 1] == INF) {
  //   throw runtime_error("No path exists between the vertices.");
  // }

  return dist[vertex2 - 1];
}

/**
 * Реализация алгоритма Флойда-Уоршелла для поиска кратчайших путей между всеми
 * парами вершин
 * @param graph ссылка на объект графа
 * @return матрица кратчайших расстояний между всеми парами вершин
 */
vector<vector<int>> GraphAlgorithms::GetShortestPathsBetweenAllVertices(
    Graph& graph) {
  int vertices_count = graph.GetVerticesCount();
  vector<vector<int>> dist = graph.GetAdjacencyMatrix();

  for (int k = 0; k < vertices_count; ++k) {
    for (int i = 0; i < vertices_count; ++i) {
      for (int j = 0; j < vertices_count; ++j) {
        if (i == j) {
          dist[i][j] = 0;
        } else if (dist[i][k] < INF_INT / 2 && dist[k][j] < INF_INT / 2) {
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }
  return dist;
}

/**
 * Поиск в ширину (BFS) для обхода графа
 * @param graph ссылка на объект графа
 * @param start_vertex начальная вершина для обхода (нумерация с 0)
 * @return вектор вершин в порядке их посещения
 */
vector<int> GraphAlgorithms::BreadthFirstSearch(Graph& graph,
                                                int start_vertex) {
  vector<int> result;

  if (start_vertex < 0 || start_vertex >= graph.GetVerticesCount() ||
      graph.GetAdjacencyMatrix().empty() || graph.GetVerticesCount() <= 0) {
    return result;
  }

  vector<bool> visited(graph.GetVerticesCount(), false);
  Queue grays;

  grays.Push(start_vertex);
  visited[start_vertex] = true;

  while (!grays.Empty()) {
    int current_vertex = grays.Pop();
    result.push_back(current_vertex);

    GetBreadthNeighbors(graph.GetAdjacencyMatrix(), current_vertex, grays,
                        visited);
  }

  return result;
}

/**
 * Вспомогательная функция для BFS - получение соседей вершины
 * @param adjacencyMatrix матрица смежности графа
 * @param current_vertex текущая вершина
 * @param grays очередь для вершин, ожидающих обработки
 * @param visited массив посещенных вершин
 */
void GraphAlgorithms::GetBreadthNeighbors(
    const vector<vector<int>>& adjacencyMatrix, int current_vertex,
    Queue& grays, vector<bool>& visited) {
  int size = adjacencyMatrix.size();
  if (current_vertex < 0 || current_vertex >= size) {
    return;
  }

  for (int j = 0; j < size; j++) {
    if (adjacencyMatrix[current_vertex][j] != 0 && !visited[j]) {
      grays.Push(j);
      visited[j] = true;
    }
  }
}

/**
 * Поиск в глубину (DFS) для обхода графа
 * @param graph ссылка на объект графа
 * @param start_vertex начальная вершина для обхода (нумерация с 0)
 * @return вектор вершин в порядке их посещения
 */
vector<int> GraphAlgorithms::DepthFirstSearch(Graph& graph, int start_vertex) {
  vector<int> result;
  if (start_vertex < 0 || start_vertex >= graph.GetVerticesCount() ||
      graph.GetAdjacencyMatrix().empty() || graph.GetVerticesCount() <= 0) {
    return result;
  }

  vector<bool> visited(graph.GetVerticesCount(), false);
  Stack grays;

  grays.Push(start_vertex);

  while (!grays.Empty()) {
    int current_vertex = grays.Pop();

    if (!visited[current_vertex]) {
      visited[current_vertex] = true;
      result.push_back(current_vertex);

      GetDepthNeighbors(graph.GetAdjacencyMatrix(), current_vertex, grays,
                        visited);
    }
  }

  return result;
}

/**
 * Вспомогательная функция для DFS - получение соседей вершины в обратном
 * порядке
 * @param adjacencyMatrix матрица смежности графа
 * @param current_vertex текущая вершина
 * @param grays стек для вершин, ожидающих обработки
 * @param visited массив посещенных вершин
 */
void GraphAlgorithms::GetDepthNeighbors(
    const vector<vector<int>>& adjacencyMatrix, int current_vertex,
    Stack& grays, vector<bool>& visited) {
  int size = adjacencyMatrix.size();
  if (current_vertex < 0 || current_vertex >= size) {
    return;
  }

  for (int j = size - 1; j >= 0; j--) {
    if (adjacencyMatrix[current_vertex][j] != 0 && !visited[j]) {
      grays.Push(j);
    }
  }
}

/**
 * Построение минимального остовного дерева алгоритмом Прима
 * @param graph ссылка на объект графа
 * @return матрица смежности минимального остовного дерева
 */
vector<vector<int>> GraphAlgorithms::GetLeastSpanningTree(Graph& graph) {
  int vertices_count = graph.GetVerticesCount();
  vector<vector<int>> adj_matrix = graph.GetAdjacencyMatrix();

  vector<bool> in_mst(vertices_count, false);

  vector<int> min_edge_weight(vertices_count, INF_INT);
  min_edge_weight[0] = 0;

  vector<int> parent(vertices_count, -1);

  for (int i = 0; i < vertices_count - 1; ++i) {
    int min_dist = INF_INT;
    int min_index = -1;
    for (int j = 0; j < vertices_count; ++j) {
      if (!in_mst[j] && min_edge_weight[j] < min_dist) {
        min_dist = min_edge_weight[j];
        min_index = j;
      }
    }
    if (min_index == -1) {
      break;
    }

    in_mst[min_index] = true;
    for (int k = 0; k < vertices_count; ++k) {
      if (adj_matrix[min_index][k] != 0 && !in_mst[k] &&
          adj_matrix[min_index][k] < min_edge_weight[k]) {
        min_edge_weight[k] = adj_matrix[min_index][k];
        parent[k] = min_index;
      }
    }
  }

  vector<vector<int>> mst_matrix(vertices_count,
                                 vector<int>(vertices_count, 0));

  for (int i = 1; i < vertices_count; ++i) {
    if (parent[i] != -1) {
      int weight = adj_matrix[i][parent[i]];
      mst_matrix[i][parent[i]] = weight;
      mst_matrix[parent[i]][i] = weight;
    }
  }
  return mst_matrix;
}

long long GraphAlgorithms::GetTime() {
  struct timeval t;
  gettimeofday(&t, NULL);

  return (long long)t.tv_sec * 1000 + t.tv_usec / 1000;
}

void GraphAlgorithms::BruteForce(Graph* graph, TsmResult* result,
                                 std::vector<int>& current_path,
                                 std::vector<int>& visited, int current_dist,
                                 int depth, long long int t) {
  if (GetTime() - t > 10 * 1000) {
    if (depth == 1) printf("Can't fully solve in 10 sec, return best case.\n");
    return;
  }

  int n = graph->GetVerticesCount();

  if (depth == n) {
    // добавляем ребро возврата в начало
    int back_edge =
        graph->GetAdjacencyMatrix()[current_path[depth - 1]][current_path[0]];
    int total_dist = (back_edge > 0) ? current_dist + back_edge : INT_MAX;

    if (total_dist < result->distance) {
      result->distance = total_dist;
      current_path[depth] = current_path[0];

      // копируем найденный маршрут
      result->vertices.assign(current_path.begin(),
                              current_path.begin() + n + 1);
    }
  } else {
    for (int i = 0; i < n; i++) {
      if (!visited[i]) {
        int weight = graph->GetAdjacencyMatrix()[current_path[depth - 1]][i];

        if (weight > 0) {  // FIX: только положительные рёбра
          visited[i] = 1;
          current_path[depth] = i;
          current_dist += weight;

          BruteForce(graph, result, current_path, visited, current_dist,
                     depth + 1, t);

          current_dist -= weight;
          visited[i] = 0;
        }
      }
    }
  }
}

TsmResult GraphAlgorithms::SolveSalesmanWithBruteForce(Graph* graph) {
  const int n = graph->GetVerticesCount();

  TsmResult result;
  result.distance = std::numeric_limits<double>::infinity();

  if (n == 0) {
    result.distance = 0;
    return result;
  }

  std::vector<int> visited(n, 0);
  visited[0] = 1;

  std::vector<int> current_path(n + 1, -1);
  current_path[0] = 0;

  long long t = GetTime();
  BruteForce(graph, &result, current_path, visited, 0, 1, t);

  return result;
}

bool GraphAlgorithms::IsStronglyConnected(Graph& graph) {
  int n = graph.GetVerticesCount();
  if (n == 0) {
    return true;
  }

  // 1. DFS в исходном графе
  auto visited_order = DepthFirstSearch(graph, 0);
  if ((int)visited_order.size() != n) {
    return false;
  }

  // 2. Строим транспонированный граф
  const auto& dist = graph.GetAdjacencyMatrix();
  std::vector<std::vector<int>> dist_transposed(n, std::vector<int>(n, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (dist[i][j] != 0) {
        dist_transposed[j][i] = dist[i][j];
      }
    }
  }

  Graph transposed_graph;
  transposed_graph.SetAdjacencyMatrix(dist_transposed);

  // 3. DFS в транспонированном графе
  auto visited_order_transposed = DepthFirstSearch(transposed_graph, 0);
  if ((int)visited_order_transposed.size() != n) {
    return false;
  }

  return true;
}

/**
 * Решение задачи коммивояжера с помощью алгоритма муравьиной колонии
 * @param graph указатель на объект графа
 * @return структура TsmResult с оптимальным маршрутом и длиной пути
 */
TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph* graph) {
  if (!IsStronglyConnected(*graph)) {
    return {{}, std::numeric_limits<double>::infinity()};
  }

  int n = graph->GetVerticesCount();
  const auto& dist = graph->GetAdjacencyMatrix();
  if (n == 0) {
    return {{}, 0.0};
  }

  const int antCount = n;
  const int maxIterations = 1000;
  const double alpha = 1.0;
  const double beta = 5.0;
  const double evaporation = 0.5;
  const double Q = 100.0;
  vector<vector<double>> pheromone(n, vector<double>(n, 1.0));
  vector<vector<double>> heuristic(n, vector<double>(n, 0.0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j && dist[i][j] > 0) {
        heuristic[i][j] = 1.0 / dist[i][j];
      }
    }
  }
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dis(0.0, 1.0);
  double bestDistance = numeric_limits<double>::max();
  vector<int> bestTour(n);
  for (int iter = 0; iter < maxIterations; iter++) {
    vector<vector<int>> antsTours(antCount, vector<int>(n));
    vector<double> antsDistances(antCount, 0.0);
    for (int k = 0; k < antCount; k++) {
      vector<bool> visited(n, false);
      int current = k % n;
      antsTours[k][0] = current;
      visited[current] = true;
      for (int step = 1; step < n; step++) {
        double sumProb = 0.0;
        vector<double> probabilities(n, 0.0);
        for (int j = 0; j < n; j++) {
          if (!visited[j] && dist[current][j] > 0) {
            probabilities[j] = pow(pheromone[current][j], alpha) *
                               pow(heuristic[current][j], beta);
            sumProb += probabilities[j];
          }
        }
        double threshold = dis(gen) * sumProb;
        double cumulative = 0.0;
        int nextNode = -1;
        for (int j = 0; j < n; j++) {
          if (!visited[j] && probabilities[j] > 0) {
            cumulative += probabilities[j];
            if (cumulative >= threshold) {
              nextNode = j;
              break;
            }
          }
        }
        if (nextNode == -1) {
          for (int j = 0; j < n; j++) {
            if (!visited[j]) {
              nextNode = j;
              break;
            }
          }
        }
        antsTours[k][step] = nextNode;
        visited[nextNode] = true;
        antsDistances[k] += dist[current][nextNode];
        current = nextNode;
      }
      antsDistances[k] += dist[current][antsTours[k][0]];
      if (antsDistances[k] < bestDistance) {
        bestDistance = antsDistances[k];
        bestTour = antsTours[k];
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        pheromone[i][j] *= (1.0 - evaporation);
        if (pheromone[i][j] < 0.0001) pheromone[i][j] = 0.0001;
      }
    }
    for (int k = 0; k < antCount; k++) {
      double contribution = Q / antsDistances[k];
      for (int i = 0; i < n; i++) {
        int curr = antsTours[k][i];
        int next = antsTours[k][(i + 1) % n];
        pheromone[curr][next] += contribution;
        pheromone[next][curr] += contribution;
      }
    }
  }

  return {bestTour, bestDistance};
}