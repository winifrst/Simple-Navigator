#ifndef A2_SIMPLENAVIGATOR_V1_0_1_MAIN_H
#define A2_SIMPLENAVIGATOR_V1_0_1_MAIN_H

// #include "common.h"
#include <string.h>

#include <climits>
// #include <vector>

#include "../graph/graph.h"
#include "../graph_algorithms/graph_algorithms.h"

typedef struct data {
  int error;
  int state;
  int user_choice;
  Graph graph;
} Data;

void main_loop(Data* data);
int get_user_input_int(int start, int end);
int print_main_menu();
void print_matrix(const Graph* graph);
// void print_array(int count, int* array);
void print_vector(const std::vector<int>& result);

typedef void (*fsm_func)(Data* data);
void paint_tyan(Data* data);
void load_graph(Data* data);
void export_graph(Data* data);
void bfs(Data* data);
void dfs(Data* data);
void deikstra(Data* data);
void floid(Data* data);
void prim(Data* data);
void kamen(Data* data);

#endif  // A2_SIMPLENAVIGATOR_V1_0_1_MAIN_H