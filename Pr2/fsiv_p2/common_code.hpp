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


// ------------------------------------------------------------------------------------
// ---------------------------------- RGB ---------------------------------------------
// ------------------------------------------------------------------------------------


/**
 * @brief Multiplies a value to independent channels in the source image: dst <- src * val
 * @param src input image.
 * @param dst resulting image.
 * @param val_R value to multiply RED channel.
 * @param val_G value to multiply GREEN channel.
 * @param val_B value to multiply BLUE channel.
 */

void fsiv_mult_safe_RGB(const cv::Mat& src, cv::Mat& dst, int val_R, int val_G, int val_B);


/**
 * @brief Adds a scalar to independent channels in the source image: dst <- src + val
 * @param src input image.
 * @param dst resulting image.
 * @param val_R value to add RED channel.
 * @param val_G value to add GREEN channel.
 * @param val_B value to add BLUE channel.
 */
void fsiv_add_safe_RGB(const cv::Mat& src, cv::Mat& dst, int val_R, int val_G, int val_B);


/**
 * @brief Subtracts a scalar to independent channels in the source image: dst <- src - val
 * @param src input image.
 * @param dst resulting image.
 * @param val_R value to subtract RED channel.
 * @param val_G value to subtract GREEN channel.
 * @param val_B value to subtract BLUE channel.
 */
void fsiv_sub_safe_RGB(const cv::Mat& src, cv::Mat & dst, int val_R, int val_G, int val_B);
