#pragma once
#include <vector>

inline bool MatricesEqual(const std::vector<std::vector<int>> &a,
                          const std::vector<std::vector<int>> &b) {
  if (a.size() != b.size()) {
    return false;
  }
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i].size() != b[i].size()) {
      return false;
    }
    for (size_t j = 0; j < a[i].size(); ++j) {
      if (a[i][j] != b[i][j]) {
        return false;
      }
    }
  }
  return true;
}