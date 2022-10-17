// FSIV

#pragma once

#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


/**
 * @brief Applies the Filtered image to the original using a gamma value
 * @param O input image.
 * @param F filtered image.
 * @param U unsharp image.
 * @param g value of gamma.
 */
void apply_filter(const cv::Mat O, const cv::Mat F, cv::Mat& U, const double g);


/**
 * @brief Select the type of filter to use
 * @param O input image.
 * @param F filtered image.
 * @param k kernel size.
 * @param option filter type.
 */
void use_filter(const cv::Mat O, cv::Mat F, const int k, const int option);
