#pragma once
#include <cstring>

#include "../graph/Graph.hpp"

typedef struct data {
  int error;
  int state;
  int user_choice;
  Graph graph;
} Data;

typedef void (*FsmFunc)(Data *data);
void PaintTyan(Data *data);
void LoadGraph(Data *data);
void ExportGraph(Data *data);
void BFS(Data *data);
void DFS(Data *data);
void Dijkstra(Data *data);
void Floyd(Data *data);
void Prim(Data *data);
void TSP(Data *data);
void ClearLastLine(int times);
long long GetTime();