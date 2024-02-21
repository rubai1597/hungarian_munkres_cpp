#ifndef HUNGARIAN_H_
#define HUNGARIAN_H_

#include <vector>

#include "opencv2/opencv.hpp"

typedef std::pair<int, int> position;

class HungarianAlgorithm {
 public:
  static std::vector<position> Solve(cv::InputArray cost_matrix);

 private:
  HungarianAlgorithm(){};
  ~HungarianAlgorithm(){};

  static void Step1(cv::Mat &cost_matrix, cv::Mat &mask_matrix,
                    std::vector<int> &row_covered,
                    std::vector<int> &col_covered, const int num_rows,
                    const int num_cols);
  static void Step2(cv::Mat &cost_matrix, cv::Mat &mask_matrix,
                    std::vector<int> &row_covered,
                    std::vector<int> &col_covered, const int num_rows,
                    const int num_cols);
  static void Step3(cv::Mat &cost_matrix, cv::Mat &mask_matrix,
                    std::vector<int> &row_covered,
                    std::vector<int> &col_covered, const int num_rows,
                    const int num_cols);
  static void Step4(cv::Mat &cost_matrix, cv::Mat &mask_matrix,
                    std::vector<int> &row_covered,
                    std::vector<int> &col_covered, const int num_rows,
                    const int num_cols);
  static void Step5(cv::Mat &cost_matrix, cv::Mat &mask_matrix,
                    std::vector<int> &row_covered,
                    std::vector<int> &col_covered, const int num_rows,
                    const int num_cols, std::vector<position> &paths);
  static void Step6(cv::Mat &cost_matrix, cv::Mat &mask_matrix,
                    std::vector<int> &row_covered,
                    std::vector<int> &col_covered, const int num_rows,
                    const int num_cols);
};

#endif  // HUNGARIAN_H_