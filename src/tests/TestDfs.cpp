#include <gtest/gtest.h>

#include <fstream>
#include <set>
#include <vector>

#include "../algorithms/GraphAlgorithms.hpp"
#include "../graph/Graph.hpp"

TEST(DFSTest, EmptyGraph) {
  Graph emptyGraph;

  auto result = GraphAlgorithms::DepthFirstSearch(emptyGraph, 0);
  EXPECT_TRUE(result.empty());
}

TEST(DFSTest, SingleVertex) {
  Graph graph;
  graph.LoadGraphFromFile("../data-samples/true_graph_1.txt");
  auto result = GraphAlgorithms::DepthFirstSearch(graph, 0);
  EXPECT_EQ(result, std::vector<int>({0}));
}

TEST(DFSTest, SmallGraph) {
  Graph graph;
  graph.LoadGraphFromFile("../data-samples/true_graph_2.txt");
  auto result = GraphAlgorithms::DepthFirstSearch(graph, 0);
  EXPECT_EQ(result, std::vector<int>({0, 1}));
}

TEST(DFSTest, LargeGraph) {
  Graph graph;
  graph.LoadGraphFromFile("../data-samples/true_graph_3.txt");
  auto result = GraphAlgorithms::DepthFirstSearch(graph, 0);

  EXPECT_EQ(result.size(), static_cast<const unsigned long>(11));
  EXPECT_EQ(result[0], 0);

  std::set<int> uniqueVertices(result.begin(), result.end());
  EXPECT_EQ(uniqueVertices.size(), static_cast<const unsigned long>(11));
}

TEST(DFSTest, DirectedGraph) {
  Graph graph;
  graph.LoadGraphFromFile("../data-samples/true_graph_4.txt");
  auto result = GraphAlgorithms::DepthFirstSearch(graph, 0);
  EXPECT_EQ(result, std::vector<int>({0, 1, 2, 3, 4, 5}));
}

TEST(DFSTest, InvalidStartVertex) {
  Graph graph;
  graph.LoadGraphFromFile("../data-samples/true_graph_2.txt");
  auto result = GraphAlgorithms::DepthFirstSearch(graph, -1);
  EXPECT_TRUE(result.empty());

  result = GraphAlgorithms::DepthFirstSearch(graph, 100);
  EXPECT_TRUE(result.empty());
}
