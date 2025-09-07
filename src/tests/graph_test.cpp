#include "../graph/graph.h"

#include <gtest/gtest.h>

#include <fstream>
#include <sstream>

TEST(GraphTest, LoadGraphFromFile) {
  const std::string testFilename = "TEEEEEAST";

  std::ofstream outFile(testFilename);
  outFile << "3\n";
  outFile << "0 1 0\n";
  outFile << "1 0 1\n";
  outFile << "0 1 0\n";
  outFile.close();

  Graph graph;

  int result = graph.LoadGraphFromFile(testFilename);

  ASSERT_EQ(result, EXIT_SUCCESS);

  ASSERT_EQ(graph.verticesCount, 3);

  ASSERT_EQ(graph.adjacencyMatrix[0][0], 0);
  ASSERT_EQ(graph.adjacencyMatrix[0][1], 1);
  ASSERT_EQ(graph.adjacencyMatrix[0][2], 0);
  ASSERT_EQ(graph.adjacencyMatrix[1][0], 1);
  ASSERT_EQ(graph.adjacencyMatrix[1][1], 0);
  ASSERT_EQ(graph.adjacencyMatrix[1][2], 1);
  ASSERT_EQ(graph.adjacencyMatrix[2][0], 0);
  ASSERT_EQ(graph.adjacencyMatrix[2][1], 1);
  ASSERT_EQ(graph.adjacencyMatrix[2][2], 0);

  std::remove(testFilename.c_str());
}

TEST(GraphTest, ExportGraphToDot) {
  Graph graph;

  graph.verticesCount = 3;
  graph.adjacencyMatrix = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};

  const std::string testFilename = "test_graph.dot";

  int result = graph.ExportGraphToDot(testFilename);

  ASSERT_EQ(result, EXIT_SUCCESS);

  std::ifstream file(testFilename);
  ASSERT_TRUE(file.is_open());

  std::string line;
  std::string content;
  while (std::getline(file, line)) {
    content += line + "\n";
  }
  file.close();

  std::string expectedContent =
      "graph graphname {\n"
      "    a;\n"
      "    b;\n"
      "    c;\n"
      "    a -- b;\n"
      "    b -- c;\n"
      "}\n";

  ASSERT_EQ(content, expectedContent);

  std::remove(testFilename.c_str());
}