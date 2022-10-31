// FSIV

#pragma once

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/**
 * @brief Creates a cube of size 1
 * @return The cube in a cv::Mat
 */
cv::Mat fsiv_cube3d(void);

/**
 * @brief Creates a basic 3D projection matrix 3x4
 * @param f focal length.
 * @param cx X center .
 * @param cy Y center.
 * @return The camera matrix
 */
cv::Mat fsiv_cameraMatrix(float f, float cx, float cy);

/**
  * @ brief Creates a rotation matrix around the X axis given the angle in radians.
*/
cv::Mat rotationMatrixZ(float angle);


/**
// @brief Function to project 3d points to 2d points using a projection matrix
// @param points3d The 3d points are a Nx3 matrix
// @param projection The projection matrix is a 3x4 matrix
// @return The 2d points are a Nx2 matrix
// You may use 'mat2homog'
*/
cv::Mat fsiv_projectPoints(cv::Mat& points3d, cv::Mat& projection);


/**
* @brief Draws the face of a projected cube
* @param img Image where to draw
* @param cube2d Matrix with the 2D coordinates per row
* @param idx_face Vector with the four indices to be used. Be careful with the order of them.
* @param color Color of the lines
*/
void drawFace(cv::Mat& img, const cv::Mat& cube2d, int* idx_face, cv::Scalar& color);


/**
* @brief Draws a set of faces
*/
// This function requires 'drawFace'
void fsiv_drawFullCubeOnImage(cv::Mat& img, const cv::Mat& cube2d);

/**
* @brief Given a matrix Nx3, generates a new matrix Nx4, where the last column is filled with 1's
*/
cv::Mat fsiv_mat2homog(cv::Mat& coord3d);

// TO DO: define all the extra functions that you might need