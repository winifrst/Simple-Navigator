#pragma once

#include <string.h>
#include <sys/time.h>

#include <climits>

#include "../algorithms/GraphAlgorithms.hpp"
#include "../graph/Graph.hpp"

typedef struct data {
  int error;
  int state;
  int user_choice;
  Graph graph;
} Data;

void MainLoop(Data* data);
int GetUserInputInt(int start, int end);
int PrintMainMenu();
void PrintMatrix(const std::vector<std::vector<int>>& adjacencyMatrix);
void PrintVector(const std::vector<int>& result);
void PrintHeader(const char* title);
void PrintResultFooter();
long long GetTime();

typedef void (*FsmFunc)(Data* data);
void PaintTyan(Data* data);
void LoadGraph(Data* data);
void ExportGraph(Data* data);
void BFS(Data* data);
void DFS(Data* data);
void Dijkstra(Data* data);
void Floyd(Data* data);
void Prim(Data* data);
void Kamen(Data* data);
