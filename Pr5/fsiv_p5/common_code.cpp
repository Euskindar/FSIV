// FSIV

#include "common_code.hpp"

void fsiv_boardPoints3d(const float size, const cv::Size patternsize, std::vector<cv::Point3f>& points3d)
{
	CV_Assert(size > 0);

	// TODO

	points3d.clear();

	for (int row = 0; row < patternsize.height; row++)
	{
		for (int col = 0; col < patternsize.width; col++)
		{
			points3d.push_back(cv::Point3f(row*size, col*size, 0)); // Store the 3D coordinates
		}
	}
}

void fsiv_calibrateCamera(const std::vector< std::vector<cv::Point3f> > points3d, const std::vector< std::vector<cv::Point2f> > cornerPoints, const cv::Size imageSize, cv::Mat& cameraMatrix, cv::Mat& distCoeffs)
{
	CV_Assert(points3d.size() > 0);
	CV_Assert(cornerPoints.size() > 0);

	




}


// TO DO: define all the extra functions that you might need