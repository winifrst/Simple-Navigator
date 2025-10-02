#pragma once
#include <cstdio>
#include <cstring>
#include <vector>

int GetUserInputInt(int start, int end);
int PrintMainMenu();
void PrintMatrix(const std::vector<std::vector<int>> &adjacencyMatrix);
void PrintVector(const std::vector<int> &result);
void PrintHeader(const char *title);
void PrintResultFooter();