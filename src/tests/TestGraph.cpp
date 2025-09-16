#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <sstream>

#include "../graph/Graph.hpp"

void CreateTestFile(const std::string& filename, const std::string& content) {
  std::ofstream file(filename);
  file << content;
  file.close();
}

void RemoveTestFile(const std::string& filename) {
  if (std::filesystem::exists(filename)) {
    std::filesystem::remove(filename);
  }
}

bool CompareFiles(const std::string& filename1, const std::string& filename2) {
  std::ifstream file1(filename1);
  std::ifstream file2(filename2);

  if (!file1.is_open() || !file2.is_open()) {
    return false;
  }

  std::string content1((std::istreambuf_iterator<char>(file1)),
                       std::istreambuf_iterator<char>());
  std::string content2((std::istreambuf_iterator<char>(file2)),
                       std::istreambuf_iterator<char>());

  return content1 == content2;
}

TEST(GraphLoadTest, LoadFalseGraph1) {
  Graph graph;
  EXPECT_EQ(EXIT_FAILURE,
            graph.LoadGraphFromFile("../data-samples/false_graph_1.txt"));
  EXPECT_TRUE(graph.GetAdjacencyMatrix().empty());
  EXPECT_EQ(graph.GetVerticesCount(), 0);
}

TEST(GraphLoadTest, LoadFalseGraph2) {
  Graph graph;
  EXPECT_EQ(EXIT_FAILURE,
            graph.LoadGraphFromFile("../data-samples/false_graph_2.txt"));
  EXPECT_TRUE(graph.GetAdjacencyMatrix().empty());
  EXPECT_EQ(graph.GetVerticesCount(), 0);
}

TEST(GraphLoadTest, LoadFalseGraph3) {
  Graph graph;
  EXPECT_EQ(EXIT_FAILURE,
            graph.LoadGraphFromFile("../data-samples/false_graph_3.txt"));
  EXPECT_TRUE(graph.GetAdjacencyMatrix().empty());
  EXPECT_EQ(graph.GetVerticesCount(), 0);
}

TEST(GraphLoadTest, LoadFalseGraph4) {
  Graph graph;
  EXPECT_EQ(EXIT_FAILURE,
            graph.LoadGraphFromFile("../data-samples/false_graph_4.txt"));
  EXPECT_TRUE(graph.GetAdjacencyMatrix().empty());
  EXPECT_EQ(graph.GetVerticesCount(), 0);
}

TEST(GraphLoadTest, LoadFalseGraph5) {
  Graph graph;
  EXPECT_EQ(EXIT_FAILURE,
            graph.LoadGraphFromFile("../data-samples/false_graph_5.txt"));
  EXPECT_TRUE(graph.GetAdjacencyMatrix().empty());
  EXPECT_EQ(graph.GetVerticesCount(), 0);
}

TEST(GraphLoadTest, LoadTrueGraph1) {
  Graph graph;
  EXPECT_EQ(EXIT_SUCCESS,
            graph.LoadGraphFromFile("../data-samples/true_graph_1.txt"));
  EXPECT_FALSE(graph.GetAdjacencyMatrix().empty());
  EXPECT_GT(graph.GetVerticesCount(), 0);
}

TEST(GraphLoadTest, LoadTrueGraph2) {
  Graph graph;
  EXPECT_EQ(EXIT_SUCCESS,
            graph.LoadGraphFromFile("../data-samples/true_graph_2.txt"));
  EXPECT_FALSE(graph.GetAdjacencyMatrix().empty());
  EXPECT_GT(graph.GetVerticesCount(), 0);
}

TEST(GraphLoadTest, LoadTrueGraph3) {
  Graph graph;
  EXPECT_EQ(EXIT_SUCCESS,
            graph.LoadGraphFromFile("../data-samples/true_graph_3.txt"));
  EXPECT_FALSE(graph.GetAdjacencyMatrix().empty());
  EXPECT_GT(graph.GetVerticesCount(), 0);
}

