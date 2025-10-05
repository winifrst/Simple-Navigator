#include <gtest/gtest.h>

#include <climits>
#include <limits>
#include <vector>

#include "GraphAlgorithms.hpp"

TEST(SolveTravelingSalesmanProblemTest, SingleVertexGraph) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveTravelingSalesmanProblem(&graph);

  EXPECT_EQ(result.distance, 0);
  ASSERT_EQ(result.vertices.size(), 1);
  EXPECT_EQ(result.vertices[0], 0);
}

TEST(SolveTravelingSalesmanProblemTest, TwoVerticesCompleteGraph) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0, 5}, {3, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveTravelingSalesmanProblem(&graph);

  EXPECT_EQ(result.distance, 8);
  EXPECT_EQ(result.vertices.size(), 2);
}

TEST(SolveTravelingSalesmanProblemTest, ThreeVerticesCompleteGraph) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0, 1, 2}, {1, 0, 3}, {2, 3, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveTravelingSalesmanProblem(&graph);

  EXPECT_NE(result.distance, std::numeric_limits<double>::infinity());
  EXPECT_GT(result.distance, 0);
  EXPECT_EQ(result.vertices.size(), 3);

  std::vector<bool> vertices_found(3, false);
  for (int vertex : result.vertices) {
    EXPECT_GE(vertex, 0);
    EXPECT_LT(vertex, 3);
    vertices_found[vertex] = true;
  }
  for (bool found : vertices_found) {
    EXPECT_TRUE(found);
  }
}

TEST(SolveTravelingSalesmanProblemTest, GraphWithMissingEdgesButConnected) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0, 2, 0}, {2, 0, 4}, {0, 4, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveTravelingSalesmanProblem(&graph);

  EXPECT_NE(result.distance, std::numeric_limits<double>::infinity());
  EXPECT_GT(result.distance, 0);
  EXPECT_EQ(result.vertices.size(), 3);
}

TEST(SolveTravelingSalesmanProblemTest, GraphWithoutHamiltonianCycle) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {
      {0, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveTravelingSalesmanProblem(&graph);

  EXPECT_EQ(result.distance, std::numeric_limits<double>::infinity());
  EXPECT_TRUE(result.vertices.empty());
}

TEST(SolveTravelingSalesmanProblemTest, EmptyGraph) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveTravelingSalesmanProblem(&graph);

  EXPECT_EQ(result.distance, 0);
  EXPECT_TRUE(result.vertices.empty());
}

TEST(SolveTravelingSalesmanProblemTest, GraphWithZeroWeights) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveTravelingSalesmanProblem(&graph);

  EXPECT_EQ(result.distance, std::numeric_limits<double>::infinity());
  EXPECT_TRUE(result.vertices.empty());
}

TEST(SolveTravelingSalesmanProblemTest, SymmetricGraph) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0, 2, 1}, {2, 0, 2}, {1, 2, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveTravelingSalesmanProblem(&graph);

  EXPECT_NE(result.distance, std::numeric_limits<double>::infinity());
  EXPECT_GT(result.distance, 0);
  EXPECT_EQ(result.vertices.size(), 3);
}

TEST(SolveTravelingSalesmanProblemTest, CompleteGraph4Vertices) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {
      {0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveTravelingSalesmanProblem(&graph);

  EXPECT_NE(result.distance, std::numeric_limits<double>::infinity());
  EXPECT_GT(result.distance, 0);
  EXPECT_EQ(result.vertices.size(), 4);

  std::vector<bool> vertices_found(4, false);
  for (int vertex : result.vertices) {
    EXPECT_GE(vertex, 0);
    EXPECT_LT(vertex, 4);
    vertices_found[vertex] = true;
  }
  for (bool found : vertices_found) {
    EXPECT_TRUE(found);
  }
}

TEST(SolveTravelingSalesmanProblemTest, SingleVertexWithLoop) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{5}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveTravelingSalesmanProblem(&graph);

  EXPECT_EQ(result.distance, 5);
  EXPECT_EQ(result.vertices.size(), 1);
}

TEST(SolveTravelingSalesmanProblemTest, LinearConnectedGraph) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {
      {0, 1, 0, 0}, {1, 0, 1, 0}, {0, 1, 0, 1}, {0, 0, 1, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveTravelingSalesmanProblem(&graph);

  EXPECT_NE(result.distance, std::numeric_limits<double>::infinity());
  EXPECT_GT(result.distance, 0);
  EXPECT_EQ(result.vertices.size(), 4);
}

TEST(SolveTravelingSalesmanProblemTest, GraphWithDifferentWeights) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0, 1, 10}, {1, 0, 1}, {10, 1, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveTravelingSalesmanProblem(&graph);

  EXPECT_NE(result.distance, std::numeric_limits<double>::infinity());
  EXPECT_GT(result.distance, 0);

  EXPECT_LE(result.distance, 12);
}

TEST(SolveTravelingSalesmanProblemTest, PerformanceSmallGraph) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {
      {0, 2, 9, 10}, {1, 0, 6, 4}, {15, 7, 0, 8}, {6, 3, 12, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveTravelingSalesmanProblem(&graph);

  EXPECT_NE(result.distance, std::numeric_limits<double>::infinity());
  EXPECT_GT(result.distance, 0);
  EXPECT_EQ(result.vertices.size(), 4);
}

TEST(SolveTravelingSalesmanProblemTest, CompareWithBruteForceOnSmallGraph) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0, 2, 1}, {2, 0, 3}, {1, 3, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult antResult = GraphAlgorithms::SolveTravelingSalesmanProblem(&graph);
  TsmResult bruteResult = GraphAlgorithms::SolveSalesmanWithBruteForce(&graph);

  EXPECT_NE(antResult.distance, std::numeric_limits<double>::infinity());

  if (bruteResult.distance != std::numeric_limits<double>::infinity()) {
    EXPECT_NE(antResult.distance, std::numeric_limits<double>::infinity());
  }
}