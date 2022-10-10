// FSIV

#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
// #include <iostream>

/**
 * @brief Convert a gray image to color RGB.
 * @param img gray input image.
 * @return output color image.
 */
cv::Mat convert_gray_to_rgb(const cv::Mat& img);

/**
 * @brief Conviert from color to gray.
 * @param img input color image.
 * @return output gray image.
 */
cv::Mat convert_rgb_to_gray(const cv::Mat& img);

/**
 * @brief Generates a binary mask 0/255 with a rectangular ROI.
 * @param img_width wrt output image mask 
 * @param img_height wrt output image mask 
 * @param x top left corner X coordinate of the ROI
 * @param y top left corner Y coordinate of the ROI
 * @param rect_width width of the ROI.
 * @param rect_height height of the ROI.
 * @param type data type of the output matrix mask.
 * @return the mask.
 */
cv::Mat generate_rectagle_mask(int img_width, int img_height,
                       int x, int y, int rect_widht, int rect_height,
                               int type=CV_8UC1);

/**
 * @brief Performs a "hard" combination between two images using a mask.
 * @param foreground the foreground image (inside the mask).
 * @param background the background image (outside the mask).
 * @param mask the mask with 0 (background) / 255 (foreground).
 * @return The combined image.
 */
cv::Mat combine_images(const cv::Mat& foreground, const cv::Mat& background,
                       const cv::Mat& mask);