TEST(GraphLoadTest, LoadNonexistentFile) {
  Graph graph;
  EXPECT_EQ(EXIT_FAILURE, graph.LoadGraphFromFile("none_graph"));
}

TEST(GraphLoadTest, LoadValidGraphFromGeneratedFile) {
  const std::string testFilename = "test_valid_graph.txt";
  CreateTestFile(testFilename, "3\n0 1 0\n1 0 1\n0 1 0\n");

  Graph graph;
  EXPECT_EQ(EXIT_SUCCESS, graph.LoadGraphFromFile(testFilename));

  ASSERT_EQ(graph.GetVerticesCount(), 3);
  ASSERT_EQ(graph.GetAdjacencyMatrix().size(), 3);
  ASSERT_EQ(graph.GetAdjacencyMatrix()[0].size(), 3);

  EXPECT_EQ(graph.GetAdjacencyMatrix()[0][0], 0);
  EXPECT_EQ(graph.GetAdjacencyMatrix()[0][1], 1);
  EXPECT_EQ(graph.GetAdjacencyMatrix()[0][2], 0);
  EXPECT_EQ(graph.GetAdjacencyMatrix()[1][0], 1);
  EXPECT_EQ(graph.GetAdjacencyMatrix()[1][1], 0);
  EXPECT_EQ(graph.GetAdjacencyMatrix()[1][2], 1);
  EXPECT_EQ(graph.GetAdjacencyMatrix()[2][0], 0);
  EXPECT_EQ(graph.GetAdjacencyMatrix()[2][1], 1);
  EXPECT_EQ(graph.GetAdjacencyMatrix()[2][2], 0);

  RemoveTestFile(testFilename);
}

TEST(GraphLoadTest, LoadInvalidGraphWithNegativeWeights) {
  const std::string testFilename = "test_negative_weights.txt";
  CreateTestFile(testFilename, "2\n0 -1\n1 0\n");

  Graph graph;
  EXPECT_EQ(EXIT_FAILURE, graph.LoadGraphFromFile(testFilename));
  EXPECT_TRUE(graph.GetAdjacencyMatrix().empty());
  EXPECT_EQ(graph.GetVerticesCount(), 0);

  RemoveTestFile(testFilename);
}

TEST(GraphLoadTest, LoadInvalidGraphInsufficientData) {
  const std::string testFilename = "test_insufficient_data.txt";
  CreateTestFile(testFilename, "2\n0 1\n");

  Graph graph;
  EXPECT_EQ(EXIT_FAILURE, graph.LoadGraphFromFile(testFilename));
  EXPECT_TRUE(graph.GetAdjacencyMatrix().empty());
  EXPECT_EQ(graph.GetVerticesCount(), 0);

  RemoveTestFile(testFilename);
}

TEST(GraphLoadTest, LoadInvalidGraphExtraData) {
  const std::string testFilename = "test_extra_data.txt";
  CreateTestFile(testFilename, "2\n0 1\n1 0\n extra data\n");

  Graph graph;
  EXPECT_EQ(EXIT_FAILURE, graph.LoadGraphFromFile(testFilename));
  EXPECT_TRUE(graph.GetAdjacencyMatrix().empty());
  EXPECT_EQ(graph.GetVerticesCount(), 0);

  RemoveTestFile(testFilename);
}

TEST(GraphExportTest, ExportUndirectedGraphToDot) {
  const std::string testFilename = "test_undirected.dot";

  Graph graph;
  // graph.GetVerticesCount() = 3;
  graph.SetAdjacencyMatrix({{0, 1, 0}, {1, 0, 1}, {0, 1, 0}});

  EXPECT_EQ(EXIT_SUCCESS, graph.ExportGraphToDot(testFilename));

  std::ifstream file(testFilename);
  ASSERT_TRUE(file.is_open());

  std::string content;
  std::string line;
  while (std::getline(file, line)) {
    content += line + "\n";
  }
  file.close();

  EXPECT_TRUE(content.find("graph graphname {") != std::string::npos);
  EXPECT_TRUE(content.find("a;") != std::string::npos);
  EXPECT_TRUE(content.find("b;") != std::string::npos);
  EXPECT_TRUE(content.find("c;") != std::string::npos);
  EXPECT_TRUE(content.find("a -- b;") != std::string::npos);
  EXPECT_TRUE(content.find("b -- c;") != std::string::npos);
  EXPECT_TRUE(content.find("->") == std::string::npos);

  RemoveTestFile(testFilename);
}

