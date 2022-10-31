// FSIV

#pragma once

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/**
 * @brief Creates a list of 3D points representing the position 
 * in the real world of the corners (Z=0).
 */
void fsiv_boardPoints3d(float size, const cv::Size & patternsize, std::vector<cv::Point3f> & points3d);

/**
 * @brief Calibrates the camera given the corners and their 3D correspondences
 * @param ... 
 */
void fsiv_calibrateCamera(const std::vector<vector<cv::Point3f> > & points3d, const vector<vector<Point2f> > & cornerPoints, const cv::Size & imageSize, cv::Mat & cameraMatrix, cv::Mat & distCoeffs);


// TO DO: define all the extra functions that you might need