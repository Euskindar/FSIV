// FSIV

#include "common_code.hpp"

//////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////

// Creates a 3D projection matrix 3x4
// The projection is a perspective projection
cv::Mat fsiv_cameraMatrix(float f, float cx, float cy)
{
	cv::Mat cam(3, 4, CV_32F);
	// TODO

	// Row 1
	cam.at<float>(0, 0) = f;
	cam.at<float>(0, 1) = 0;
	cam.at<float>(0, 2) = cx;
	cam.at<float>(0, 3) = 0;

	// Row 2
	cam.at<float>(1, 0) = 0;
	cam.at<float>(1, 1) = f;
	cam.at<float>(1, 2) = cy;
	cam.at<float>(1, 3) = 0;

	// Row 3
	cam.at<float>(2, 0) = 0;
	cam.at<float>(2, 1) = 0;
	cam.at<float>(2, 2) = 1;
	cam.at<float>(2, 3) = 0;

	return cam;
}

//////////////////////////////////////////////////////////////////////

// Create a rotation matrix
// The rotation is a rotation around the Z axis
cv::Mat rotationMatrixZ(float angle)
{
	cv::Mat rot(3, 3, CV_32F);
	// TODO

	// Row 1
	rot.at<float>(0, 0) = cos(angle);
	rot.at<float>(0, 1) = -sin(angle);
	rot.at<float>(0, 2) = 0;

	// Row 2
	rot.at<float>(1, 0) = sin(angle);
	rot.at<float>(1, 1) = cos(angle);
	rot.at<float>(1, 2) = 0;

	// Row 3
	rot.at<float>(2, 0) = 0;
	rot.at<float>(2, 1) = 0;
	rot.at<float>(2, 2) = 1;

	// std::cout << "Rotation mat:" << std::endl << rot << std::endl;
	return rot;
}

//////////////////////////////////////////////////////////////////////

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
	std::cout << "Projection mat:" << std::endl << projection << std::endl;
	std::cout << std::endl << "-----------------------------" << std::endl << std::endl;
	std::cout << "3D points:" << std::endl << points3d << std::endl;
	std::cout << std::endl << "-----------------------------" << std::endl << std::endl;
	std::cout << "Homo coord:" << std::endl << fsiv_mat2homog(points3d) << std::endl;
	std::cout << std::endl << "-----------------------------" << std::endl << std::endl;

	// Transpose the Homo coord matrix
	cv::Mat transpose_3d = fsiv_mat2homog(points3d);
	cv::transpose(transpose_3d, transpose_3d);
	std::cout << "Transposed Homo coord:" << std::endl << transpose_3d << std::endl;
	std::cout << std::endl << "-----------------------------" << std::endl << std::endl;

	// Create an auxiliar matrix to operate
	cv::Mat aux;
	aux = projection * transpose_3d;	// Store the operation
	std::cout << "AUX points:" << std::endl << aux << std::endl;

	// Remove the last row of the matrix to keep the 2D coordinates: [xw, yw, w] / w = [x, y, 1]
	aux(cv::Range(0, aux.rows-1), cv::Range(0, aux.cols)).copyTo(points2d);
	cv::transpose(points2d, points2d);
	std::cout << "2D points:" << std::endl << points2d << std::endl;

	return points2d;
}

//////////////////////////////////////////////////////////////////////

cv::Mat fsiv_mat2homog(cv::Mat& coord3d)
{
	// Create matrix of ones
	cv::Mat ch(coord3d.rows, coord3d.cols+1, CV_32F);
	ch = ch.ones(ch.rows, ch.cols, CV_32F);

	int last_column = ch.cols-1;	// Store the value of last column

	// Run the matrix
	for (size_t src_rows = 0; src_rows < ch.rows; src_rows++)
	{
		for (size_t src_cols = 0; src_cols < ch.cols; src_cols++)
		{
			// Store the original values
			if (last_column != src_cols)
			{
				ch.at<float>(src_rows, src_cols) = coord3d.at<float>(src_rows, src_cols);
				// std::cout << "Added value" << std::endl;
			}
		}
	}

	// Print matrix
	// std::cout << "Homogeneus coordinates matrix:" << std::endl << ch << std::endl << std::endl;

	return ch;
}

//////////////////////////////////////////////////////////////////////

//=================================== DRAWING FUNCTIONS =============================
// Draw a face of a 3d cube
void drawFace(cv::Mat& img, const cv::Mat& cube2d, int* idx_face, cv::Scalar color)
{
	CV_Assert(cube2d.cols == 2);

	for (int i = 0; i < 4; i++)
	{
		cv::Point2f p1 = cv::Point2f(cube2d.at<float>(idx_face[i], 0), cube2d.at<float>(idx_face[i], 1));
		cv::Point2f p2 = cv::Point2f(cube2d.at<float>(idx_face[(i + 1) % 4], 0), cube2d.at<float>(idx_face[(i + 1) % 4], 1));
		cv::line(img, p1, p2, color, 2);
	}
}

//////////////////////////////////////////////////////////////////////

// This function requires 'drawFace'
void fsiv_drawFullCubeOnImage(cv::Mat& img, const cv::Mat& cube2d)
{
	// Back face
	int idx_face1[4] = { 0, 1, 2, 3 };
	drawFace(img, cube2d, idx_face1, cv::Scalar(0, 255, 0));	// G

	// Side face
	int idx_face3[4] = { 1, 2, 6, 5 };
	drawFace(img, cube2d, idx_face3, cv::Scalar(255, 0, 0));	// B

	// Side face
	int idx_face4[4] = { 0, 3, 7, 4 };
	drawFace(img, cube2d, idx_face4, cv::Scalar(255, 255, 255));	// Color

	// Front face
	int idx_face2[4] = { 4, 5, 6, 7 };
	drawFace(img, cube2d, idx_face2, cv::Scalar(0, 0, 255));	// R
}

//////////////////////////////////////////////////////////////////////

// TO DO: define all the extra functions that you might need