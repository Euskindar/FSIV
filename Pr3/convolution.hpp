// FSIV

#pragma once

#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


/**
 * @brief The algorithm to do the convolution of an image.
 * @param src Input image. Allways in 3 channles.
 * @param dst Output image. Allways in 3 channles.
 * @param kernel Kernel matrix.
 * @param padding Value of the radius of the kernel. Same as the padding of the src image.
 */
void fsiv_convolution(const cv::Mat& src, cv::Mat& dst, const cv::Mat& kernel, int padding);


/**
 * @brief Function to print the kernel values.
 * @param mat Kernel matrix to be printed.
 */
void show_matrix( const cv::Mat mat);