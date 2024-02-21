#include "hungarian.h"

std::vector<position> HungarianAlgorithm::Solve(Mat cost_matrix) {
  int num_rows = cost_matrix.rows_;
  int num_cols = cost_matrix.cols_;
  int matrix_size = num_rows > num_cols ? num_rows : num_cols;

  Mat solution_matrix(cost_matrix);

  float max_val = 0.0f;
  for (int i = 0; i < num_rows; i++)
    for (int j = 0; j < num_cols; j++)
      if (max_val < solution_matrix.at(i, j))
        max_val = solution_matrix.at(i, j);

  solution_matrix.CopyMakeBorder(solution_matrix, 0, matrix_size - num_rows, 0,
                                 matrix_size - num_cols, max_val);

  Mat mask_matrix(matrix_size, matrix_size);

  std::vector<int> row_covered;
  row_covered.resize(matrix_size, 0);
  std::vector<int> col_covered;
  col_covered.resize(matrix_size, 0);

  Step1(solution_matrix, mask_matrix, row_covered, col_covered, matrix_size,
        matrix_size);

  std::vector<position> assignment;
  for (int i = 0; i < num_rows; i++)
    for (int j = 0; j < num_cols; j++)
      if (mask_matrix.at(i, j) == 1) assignment.push_back(position(i, j));

  solution_matrix.release();
  mask_matrix.release();
  row_covered.clear();
  col_covered.clear();

  return assignment;
}

void HungarianAlgorithm::Step1(Mat &cost_matrix, Mat &mask_matrix,
                               std::vector<int> &row_covered,
                               std::vector<int> &col_covered,
                               const int num_rows, const int num_cols) {
  for (int i = 0; i < num_rows; i++) {
    float min_val_in_row = cost_matrix.at(i, 0);
    for (int j = 0; j < num_cols; j++) {
      float val = cost_matrix.at(i, j);
      if (val < min_val_in_row) min_val_in_row = val;
    }
    for (int j = 0; j < num_cols; j++) cost_matrix.at(i, j) -= min_val_in_row;
  }

  return Step2(cost_matrix, mask_matrix, row_covered, col_covered, num_rows,
               num_cols);
}

void HungarianAlgorithm::Step2(Mat &cost_matrix, Mat &mask_matrix,
                               std::vector<int> &row_covered,
                               std::vector<int> &col_covered,
                               const int num_rows, const int num_cols) {
  for (int i = 0; i < num_rows; i++)
    for (int j = 0; j < num_cols; j++) {
      if (cost_matrix.at(i, j) == 0)
        if (row_covered[i] == 0 && col_covered[j] == 0) {
          mask_matrix.at(i, j) = 1;
          row_covered[i] = 1;
          col_covered[j] = 1;
        }
    }
  for (int i = 0; i < num_rows; i++) row_covered[i] = 0;
  for (int j = 0; j < num_cols; j++) col_covered[j] = 0;

  return Step3(cost_matrix, mask_matrix, row_covered, col_covered, num_rows,
               num_cols);
}

void HungarianAlgorithm::Step3(Mat &cost_matrix, Mat &mask_matrix,
                               std::vector<int> &row_covered,
                               std::vector<int> &col_covered,
                               const int num_rows, const int num_cols) {
  for (int i = 0; i < num_rows; i++)
    for (int j = 0; j < num_cols; j++)
      if (mask_matrix.at(i, j) == 1) col_covered[j] = 1;

  int col_count = 0;
  for (int j = 0; j < num_cols; j++)
    if (col_covered[j] == 1) col_count++;

  if (col_count >= num_cols || col_count >= num_rows) return;

  return Step4(cost_matrix, mask_matrix, row_covered, col_covered, num_rows,
               num_cols);
}

void HungarianAlgorithm::Step4(Mat &cost_matrix, Mat &mask_matrix,
                               std::vector<int> &row_covered,
                               std::vector<int> &col_covered,
                               const int num_rows, const int num_cols) {
  int row = -1;
  int col = -1;
  while (true) {
    // Find Zero in A Row
    int zero_is_found = false;
    for (int i = 0; i < num_rows && zero_is_found == false; i++) {
      for (int j = 0; j < num_cols && zero_is_found == false; j++) {
        if (cost_matrix.at(i, j) == 0)
          if (row_covered[i] == 0 && col_covered[j] == 0) {
            row = i;
            col = j;
            zero_is_found = true;
          }
      }
    }

    if (zero_is_found == false) {
      return Step6(cost_matrix, mask_matrix, row_covered, col_covered, num_rows,
                   num_cols);
    }

    mask_matrix.at(row, col) = 2;

    // Find Star In A Row
    bool star_is_found = false;
    for (int j = 0; j < num_cols && star_is_found == false; j++)
      if (mask_matrix.at(row, j) == 1) {
        col = j;
        star_is_found = true;
      }

    if (star_is_found) {
      row_covered[row] = 1;
      col_covered[col] = 0;
    } else {
      std::vector<position> paths = {position(row, col)};

      return Step5(cost_matrix, mask_matrix, row_covered, col_covered, num_rows,
                   num_cols, paths);
    }
  }
}

void HungarianAlgorithm::Step5(Mat &cost_matrix, Mat &mask_matrix,
                               std::vector<int> &row_covered,
                               std::vector<int> &col_covered,
                               const int num_rows, const int num_cols,
                               std::vector<position> &paths) {
  bool done = false;
  while (done == false) {
    bool star_is_found = false;
    for (int i = 0; i < num_rows && star_is_found == false; i++)
      if (mask_matrix.at(i, paths.back().second) == 1) {
        star_is_found = true;
        paths.push_back(position(i, paths.back().second));
      }
    if (star_is_found == false) break;

    bool prime_is_found = false;
    for (int j = 0; j < num_cols && prime_is_found == false; j++)
      if (mask_matrix.at(paths.back().first, j) == 2) {
        prime_is_found = true;
        paths.push_back(position(paths.back().first, j));
      }
  }

  // Augment Paths
  for (position path : paths) {
    if (mask_matrix.at(path.first, path.second) == 1)
      mask_matrix.at(path.first, path.second) = 0;
    else
      mask_matrix.at(path.first, path.second) = 1;
  }

  // Clear Covers and Erase Primes
  for (int i = 0; i < num_rows; i++) {
    row_covered[i] = 0;
    for (int j = 0; j < num_cols; j++) {
      col_covered[j] = 0;
      if (mask_matrix.at(i, j) == 2) mask_matrix.at(i, j) = 0;
    }
  }

  return Step3(cost_matrix, mask_matrix, row_covered, col_covered, num_rows,
               num_cols);
}

void HungarianAlgorithm::Step6(Mat &cost_matrix, Mat &mask_matrix,
                               std::vector<int> &row_covered,
                               std::vector<int> &col_covered,
                               const int num_rows, const int num_cols) {
  float min_val = FLT_MAX;
  // Find Smallest Value
  for (int i = 0; i < num_rows; i++)
    for (int j = 0; j < num_cols; j++) {
      if (row_covered[i] == 0 && col_covered[j] == 0)
        if (min_val > cost_matrix.at(i, j)) min_val = cost_matrix.at(i, j);
    }
  // Subtract Uncovered Columns
  for (int i = 0; i < num_rows; i++)
    for (int j = 0; j < num_cols; j++) {
      if (row_covered[i] == 1) cost_matrix.at(i, j) += min_val;
      if (col_covered[j] == 0) cost_matrix.at(i, j) -= min_val;
    }

  return Step4(cost_matrix, mask_matrix, row_covered, col_covered, num_rows,
               num_cols);
}