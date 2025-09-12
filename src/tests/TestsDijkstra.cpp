#include "../algorithms/GraphAlgorithms.hpp"
#include <gtest/gtest.h>

TEST(DijkstraAlgorithmTest, SingleEdgeGraph) {
  Graph graph;
  std::vector<std::vector<int>> mat = {{0, 2}, {2, 0}};
  graph.SetAdjacencyMatrix(mat);

  long long dist = GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 2);
  EXPECT_EQ(dist, 2);

  dist = GraphAlgorithms::GetShortestPathBetweenVertices(graph, 2, 1);
  EXPECT_EQ(dist, 2);
}

TEST(DijkstraAlgorithmTest, PathToSelfIsZero) {
  Graph graph;
  std::vector<std::vector<int>> mat = {{0, 3}, {4, 0}};
  graph.SetAdjacencyMatrix(mat);

  long long dist = GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 1);
  EXPECT_EQ(dist, 0);
}

TEST(DijkstraAlgorithmTest, MiniGraph) {
  Graph graph;
  std::vector<std::vector<int>> mat = {{0, 1, 4}, {1, 0, 2}, {4, 2, 0}};
  graph.SetAdjacencyMatrix(mat);

  // 1->2->3 = 1+2=3
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 3), 3);
  // 3->2->1 = 2+1=3
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 3, 1), 3);
}

TEST(DijkstraAlgorithmTest, NoPathThrows) {
  Graph graph;
  std::vector<std::vector<int>> mat = {{0, 0}, {0, 0}};
  graph.SetAdjacencyMatrix(mat);

  EXPECT_THROW(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 2),
               std::runtime_error);
}

TEST(DijkstraAlgorithmTest, InvalidVertexThrows) {
  Graph graph;
  std::vector<std::vector<int>> mat = {{0, 1}, {1, 0}};
  graph.SetAdjacencyMatrix(mat);

  EXPECT_THROW(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 0, 2),
               std::out_of_range);
  EXPECT_THROW(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 3),
               std::out_of_range);
}

TEST(DijkstraAlgorithmTest, GraphWithLoop) {
  Graph graph;
  std::vector<std::vector<int>> mat = {{1, 2, 0}, {2, 0, 3}, {0, 3, 0}};
  graph.SetAdjacencyMatrix(mat);

  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 2), 2);
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 2, 3), 3);
}

TEST(DijkstraAlgorithmTest, AsymmetricWeights) {
  Graph graph;
  std::vector<std::vector<int>> mat = {{0, 10, 0}, {2, 0, 5}, {0, 1, 0}};
  graph.SetAdjacencyMatrix(mat);

  // 1 -> 2 = 10
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 2), 10);
  // 2 -> 1 = 2
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 2, 1), 2);
  // 1 -> 2 -> 3: 10 + 5 = 15
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 3), 15);
  // 3 -> 2 -> 1: 1 + 2 = 3
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 3, 1), 3);
}

TEST(DijkstraAlgorithmTest, MediumGraph) {
  Graph graph;
  std::vector<std::vector<int>> mat = {{0, 2, 0, 6, 0},
                                       {2, 0, 3, 8, 5},
                                       {0, 3, 0, 0, 7},
                                       {6, 8, 0, 0, 9},
                                       {0, 5, 7, 9, 0}};
  graph.SetAdjacencyMatrix(mat);

  // 1 -> 2 -> 5: 2 + 5 = 7
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 5), 7);

  // 3 -> 2 -> 1 -> 4: 3 + 2 + 6 = 11
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 3, 4), 11);
}

TEST(DijkstraAlgorithmTest, DenseGraph) {
  Graph graph;
  std::vector<std::vector<int>> mat = {
      {0, 1, 5, 2}, {1, 0, 2, 4}, {5, 2, 0, 1}, {2, 4, 1, 0}};
  graph.SetAdjacencyMatrix(mat);

  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 3), 3);
}

TEST(DijkstraAlgorithmTest, Large11NodeGraph) {
  Graph graph;
  std::vector<std::vector<int>> mat = {
      {0, 29, 20, 21, 16, 31, 100, 12, 4, 31, 18},
      {29, 0, 15, 29, 28, 40, 72, 21, 29, 41, 12},
      {20, 15, 0, 15, 14, 25, 81, 9, 23, 27, 13},
      {21, 29, 15, 0, 4, 12, 92, 12, 25, 13, 25},
      {16, 28, 14, 4, 0, 16, 94, 9, 20, 16, 22},
      {31, 40, 25, 12, 16, 0, 95, 24, 36, 3, 37},
      {100, 72, 81, 92, 94, 95, 0, 90, 101, 99, 84},
      {12, 21, 9, 12, 9, 24, 90, 0, 15, 25, 13},
      {4, 29, 23, 25, 20, 36, 101, 15, 0, 35, 18},
      {31, 41, 27, 13, 16, 3, 99, 25, 35, 0, 38},
      {18, 12, 13, 25, 22, 37, 84, 13, 18, 38, 0}};
  graph.SetAdjacencyMatrix(mat);

  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 9), 4);
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 11), 18);
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 7, 5), 94);
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 3, 10), 27);
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 2, 5), 28);
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 3), 20);
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 2, 5), 28);
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 4, 6), 12);
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 10, 5), 16);
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 7, 3), 81);
}

TEST(DijkstraAlgorithmTest, Large100NodeGraph) {
  int n = 100;
  Graph graph;
  std::vector<std::vector<int>> mat(n, std::vector<int>(n, 0));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j)
        mat[i][j] = j + 1;
    }
  }
  graph.SetAdjacencyMatrix(mat);

  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 100),
            100);
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 20, 30), 30);
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 50, 75), 75);
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 99, 1), 1);
}