TEST(GraphExportTest, ExportDirectedGraphToDot) {
  const std::string testFilename = "test_directed.dot";

  Graph graph;
  // graph.GetVerticesCount() = 2;
  graph.SetAdjacencyMatrix({{0, 1}, {0, 0}});

  EXPECT_EQ(EXIT_SUCCESS, graph.ExportGraphToDot(testFilename));

  std::ifstream file(testFilename);
  ASSERT_TRUE(file.is_open());

  std::string content;
  std::string line;
  while (std::getline(file, line)) {
    content += line + "\n";
  }
  file.close();

  EXPECT_TRUE(content.find("digraph graphname {") != std::string::npos);
  EXPECT_TRUE(content.find("a;") != std::string::npos);
  EXPECT_TRUE(content.find("b;") != std::string::npos);
  EXPECT_TRUE(content.find("a -> b;") != std::string::npos);
  EXPECT_TRUE(content.find("--") == std::string::npos);

  RemoveTestFile(testFilename);
}

TEST(GraphExportTest, ExportEmptyGraphToDot) {
  const std::string testFilename = "test_empty.dot";

  Graph graph;
  // graph.GetVerticesCount() = 0;
  graph.SetAdjacencyMatrix({});

  EXPECT_EQ(EXIT_FAILURE, graph.ExportGraphToDot(testFilename));
  EXPECT_FALSE(std::filesystem::exists(testFilename));
}

TEST(GraphExportTest, ExportGraphWithEmptyMatrixToDot) {
  const std::string testFilename = "test_empty_matrix.dot";

  Graph graph;
  // graph.GetVerticesCount() = 2;
  graph.SetAdjacencyMatrix({});

  EXPECT_EQ(EXIT_FAILURE, graph.ExportGraphToDot(testFilename));
  EXPECT_FALSE(std::filesystem::exists(testFilename));
}

TEST(GraphExportTest, ExportUndirectedGraphCompareWithTrue1) {
  Graph graph;
  // graph.GetVerticesCount() = 4;
  graph.SetAdjacencyMatrix(
      {{0, 1, 0, 0}, {1, 0, 1, 1}, {0, 1, 0, 0}, {0, 1, 0, 0}});

  EXPECT_EQ(EXIT_SUCCESS, graph.ExportGraphToDot("export.dot"));
  EXPECT_TRUE(CompareFiles("export.dot", "../data-samples/true_dot_1.dot"));
  RemoveTestFile("export.dot");
}

TEST(GraphExportTest, ExportDirectedGraphCompareWithTrue2) {
  Graph graph;
  // graph.GetVerticesCount() = 4;
  graph.SetAdjacencyMatrix(
      {{0, 1, 0, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}});

  EXPECT_EQ(EXIT_SUCCESS, graph.ExportGraphToDot("export.dot"));
  EXPECT_TRUE(CompareFiles("export.dot", "../data-samples/true_dot_2.dot"));
  RemoveTestFile("export.dot");
}

TEST(GraphExportTest, ExportUndirectedGraphCompareWithFalse1) {
  Graph graph;
  // graph.GetVerticesCount() = 4;
  graph.SetAdjacencyMatrix(
      {{0, 1, 0, 0}, {1, 0, 1, 1}, {0, 1, 0, 0}, {0, 1, 0, 0}});

  EXPECT_EQ(EXIT_SUCCESS, graph.ExportGraphToDot("export.dot"));
  EXPECT_FALSE(CompareFiles("export.dot", "../data-samples/false_dot_1.dot"));
  RemoveTestFile("export.dot");
}

