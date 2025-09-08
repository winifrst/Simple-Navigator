#include "../algorithms/GraphAlgorithms.hpp"
#include <gtest/gtest.h>

const int INF_INT = std::numeric_limits<int>::max();
bool MatricesEqual(const std::vector<std::vector<int>> &a,
                   const std::vector<std::vector<int>> &b) {
  if (a.size() != b.size()) {
    return false;
  }
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i].size() != b[i].size()) {
      return false;
    }

    for (size_t j = 0; j < a[i].size(); ++j) {
      if (a[i][j] != b[i][j]) {
        return false;
      }
    }
  }
  return true;
}

TEST(FloydWarshallAlgorithmTest, SingleVertex) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0}};
  graph.SetAdjacencyMatrix(matrix);

  auto result = GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
  std::vector<std::vector<int>> expected = {{0}};

  EXPECT_TRUE(MatricesEqual(result, expected));
}

TEST(FloydWarshallAlgorithmTest, GraphWithLoop) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{5, 2}, {3, 0}};
  graph.SetAdjacencyMatrix(matrix);

  auto result = GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
  std::vector<std::vector<int>> expected = {{0, 2}, {3, 0}};

  EXPECT_TRUE(MatricesEqual(result, expected));
}

TEST(FloydWarshallAlgorithmTest, LinearGraph) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {
      {0, 4, INF_INT}, {INF_INT, 0, 6}, {INF_INT, INF_INT, 0}};
  graph.SetAdjacencyMatrix(matrix);

  auto result = GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
  std::vector<std::vector<int>> expected = {
      {0, 4, 10}, {INF_INT, 0, 6}, {INF_INT, INF_INT, 0}};

  EXPECT_TRUE(MatricesEqual(result, expected));
}

TEST(FloydWarshallAlgorithmTest, CompleteGraph) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0, 1, 5}, {1, 0, 2}, {5, 2, 0}};
  graph.SetAdjacencyMatrix(matrix);

  auto result = GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
  std::vector<std::vector<int>> expected = {{0, 1, 3}, {1, 0, 2}, {3, 2, 0}};

  EXPECT_TRUE(MatricesEqual(result, expected));
}

TEST(FloydWarshallAlgorithmTest, ShorterThroughIntermediate) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {
      {0, 2, 10}, {INF_INT, 0, 2}, {INF_INT, INF_INT, 0}};
  graph.SetAdjacencyMatrix(matrix);

  auto result = GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
  std::vector<std::vector<int>> expected = {
      {0, 2, 4}, {INF_INT, 0, 2}, {INF_INT, INF_INT, 0}};

  EXPECT_TRUE(MatricesEqual(result, expected));
}

TEST(FloydWarshallAlgorithmTest, TwoVerticesNoEdge) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0, INF_INT}, {INF_INT, 0}};
  graph.SetAdjacencyMatrix(matrix);

  auto result = GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
  EXPECT_TRUE(MatricesEqual(result, matrix));
}

TEST(FloydWarshallAlgorithmTest, LoopsDifferentWeights) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {
      {3, 2, INF_INT}, {INF_INT, 5, 1}, {4, INF_INT, 7}};
  graph.SetAdjacencyMatrix(matrix);

  auto result = GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
  std::vector<std::vector<int>> expected = {{0, 2, 3}, {5, 0, 1}, {4, 6, 0}};
  EXPECT_TRUE(MatricesEqual(result, expected));
}

TEST(FloydWarshallAlgorithmTest, MultipleEqualPaths) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0, 2, 5, INF_INT},
                                          {INF_INT, 0, 2, 3},
                                          {INF_INT, INF_INT, 0, 1},
                                          {1, INF_INT, INF_INT, 0}};
  graph.SetAdjacencyMatrix(matrix);

  auto result = GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
  std::vector<std::vector<int>> expected = {
      {0, 2, 4, 5}, {4, 0, 2, 3}, {2, 4, 0, 1}, {1, 3, 5, 0}};
  EXPECT_TRUE(MatricesEqual(result, expected));
}

TEST(FloydWarshallAlgorithmTest, LinearGraph5Vertices) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {
      {0, 1, INF_INT, INF_INT, INF_INT},
      {INF_INT, 0, 2, INF_INT, INF_INT},
      {INF_INT, INF_INT, 0, 3, INF_INT},
      {INF_INT, INF_INT, INF_INT, 0, 4},
      {INF_INT, INF_INT, INF_INT, INF_INT, 0}};
  graph.SetAdjacencyMatrix(matrix);

  auto result = GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
  std::vector<std::vector<int>> expected = {
      {0, 1, 3, 6, 10},
      {INF_INT, 0, 2, 5, 9},
      {INF_INT, INF_INT, 0, 3, 7},
      {INF_INT, INF_INT, INF_INT, 0, 4},
      {INF_INT, INF_INT, INF_INT, INF_INT, 0}};
  EXPECT_TRUE(MatricesEqual(result, expected));
}

TEST(FloydWarshallAlgorithmTest, RandomConnected6Vertices) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {
      {0, 3, INF_INT, 7, INF_INT, INF_INT},
      {8, 0, 2, INF_INT, INF_INT, INF_INT},
      {5, INF_INT, 0, 1, INF_INT, INF_INT},
      {2, INF_INT, INF_INT, 0, 1, INF_INT},
      {INF_INT, INF_INT, 3, INF_INT, 0, 2},
      {INF_INT, 1, INF_INT, INF_INT, INF_INT, 0}};
  graph.SetAdjacencyMatrix(matrix);

  auto result = GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
  std::vector<std::vector<int>> expected = {
      {0, 3, 5, 6, 7, 9}, {5, 0, 2, 3, 4, 6}, {3, 5, 0, 1, 2, 4},
      {2, 4, 4, 0, 1, 3}, {6, 3, 3, 4, 0, 2}, {6, 1, 3, 4, 5, 0}};

  EXPECT_TRUE(MatricesEqual(result, expected));
}