#include "GraphAlgorithms.hpp"

const long long INF = std::numeric_limits<long long>::max();
const int INF_INT = std::numeric_limits<int>::max();

long long GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph,
                                                          int vertex1,
                                                          int vertex2) {
  int vertices_count = graph.GetVerticesCount();

  if (vertex1 < 1 || vertex2 < 1 || vertex1 > vertices_count ||
      vertex2 > vertices_count) {
    throw std::out_of_range("Vertex index is out of range.");
  }
  std::vector<std::vector<int>> adj_matrix = graph.GetAdjacencyMatrix();

  std::vector<long long> dist(vertices_count, INF);
  dist[vertex1 - 1] = 0;
  std::vector<bool> visited(vertices_count, false);

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
  if (dist[vertex2 - 1] == INF) {
    throw std::runtime_error("No path exists between the vertices.");
  }

  return dist[vertex2 - 1];
}

std::vector<std::vector<int>>
GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph) {
  int vertices_count = graph.GetVerticesCount();
  std::vector<std::vector<int>> dist = graph.GetAdjacencyMatrix();

  for (int k = 0; k < vertices_count; ++k) {
    for (int i = 0; i < vertices_count; ++i) {
      for (int j = 0; j < vertices_count; ++j) {
        if (i == j) {
          dist[i][j] = 0;
        } else if (dist[i][k] < INF_INT / 2 && dist[k][j] < INF_INT / 2) {
          dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }
  return dist;
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                     int start_vertex) {
  std::vector<int> result;

  if (start_vertex < 0 || start_vertex >= graph.GetVerticesCount() ||
      graph.GetAdjacencyMatrix().empty() || graph.GetVerticesCount() <= 0) {
    return result;
  }

  std::vector<bool> visited(graph.GetVerticesCount(), false);
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

void GraphAlgorithms::GetBreadthNeighbors(
    const std::vector<std::vector<int>> &adjacencyMatrix, int current_vertex,
    Queue &grays, std::vector<bool> &visited) {
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

std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph,
                                                   int start_vertex) {
  std::vector<int> result;
  if (start_vertex < 0 || start_vertex >= graph.GetVerticesCount() ||
      graph.GetAdjacencyMatrix().empty() || graph.GetVerticesCount() <= 0) {
    return result;
  }

  std::vector<bool> visited(graph.GetVerticesCount(), false);
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

void GraphAlgorithms::GetDepthNeighbors(
    const std::vector<std::vector<int>> &adjacencyMatrix, int current_vertex,
    Stack &grays, std::vector<bool> &visited) {
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

std::vector<std::vector<int>> GraphAlgorithms::GetLeastSpanningTree(
    Graph &graph) {
  int vertices_count = graph.GetVerticesCount();
  std::vector<std::vector<int>> adj_matrix = graph.GetAdjacencyMatrix();

  std::vector<bool> in_mst(vertices_count, false);

  std::vector<int> min_edge_weight(vertices_count, INF_INT);
  min_edge_weight[0] = 0;

  std::vector<int> parent(vertices_count, -1);

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

  std::vector<std::vector<int>> mst_matrix(vertices_count,
                                           std::vector<int>(vertices_count, 0));

  for (int i = 1; i < vertices_count; ++i) {
    if (parent[i] != -1) {
      int weight = adj_matrix[i][parent[i]];
      mst_matrix[i][parent[i]] = weight;
      mst_matrix[parent[i]][i] = weight;
    }
  }
  return mst_matrix;
}

TsmResult GraphAlgorithms::solve_traveling_salesman_problem(Graph *graph) {
  int n = graph->GetVerticesCount();
  const auto &dist = graph->GetAdjacencyMatrix();
  if (n == 0) {
    return {nullptr, 0.0};
  }
  const int antCount = n;
  const int maxIterations = 1000;
  const double alpha = 1.0;
  const double beta = 5.0;
  const double evaporation = 0.5;
  const double Q = 100.0;
  std::vector<std::vector<double>> pheromone(n, std::vector<double>(n, 1.0));
  std::vector<std::vector<double>> heuristic(n, std::vector<double>(n, 0.0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j && dist[i][j] > 0) {
        heuristic[i][j] = 1.0 / dist[i][j];
      }
    }
  }
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);
  double bestDistance = std::numeric_limits<double>::max();
  std::vector<int> bestTour(n);
  for (int iter = 0; iter < maxIterations; iter++) {
    std::vector<std::vector<int>> antsTours(antCount, std::vector<int>(n));
    std::vector<double> antsDistances(antCount, 0.0);
    for (int k = 0; k < antCount; k++) {
      std::vector<bool> visited(n, false);
      int current = k % n;
      antsTours[k][0] = current;
      visited[current] = true;
      for (int step = 1; step < n; step++) {
        double sumProb = 0.0;
        std::vector<double> probabilities(n, 0.0);
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
  int *resultPath = new int[n];
  for (int i = 0; i < n; i++) {
    resultPath[i] = bestTour[i];
  }
  return {resultPath, bestDistance};
}