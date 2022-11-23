// FSIV

#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>
#include <fstream>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <stdio.h>

#include <opencv2/calib3d.hpp>


/**
 * @brief Creates a list of 3D points representing the position
 * in the real world of the corners (Z=0).
 */
void fsiv_boardPoints3d(const float size, const cv::Size patternsize, std::vector<cv::Point3f>& points3d);

/**
 * @brief Calibrates the camera given the corners and their 3D correspondences
 * @param ...
 */
double fsiv_calibrateCamera(const std::vector< std::vector<cv::Point3f> > points3d, const std::vector< std::vector<cv::Point2f> > cornerPoints, const cv::Size imageSize, cv::Mat& cameraMatrix, cv::Mat& distCoeffs, cv::Mat& rotVec, cv::Mat& trasVec);


// TO DO: define all the extra functions that you might need