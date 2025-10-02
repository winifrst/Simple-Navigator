#include "Main.hpp"

#include "UserInterface.hpp"

int main() {
  Data data = {0, 0, 0, Graph()};
  MainLoop(&data);
  return data.error;
}

/**
 * Основной цикл программы
 * @param data Указатель на набор данных
 */
void MainLoop(Data *data) {
  while (PrintMainMenu() && (data->user_choice = GetUserInputInt(0, 9)) != 9) {
    data->state = data->state * 10 + data->user_choice;

    FsmFunc fsm_table[9] = {PaintTyan, LoadGraph, ExportGraph, BFS, DFS,
                            Dijkstra,  Floyd,     Prim,        TSP};
    FsmFunc FsmAction = fsm_table[data->state];
    if (FsmAction) {
      FsmAction(data);
    }
  }
}