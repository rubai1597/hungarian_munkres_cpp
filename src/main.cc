#include <chrono>
#include <iostream>
#include <random>

#include "hungarian.h"

namespace chrono = std::chrono;
typedef chrono::high_resolution_clock::time_point time_point;

int main(int argc, char *argv[]) {
  srand((unsigned int)time(NULL));

  int kMinRow = 3;
  int kMinCol = 3;
  int kMaxRow = 6;
  int kMaxCol = 6;

  // Generate Random Sized Cost Matrix
  int num_rows = kMinRow + rand() % (kMaxRow - kMinRow + 1);
  int num_cols = kMinCol + rand() % (kMaxCol - kMinCol + 1);

  Mat cost_matrix(num_rows, num_cols);
  for (int i = 0; i < num_rows; i++)
    for (int j = 0; j < num_cols; j++)
      cost_matrix.at(i, j) = (float)rand() / (float)RAND_MAX;

  printf("Cost matrix is initialized (%d x %d)\n", num_rows, num_cols);
  printf("[");
  for (int i = 0; i < num_rows; i++) {
    if (i != 0) printf(" ");
    for (int j = 0; j < num_cols; j++) {
      std::cout << cost_matrix.at(i, j);
      if (j != num_cols - 1) std::cout << ", ";
    }
    if (i != num_rows - 1)
      std::cout << std::endl;
    else
      std::cout << "]" << std::endl;
  }

  std::vector<position> assignment = HungarianAlgorithm::Solve(cost_matrix);
  printf("Assignments:\n\t");
  for (auto position : assignment) {
    printf("(%d, %d), ", position.first, position.second);
  }
  printf("\n");

  cost_matrix.release();

  return 0;
}