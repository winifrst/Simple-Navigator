#include <gtest/gtest.h>

#include "../algorithms/GraphAlgorithms.hpp"
#include "TestUtils.hpp"

TEST(PrimAlgorithmTest, SingleVertex) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0}};
  graph.SetAdjacencyMatrix(matrix);

  auto mst = GraphAlgorithms::GetLeastSpanningTree(graph);
  std::vector<std::vector<int>> expected = {{0}};
  EXPECT_TRUE(MatricesEqual(mst, expected));
}

TEST(PrimAlgorithmTest, TwoVerticesConnected) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0, 5}, {5, 0}};
  graph.SetAdjacencyMatrix(matrix);

  auto mst = GraphAlgorithms::GetLeastSpanningTree(graph);
  std::vector<std::vector<int>> expected = {{0, 5}, {5, 0}};
  EXPECT_TRUE(MatricesEqual(mst, expected));
}

TEST(PrimAlgorithmTest, TwoVerticesDisconnected) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0, 0}, {0, 0}};
  graph.SetAdjacencyMatrix(matrix);

  auto mst = GraphAlgorithms::GetLeastSpanningTree(graph);
  std::vector<std::vector<int>> expected = {{0, 0}, {0, 0}};
  EXPECT_TRUE(MatricesEqual(mst, expected));
}

TEST(PrimAlgorithmTest, ThreeVerticesTriangle) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0, 1, 3}, {1, 0, 2}, {3, 2, 0}};
  graph.SetAdjacencyMatrix(matrix);

  auto mst = GraphAlgorithms::GetLeastSpanningTree(graph);
  std::vector<std::vector<int>> expected = {{0, 1, 0}, {1, 0, 2}, {0, 2, 0}};
  EXPECT_TRUE(MatricesEqual(mst, expected));
}

TEST(PrimAlgorithmTest, CompleteGraphFourVertices) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {
      {0, 2, 4, 3}, {2, 0, 5, 1}, {4, 5, 0, 6}, {3, 1, 6, 0}};
  graph.SetAdjacencyMatrix(matrix);

  auto mst = GraphAlgorithms::GetLeastSpanningTree(graph);

  std::vector<std::vector<int>> expected = {
      {0, 2, 4, 0}, {2, 0, 0, 1}, {4, 0, 0, 0}, {0, 1, 0, 0}};

  EXPECT_TRUE(MatricesEqual(mst, expected));
}

TEST(PrimAlgorithmTest, GraphWithLoops) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{2, 3, 0}, {3, 5, 1}, {0, 1, 4}};
  graph.SetAdjacencyMatrix(matrix);

  auto mst = GraphAlgorithms::GetLeastSpanningTree(graph);
  std::vector<std::vector<int>> expected = {{0, 3, 0}, {3, 0, 1}, {0, 1, 0}};

  EXPECT_TRUE(MatricesEqual(mst, expected));
}

TEST(PrimAlgorithmTest, LinearGraphFiveVertices) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0, 1, 0, 0, 0},
                                          {1, 0, 2, 0, 0},
                                          {0, 2, 0, 3, 0},
                                          {0, 0, 3, 0, 4},
                                          {0, 0, 0, 4, 0}};
  graph.SetAdjacencyMatrix(matrix);

  auto mst = GraphAlgorithms::GetLeastSpanningTree(graph);

  std::vector<std::vector<int>> expected = {{0, 1, 0, 0, 0},
                                            {1, 0, 2, 0, 0},
                                            {0, 2, 0, 3, 0},
                                            {0, 0, 3, 0, 4},
                                            {0, 0, 0, 4, 0}};

  EXPECT_TRUE(MatricesEqual(mst, expected));
}

TEST(PrimAlgorithmTest, EqualMinimalEdges) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {
      {0, 1, 1, 2}, {1, 0, 2, 1}, {1, 2, 0, 1}, {2, 1, 1, 0}};
  graph.SetAdjacencyMatrix(matrix);

  auto mst = GraphAlgorithms::GetLeastSpanningTree(graph);

  int edge_count = 0;
  int total_weight = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {
      if (mst[i][j] != 0) {
        edge_count++;
        total_weight += mst[i][j];
      }
    }
  }

  EXPECT_EQ(edge_count, 3);
  EXPECT_EQ(total_weight, 3);
}

TEST(PrimAlgorithmTest, RandomGraphSixVertices) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {
      {0, 3, 0, 7, 0, 0}, {3, 0, 2, 0, 0, 0}, {0, 2, 0, 1, 0, 0},
      {7, 0, 1, 0, 1, 0}, {0, 0, 0, 1, 0, 5}, {0, 0, 0, 0, 5, 0}};
  graph.SetAdjacencyMatrix(matrix);

  auto mst = GraphAlgorithms::GetLeastSpanningTree(graph);

  std::vector<std::vector<int>> expected = {
      {0, 3, 0, 0, 0, 0}, {3, 0, 2, 0, 0, 0}, {0, 2, 0, 1, 0, 0},
      {0, 0, 1, 0, 1, 0}, {0, 0, 0, 1, 0, 5}, {0, 0, 0, 0, 5, 0}};

  EXPECT_TRUE(MatricesEqual(mst, expected));
}

TEST(PrimAlgorithmTest, DisconnectedGraph) {
  Graph graph;

  std::vector<std::vector<int>> matrix = {
      {0, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}};
  graph.SetAdjacencyMatrix(matrix);

  std::vector<std::vector<int>> result =
      GraphAlgorithms::GetLeastSpanningTree(graph);

  EXPECT_EQ(result.size(), 4);
  EXPECT_EQ(result[0].size(), 4);

  bool has_edges = false;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (result[i][j] > 0) {
        has_edges = true;

        EXPECT_GT(matrix[i][j], 0);
      }
    }
  }

  EXPECT_TRUE(has_edges);
}