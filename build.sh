# !/bin/bash

set -e

# for rv1109/rv1126 armhf

ROOT_PWD=$( cd "$( dirname $0 )" && cd -P "$( dirname "$SOURCE" )" && pwd )

OPENCV_LIB_PATH="${OPENCV_LIB_PATH:-/usr/local/lib}"
OPENCV_INCLUDE_PATH="${OPENCV_INCLUDE_PATH:-/usr/local/include/opencv4}"

# build rockx
BUILD_DIR=${ROOT_PWD}/build

if [[ ! -d "${BUILD_DIR}" ]]; then
  mkdir -p ${BUILD_DIR}
fi

cd ${BUILD_DIR}
cmake .. \
  -DCMAKE_C_COMPILER=gcc \
  -DCMAKE_CXX_COMPILER=g++ \
  -DOPENCV_LIB_PATH=${OPENCV_LIB_PATH} \
  -DOPENCV_INCLUDE_PATH=${OPENCV_INCLUDE_PATH}
make -j4
make install
cd -