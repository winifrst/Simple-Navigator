#ifndef A2_SIMPLENAVIGATOR_V1_0_1_MAIN_H
#define A2_SIMPLENAVIGATOR_V1_0_1_MAIN_H

#include <string.h>

#include <climits>

#include "../graph/graph.h"
#include "../graph_algorithms/graph_algorithms.h"

typedef struct data {
  int error;
  int state;
  int user_choice;
  Graph graph;
} Data;

void MainLoop(Data* data);
int GetUserInputInt(int start, int end);
int PrintMainMenu();
void PrintMatrix(const Graph* graph);
void PrintVector(const std::vector<int>& result);

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

#endif  // A2_SIMPLENAVIGATOR_V1_0_1_MAIN_H