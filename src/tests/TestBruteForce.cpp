#include <gtest/gtest.h>

#include <climits>
#include <limits>
#include <vector>

#include "GraphAlgorithms.hpp"

TEST(SolveSalesmanWithBruteForceTest, TwoVerticesCompleteGraph) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0, 5}, {3, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveSalesmanWithBruteForce(&graph);

  EXPECT_EQ(result.distance, 8);
  ASSERT_EQ(result.vertices.size(), 3);
  EXPECT_EQ(result.vertices[0], 0);
  EXPECT_EQ(result.vertices[1], 1);
  EXPECT_EQ(result.vertices[2], 0);
}

TEST(SolveSalesmanWithBruteForceTest, ThreeVerticesCompleteGraph) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0, 1, 2}, {1, 0, 3}, {2, 3, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveSalesmanWithBruteForce(&graph);

  EXPECT_NE(result.distance, std::numeric_limits<double>::infinity());
  EXPECT_EQ(result.vertices.size(), 4);
  EXPECT_EQ(result.vertices[0], result.vertices[3]);

  std::vector<bool> vertices_found(3, false);
  for (int i = 0; i < 3; i++) {
    int vertex = result.vertices[i];
    EXPECT_GE(vertex, 0);
    EXPECT_LT(vertex, 3);
    vertices_found[vertex] = true;
  }
  for (bool found : vertices_found) {
    EXPECT_TRUE(found);
  }
}

TEST(SolveSalesmanWithBruteForceTest, GraphWithMissingEdges) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0, 2, 0}, {2, 0, 4}, {0, 4, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveSalesmanWithBruteForce(&graph);

  EXPECT_NE(result.distance, std::numeric_limits<double>::infinity());
  EXPECT_EQ(result.vertices.size(), 4);
}

TEST(SolveSalesmanWithBruteForceTest, GraphWithoutHamiltonianCycle) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {
      {0, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveSalesmanWithBruteForce(&graph);

  EXPECT_EQ(result.distance, std::numeric_limits<double>::infinity());
}

TEST(SolveSalesmanWithBruteForceTest, EmptyGraph) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveSalesmanWithBruteForce(&graph);

  EXPECT_EQ(result.distance, 0);
  EXPECT_TRUE(result.vertices.empty());
}

TEST(SolveSalesmanWithBruteForceTest, GraphWithZeroWeights) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveSalesmanWithBruteForce(&graph);

  EXPECT_EQ(result.distance, std::numeric_limits<double>::infinity());
}

TEST(SolveSalesmanWithBruteForceTest, PathCorrectness) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0, 3, 1}, {3, 0, 2}, {1, 2, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveSalesmanWithBruteForce(&graph);

  EXPECT_NE(result.distance, std::numeric_limits<double>::infinity());
  EXPECT_EQ(result.vertices.size(), 4);
  EXPECT_EQ(result.vertices[0], result.vertices[3]);

  std::vector<bool> vertices_visited(3, false);
  for (int i = 0; i < 3; i++) {
    int vertex = result.vertices[i];
    EXPECT_GE(vertex, 0);
    EXPECT_LT(vertex, 3);
    vertices_visited[vertex] = true;
  }

  for (bool visited : vertices_visited) {
    EXPECT_TRUE(visited);
  }
}

TEST(SolveSalesmanWithBruteForceTest, LinearGraph) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveSalesmanWithBruteForce(&graph);

  EXPECT_NE(result.distance, std::numeric_limits<double>::infinity());
  EXPECT_EQ(result.vertices.size(), 4);
}

TEST(SolveSalesmanWithBruteForceTest, SymmetricGraph) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {{0, 2, 1}, {2, 0, 2}, {1, 2, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveSalesmanWithBruteForce(&graph);

  EXPECT_NE(result.distance, std::numeric_limits<double>::infinity());
  EXPECT_EQ(result.vertices.size(), 4);
}

TEST(SolveSalesmanWithBruteForceTest, GraphWithIsolatedVertices) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {
      {0, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveSalesmanWithBruteForce(&graph);

  EXPECT_EQ(result.distance, std::numeric_limits<double>::infinity());
}

TEST(SolveSalesmanWithBruteForceTest, OptimalSolutionForSmallGraph) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {
      {0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveSalesmanWithBruteForce(&graph);

  EXPECT_NE(result.distance, std::numeric_limits<double>::infinity());
  EXPECT_EQ(result.vertices.size(), 5);
  EXPECT_EQ(result.vertices[0], result.vertices[4]);
}

TEST(SolveSalesmanWithBruteForceTest, GraphWithLargeWeights) {
  Graph graph;
  std::vector<std::vector<int>> matrix = {
      {0, 1000, 2000}, {1000, 0, 3000}, {2000, 3000, 0}};
  graph.SetAdjacencyMatrix(matrix);

  TsmResult result = GraphAlgorithms::SolveSalesmanWithBruteForce(&graph);

  EXPECT_NE(result.distance, std::numeric_limits<double>::infinity());
  EXPECT_GT(result.distance, 0);
  EXPECT_EQ(result.vertices.size(), 4);
}