TEST(GraphExportTest, ExportDirectedGraphCompareWithFalse2) {
  Graph graph;
  // graph.GetVerticesCount() = 4;
  graph.SetAdjacencyMatrix(
      {{0, 1, 0, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}});

  EXPECT_EQ(EXIT_SUCCESS, graph.ExportGraphToDot("export.dot"));
  EXPECT_FALSE(CompareFiles("export.dot", "../data-samples/false_dot_2.dot"));
  RemoveTestFile("export.dot");
}

TEST(GraphExportTest, ExportGraphWithZeroVertices) {
  Graph graph;
  // graph.GetVerticesCount() = 0;
  graph.SetAdjacencyMatrix({});

  EXPECT_EQ(EXIT_FAILURE, graph.ExportGraphToDot("export.dot"));
  EXPECT_FALSE(std::filesystem::exists("export.dot"));
}

TEST(GraphExportTest, ExportLargeGraphWithoutEdges) {
  Graph graph;
  // graph.GetVerticesCount() = 27;
  graph.SetAdjacencyMatrix(
      std::vector<std::vector<int>>(27, std::vector<int>(27, 0)));

  EXPECT_EQ(EXIT_SUCCESS, graph.ExportGraphToDot("export.dot"));
  EXPECT_TRUE(CompareFiles("export.dot", "../data-samples/true_dot_3.dot"));
  RemoveTestFile("export.dot");
}

TEST(GraphExportTest, ExportLargeGraphWithEdgesAndVertexNames) {
  Graph graph;
  // graph.GetVerticesCount() = 29;
  std::vector<std::vector<int>> matrix(29, std::vector<int>(29, 0));

  matrix[26][27] = 1;
  matrix[26][28] = 1;
  matrix[27][28] = 1;
  graph.SetAdjacencyMatrix(matrix);

  EXPECT_EQ(EXIT_SUCCESS, graph.ExportGraphToDot("export.dot"));
  EXPECT_TRUE(CompareFiles("export.dot", "../data-samples/true_dot_4.dot"));

  std::ifstream file("export.dot");
  std::string content((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());

  EXPECT_TRUE(content.find("a1") != std::string::npos);
  EXPECT_TRUE(content.find("b1") != std::string::npos);
  EXPECT_TRUE(content.find("c1") != std::string::npos);

  RemoveTestFile("export.dot");
}

TEST(GraphExportTest, ExportGraphWithEmptyMatrix) {
  Graph graph;
  // graph.GetVerticesCount() = 3;
  graph.SetAdjacencyMatrix({});

  EXPECT_EQ(EXIT_FAILURE, graph.ExportGraphToDot("export.dot"));
  EXPECT_FALSE(std::filesystem::exists("export.dot"));
}

// TEST(GraphExportTest, ExportGraphWithMismatchedMatrixSize) {
//   Graph graph;
//   graph.SetVerticesCount(3);
//   graph.SetAdjacencyMatrix({{0, 1}, {1, 0}});

//   EXPECT_EQ(EXIT_FAILURE, graph.ExportGraphToDot("export.dot"));
//   EXPECT_FALSE(std::filesystem::exists("export.dot"));
// }

// TEST(GraphExportTest, ExportGraphWithWeights) {
//   Graph graph;
//   graph.GetVerticesCount() = 3;
//   graph.GetAdjacencyMatrix() = {{0, 5, 0}, {5, 0, 2}, {0, 2, 0}};

//   EXPECT_EQ(EXIT_SUCCESS, graph.ExportGraphToDot("export.dot"));

//   std::ifstream file("export.dot");
//   std::string content((std::istreambuf_iterator<char>(file)),
//                       std::istreambuf_iterator<char>());

//   EXPECT_TRUE(content.find("a -- b") != std::string::npos);
//   EXPECT_TRUE(content.find("b -- c") != std::string::npos);

//   RemoveTestFile("export.dot");
// }