#ifndef HUNGARIAN_H_
#define HUNGARIAN_H_

#include <vector>

#include "float.h"

typedef std::pair<int, int> position;

template <typename T>
class Mat_ {
 public:
  Mat_<T>() {
    rows_ = 0;
    cols_ = 0;
  };
  Mat_<T>(int rows, int cols) {
    rows_ = rows;
    cols_ = cols;
    data.resize(rows * cols, 0);
  };
  Mat_<T>(const Mat_<T> &mat) {
    data = mat.data;
    rows_ = mat.rows_;
    cols_ = mat.cols_;
  }

  std::vector<T> data;

  int rows_;
  int cols_;

  T &at(int row, int col) { return data[cols_ * row + col]; };

  Mat_<T> t() {
    int dst_rows = cols_;
    int dst_cols = rows_;
    Mat_<T> dst = Mat_<T>(dst_rows, dst_cols);
    dst.data.resize(dst_rows * dst_cols, 0);
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++) {
        int index = dst_cols * j + i;
        dst.data[index] = data[cols_ * i + j];
      }
    return dst;
  }

  void CopyMakeBorder(Mat_ &dst, int top, int bottom, int left, int right,
                      T value) {
    int dst_rows = dst.rows_ + top + bottom;
    int dst_cols = dst.rows_ + top + bottom;

    std::vector<T> new_data;
    new_data.resize(dst_rows * dst_cols, value);
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++) {
        int index = dst_cols * (top + i) + (left + j);
        new_data[index] = data[cols_ * i + j];
      }
    dst.data = new_data;
    dst.rows_ = dst_rows;
    dst.cols_ = dst_cols;
  };

  void release() {
    data.clear();
    data.shrink_to_fit();
    rows_ = 0;
    cols_ = 0;
  }

 protected:
 private:
};

typedef Mat_<float> Mat;

class HungarianAlgorithm {
 public:
  static std::vector<position> Solve(Mat cost_matrix);

 private:
  HungarianAlgorithm(){};
  ~HungarianAlgorithm(){};

  static void Step1(Mat &cost_matrix, Mat &mask_matrix,
                    std::vector<int> &row_covered,
                    std::vector<int> &col_covered, const int num_rows,
                    const int num_cols);
  static void Step2(Mat &cost_matrix, Mat &mask_matrix,
                    std::vector<int> &row_covered,
                    std::vector<int> &col_covered, const int num_rows,
                    const int num_cols);
  static void Step3(Mat &cost_matrix, Mat &mask_matrix,
                    std::vector<int> &row_covered,
                    std::vector<int> &col_covered, const int num_rows,
                    const int num_cols);
  static void Step4(Mat &cost_matrix, Mat &mask_matrix,
                    std::vector<int> &row_covered,
                    std::vector<int> &col_covered, const int num_rows,
                    const int num_cols);
  static void Step5(Mat &cost_matrix, Mat &mask_matrix,
                    std::vector<int> &row_covered,
                    std::vector<int> &col_covered, const int num_rows,
                    const int num_cols, std::vector<position> &paths);
  static void Step6(Mat &cost_matrix, Mat &mask_matrix,
                    std::vector<int> &row_covered,
                    std::vector<int> &col_covered, const int num_rows,
                    const int num_cols);
};

#endif  // HUNGARIAN_H_