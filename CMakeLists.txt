cmake_minimum_required(VERSION 3.4.1)

project(hungarian_munkres)

set(CMAKE_SYSTEM_NAME Linux)

# SET SYSTEM ROOT PATH
set(SYSROOT /)
set(SYSROOT_LIB ${SYSROOT}/usr/lib)
set(SYSROOT_INCLUDE ${SYSROOT}/usr/include)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c++11 --sysroot=${SYSROOT}")

include_directories("${SYSROOT_INCLUDE}")
include_directories("${OPENCV_INCLUDE_PATH}")

# INCLUDE ADDITIONAL HEADERS
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(
    hungarian_munkres
    src/main.cc
    src/hungarian.cc
)

target_link_libraries(
    hungarian_munkres
    dl
    stdc++fs

    ${OPENCV_LIB_PATH}/libopencv_core.so
    ${OPENCV_LIB_PATH}/libopencv_imgcodecs.so
    ${OPENCV_LIB_PATH}/libopencv_imgproc.so
    ${OPENCV_LIB_PATH}/libopencv_video.so
    ${OPENCV_LIB_PATH}/libopencv_highgui.so
)

# install target and libraries
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install/hungarian_munkres)
install(TARGETS hungarian_munkres DESTINATION ./)