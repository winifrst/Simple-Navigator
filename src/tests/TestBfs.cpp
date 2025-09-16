#include <gtest/gtest.h>

#include <fstream>
#include <set>
#include <vector>

#include "../algorithms/GraphAlgorithms.hpp"
#include "../graph/Graph.hpp"

TEST(BFSTest, EmptyGraph) {
  Graph emptyGraph;
  // emptyGraph.verticesCount = 0;
  auto result = GraphAlgorithms::BreadthFirstSearch(emptyGraph, 0);
  EXPECT_TRUE(result.empty());
}

TEST(BFSTest, SingleVertex) {
  Graph graph;
  graph.LoadGraphFromFile("../data-samples/true_graph_1.txt");
  auto result = GraphAlgorithms::BreadthFirstSearch(graph, 0);
  EXPECT_EQ(result, std::vector<int>({0}));
}

TEST(BFSTest, SmallGraph) {
  Graph graph;
  graph.LoadGraphFromFile("../data-samples/true_graph_2.txt");
  auto result = GraphAlgorithms::BreadthFirstSearch(graph, 0);
  EXPECT_EQ(result, std::vector<int>({0, 1}));
}

TEST(BFSTest, LargeGraph) {
  Graph graph;
  graph.LoadGraphFromFile("../data-samples/true_graph_3.txt");
  auto result = GraphAlgorithms::BreadthFirstSearch(graph, 0);

  EXPECT_EQ(result.size(), 11);
  EXPECT_EQ(result[0], 0);

  std::set<int> uniqueVertices(result.begin(), result.end());
  EXPECT_EQ(uniqueVertices.size(), 11);
}

TEST(BFSTest, DirectedGraph) {
  Graph graph;
  graph.LoadGraphFromFile("../data-samples/true_graph_4.txt");
  auto result = GraphAlgorithms::BreadthFirstSearch(graph, 0);
  EXPECT_EQ(result, std::vector<int>({0, 1, 2, 3, 4, 5}));
}

TEST(BFSTest, InvalidStartVertex) {
  Graph graph;
  graph.LoadGraphFromFile("../data-samples/true_graph_2.txt");
  auto result = GraphAlgorithms::BreadthFirstSearch(graph, -1);
  EXPECT_TRUE(result.empty());

  result = GraphAlgorithms::BreadthFirstSearch(graph, 100);
  EXPECT_TRUE(result.empty());
}

TEST(SearchAlgorithmsTest, BFSvsDFS_MoreComplexGraph) {
  Graph graph;
  // graph.verticesCount = 7;

  graph.SetAdjacencyMatrix({{0, 1, 1, 0, 0, 0, 0},
                            {0, 0, 0, 1, 1, 0, 0},
                            {0, 0, 0, 0, 0, 1, 1},
                            {0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0}});

  auto bfs = GraphAlgorithms::BreadthFirstSearch(graph, 0);
  auto dfs = GraphAlgorithms::DepthFirstSearch(graph, 0);

  EXPECT_NE(bfs, dfs);
}

TEST(SearchAlgorithmsTest, WithWeights) {
  Graph graph;
  graph.LoadGraphFromFile("../data-samples/true_graph_3.txt");

  auto bfs = GraphAlgorithms::BreadthFirstSearch(graph, 0);
  auto dfs = GraphAlgorithms::DepthFirstSearch(graph, 0);

  EXPECT_EQ(bfs.size(), 11);
  EXPECT_EQ(dfs.size(), 11);
}