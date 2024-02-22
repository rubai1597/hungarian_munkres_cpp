This repository was written with reference to https://brc2.com/the-algorithm-workshop/

Check [this branch](https://github.com/rubai1597/hungarian_munkres_cpp/tree/no_opencv) which does not require OpenCV - Not Stable

# How to Run
### Set OpenCV Library Path (optional)
Specify the path where OpenCV was installed
```bash
export OPENCV_INCLUDE_PATH=/usr/local/include/opencv4
export OPENCV_LIB_PATH=/usr/local/lib
```

### Run Build Script
```bash
./build.sh
```

### Get Results
Get algorithm results of random sized cost matrix (See [this](http://github.com/rubai1597/hungarian_munkres_cpp/blob/develop/src/main.cc?plain=1#L13)).
```bash
./install/hungarian_munkres/hungarian_munkres
```

### Compare results with scipy.optimize.lienar_sum_assignment

Install scipy in your python environment
```bash
pip install tqdm
pip install scipy
```

Run python script
```bash
python check_alogrithm_valid.py --exec_path ./install/hungarian_munkres/hungarian_munkres --num_iter 10000
```