// FSIV

#include "common_code.hpp"

void fsiv_boardPoints3d(float size, const cv::Size & patternsize, std::vector<cv::Point3f>& points3d)
{
	CV_Assert(size > 0);
	// TODO


}

void fsiv_calibrateCamera(const std::vector<vector<cv::Point3f> > & points3d, const vector<vector<Point2f> > & cornerPoints, const cv::Size & imageSize, cv::Mat & cameraMatrix, cv::Mat & distCoeffs)
{
	CV_Assert(points3d.size() > 0);
	CV_Assert(cornerPoints.size() > 0);
}

// TO DO: define all the extra functions that you might need
