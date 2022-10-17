// FSIV

#include "common_code.hpp"

// Define a cv::Mat containing a cube in 3D of 1x1x1
// The cube is centered in (0.5, 0.5, 0.5)
cv::Mat fsiv_cube3d(void)
{
	cv::Mat cube(8, 3, CV_32F);
	cube.at<float>(0, 0) = 0;
	cube.at<float>(0, 1) = 0;
	cube.at<float>(0, 2) = 0;
	cube.at<float>(1, 0) = 1;
	cube.at<float>(1, 1) = 0;
	cube.at<float>(1, 2) = 0;
	cube.at<float>(2, 0) = 1;
	cube.at<float>(2, 1) = 1;
	cube.at<float>(2, 2) = 0;
	cube.at<float>(3, 0) = 0;
	cube.at<float>(3, 1) = 1;
	cube.at<float>(3, 2) = 0;
	cube.at<float>(4, 0) = 0;
	cube.at<float>(4, 1) = 0;
	cube.at<float>(4, 2) = 1;
	cube.at<float>(5, 0) = 1;
	cube.at<float>(5, 1) = 0;
	cube.at<float>(5, 2) = 1;
	cube.at<float>(6, 0) = 1;
	cube.at<float>(6, 1) = 1;
	cube.at<float>(6, 2) = 1;
	cube.at<float>(7, 0) = 0;
	cube.at<float>(7, 1) = 1;
	cube.at<float>(7, 2) = 1;
	return cube;
}

// Creates a 3D projection matrix 3x4
// The projection is a perspective projection
cv::Mat fsiv_cameraMatrix(float f, float cx, float cy)
{
	cv::Mat cam(3, 4, CV_32F);
	// TODO

	return cam;
}

// Create a rotation matrix
// The rotation is a rotation around the Z axis
cv::Mat rotationMatrixZ(float angle)
{
	cv::Mat rot(3, 3, CV_32F);
	// TODO

	return rot;
}

// Function to project 3d points to 2d points using a projection matrix
// The projection matrix is a 3x4 matrix
// The 3d points are a Nx3 matrix
// The 2d points are a Nx2 matrix
// You may use 'mat2homog'
cv::Mat fsiv_projectPoints(cv::Mat& points3d, cv::Mat& projection)
{
	cv::Mat points2d(points3d.rows, 2, CV_32F);

	CV_Assert(points3d.cols == 3);
	CV_Assert(projection.cols == 4 && projection.rows == 3);

	// TODO

	return points2d;
}

cv::Mat fsiv_mat2homog(cv::Mat& m)
{
	cv::Mat ch;

	// TODO

	return ch;
}

//=================================== DRAWING FUNCTIONS =============================
// Draw a face of a 3d cube
void drawFace(cv::Mat& img, const cv::Mat& cube2d, int* idx_face, cv::Scalar& color)
{
	CV_Assert(cube2d.cols == 2);

	for (int i = 0; i < 4; i++)
	{
		cv::Point2f p1 = cv::Point2f(cube2d.at<float>(idx_face[i], 0), cube2d.at<float>(idx_face[i], 1));
		cv::Point2f p2 = cv::Point2f(cube2d.at<float>(idx_face[(i + 1) % 4], 0), cube2d.at<float>(idx_face[(i + 1) % 4], 1));
		cv::line(img, p1, p2, color, 2);
	}

}

// This function requires 'drawFace'
void fsiv_drawFullCubeOnImage(cv::Mat& img, const cv::Mat& cube2d)
{

	int idx_face1[4] = { 0,1,2,3 };
	drawFace(img, cube2d, idx_face1, cv::Scalar(0, 255, 0));

	int idx_face2[4] = { 4,5,6,7 };
	drawFace(img, cube2d, idx_face2, cv::Scalar(0, 0, 255));

	int idx_face3[4] = { 1, 2, 4, 7 };
	drawFace(img, cube2d, idx_face3, cv::Scalar(255, 0, 0));

	int idx_face4[4] = { 0, 3, 5, 6 };
	drawFace(img, cube2d, idx_face4, cv::Scalar(255, 255, 0));
}

// TO DO: define all the extra functions that you might need