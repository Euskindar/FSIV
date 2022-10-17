#include "opencv2/opencv.hpp"
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>

using namespace cv;

////////////////////////////////////////////////////////////////////////////////

int main(int argc,char **argv)
{
  int rows = std::stoi(argv[1]); // Rows of the board
  int cols = std::stoi(argv[2]); // Cols of the board
  int size = std::stoi(argv[3]); // Total Size of the board
  std::string intrinsics_yml = argv[4];  // Store the intrinsic values file ".yml"
  std::string pathToVideo    = argv[5];  // Store the video file name

  cv::Mat image, greyImage;  // Frames of the video

  std::vector<cv::Point2f> corners; // Corners

  std::vector<cv::Point3f> objectPoints;  // For solvePnP(), camera coordinates
  cv::Mat camera_matrix, distCoeffs;  // Camera matrix and distorsion coefficients
  cv::Mat rvec, tvec;  // Rotation and Translation matrix
  cv::FileStorage fs; // Variable to store the file

  std::vector<cv::Point3f> objectPointsToProject; // Coordinates 3D to be projected on the board
  std::vector<cv::Point2f> imagePointsProjected;  // Coordinates 2D projected on the board

  cv::Scalar Blue(0,0,255);   // Blue color
  cv::Scalar Green(0,255,0);  // Green color
  cv::Scalar Red(255,0,0);    // Red color

// --------------------------------------------------------------------------------------------

  cv::VideoCapture video(pathToVideo);  // Open the video
  if(!video.isOpened())  // Check if we succeeded
      return -1;

  while (video.grab())  // For each frame of the video
  {
    video.retrieve(image);  // Returns the video frame to "image"

    cv::cvtColor(image, greyImage, COLOR_BGR2GRAY);

// --------------------------------------------------------------------------------------------
    // 1- Detect the board using cv::findChessboardCorners, and refine the corners with cv::cornerSubPix.
    bool found = cv::findChessboardCorners(greyImage, cv::Size(rows,cols), corners);
    if (found == true)
    {
      cornerSubPix(greyImage, corners, cv::Size(rows,cols), cv::Size(-1,-1), cv::TermCriteria());

// --------------------------------------------------------------------------------------------

      // 2- Estimate the camera pose with respect to the board using cv::solvePnP.
      objectPoints.clear();
      for (size_t row = 0; row < rows; row++)
      {
        for (size_t col = 0; col < cols; col++)
        {
          objectPoints.push_back(cv::Point3f(row*size, col*size, 0)); // Store the 3D coordinates
        }
      }

      // Read of "intrinsics.yml" data for camera matrix values and distorsion coefficients
      fs.open(intrinsics_yml, cv::FileStorage::READ); // Opens the file
      if (!fs.isOpened()) // Error controling
      {
        std::cout << "Failed to open " << intrinsics_yml << '\n';
        return 1;
      }
      // Assignation of the values
      fs["camera_matrix"] >> camera_matrix;
      fs["distortion_coefficients"] >> distCoeffs;

      cv::solvePnP(objectPoints, corners, camera_matrix, distCoeffs, rvec, tvec);

// --------------------------------------------------------------------------------------------

      // 3- Drawing on the image a simple 3D scene. The 3D axis placed in the center of the reference system in colors red (X axis), green (Y axis) and blue (Z axis). The size of the axis should be the same as the board squares. You can use the function cv::projectPoints and cv::line for that.
      objectPointsToProject.push_back(cv::Point3f((rows/2)*size, (cols/2)*size, 0));  // Center of the board to start

      objectPointsToProject.push_back(cv::Point3f((rows/2)*size, (cols/2)*size, size));  // Z axis line
      objectPointsToProject.push_back(cv::Point3f((rows/2)*size, ((cols/2)+1)*size, 0));  // Y axis line
      objectPointsToProject.push_back(cv::Point3f(((rows/2)+1)*size, (cols/2)*size, 0));  // X axis line

      // Calculates the selected 3D points to be projected to the 2D board
      cv::projectPoints(objectPointsToProject, rvec, tvec, camera_matrix, distCoeffs, imagePointsProjected);

      // Print the lines (BGR = ZYX)
      cv::line(image, imagePointsProjected[0], imagePointsProjected[1], Blue, 3);   // Z line
      cv::line(image, imagePointsProjected[0], imagePointsProjected[2], Green, 3);  // Y line
      cv::line(image, imagePointsProjected[0], imagePointsProjected[3], Red, 3);    // X line
// --------------------------------------------------------------------------------------------
    }

    cv::imshow("VIDEO", image);

    cv::waitKey(10);
  }
}

////////////////////////////////////////////////////////////////////////////////
