// FSIV

#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


/**
 * @brief Convert a gray image to color RGB.
 * @param img gray input image.
 * @return output color image.
 */
cv::Mat convert_gray_to_rgb(const cv::Mat& img);


/**
 * @brief Multiplies a value to all pixels in the source image: dst <- src * val
 * @param src input image.
 * @param dst resulting image.
 * @param val value to multiply.
 */
void fsiv_mult_safe(const cv::Mat& src, cv::Mat & dst, int val);


/**
 * @brief Adds a scalar to all pixels in the source image: dst <- src + val
 * @param src input image.
 * @param dst resulting image.
 * @param val value to be added.
 */
void fsiv_add_safe(const cv::Mat& src, cv::Mat & dst, int val);


/**
 * @brief Subtracts a scalar to all pixels in the source image: dst <- src - val
 * @param src input image.
 * @param dst resulting image.
 * @param val value to be subtracted.
 */
void fsiv_sub_safe(const cv::Mat& src, cv::Mat & dst, int val);
