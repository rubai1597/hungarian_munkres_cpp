#include <chrono>
#include <iostream>

#include "hungarian.h"
#include "opencv2/opencv.hpp"

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

  cv::Mat cost_matrix(cv::Size(num_cols, num_rows), CV_32FC1);
  cv::randu(cost_matrix, 0.0, 1.0);

  printf("Cost matrix is initialized (%d x %d)\n", num_rows, num_cols);
  std::cout << cost_matrix << std::endl;

  std::vector<position> assignment = HungarianAlgorithm::Solve(cost_matrix);
  printf("Assignments:\n\t");
  for (auto position : assignment) {
    printf("(%d, %d), ", position.first, position.second);
  }
  printf("\n");

  cost_matrix.release();

  return 0;
}