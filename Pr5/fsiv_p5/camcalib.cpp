/***********************************
 * Autor: Manuel J Marin-Jimenez
 * Universidad de Córdoba (Spain)
 * Grado en Ing Informatica
 * Asignatura: FSIV
 *
 * Info:
 * Shows how to calibrate a camera
 *
 * ******************************************/

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

#include "common_code.hpp"

using namespace std;
using namespace cv;

cv::Size patternsize = cv::Size(5, 8);
cv::Size winSize = cv::Size(11, 17); // patternsize*2+1

const String keys =
"{help h usage ? |                    | print this message}"
"{list           | ../data/images.txt | path to txt with filenames}"
"{out            | ../intrinsics.yml  | output name}"
"{size           |        31          | size of the squares of the chessboard in milimeters}"
"{video          |                    | path of the video with the chessboard}"
"{live           |      false         | set to record a live camera}"
;


// ===================================================================
// =============================== THE MAIN ==========================
// ===================================================================

int main(int argc,char **argv)
{
	char key = 0;

	CommandLineParser parser(argc, argv, keys);
	parser.about("Camera calibration");

	if (parser.has("help"))
	{
		parser.printMessage();
		return 0;
	}

	// Save the output name
	bool live_cam = parser.get<bool>("live");

	// Save the size of the square in mm
	float sqsize = parser.get<float>("size");

	// Save the output name
	cv::String outname = parser.get<cv::String>("out");

	// Save the images paths file
	cv::String listtxt = parser.get<cv::String>("list");

	// Save the image path
	std::vector<String> lfiles;

	// Save the video path
	cv::String pathToVideo = parser.get<cv::String>("video");

	cv::Size imageSize;
	cv::Mat image;

	std::vector<cv::Point2f> corners;	// Image corners

	// Creating vector to store vectors of 3D points for each checkerboard image
	std::vector<std::vector<cv::Point3f>> object_points;
	std::vector<cv::Point3f> obj_point;

	// Creating vector to store vectors of 2D points for each checkerboard image
	std::vector<std::vector<cv::Point2f>> image_points;

	try
	{
		bool listPathEmpty = listtxt.empty();	// Option to calibrate with image list

		if (listPathEmpty)
		{
			std::cout << "Image list path empty . . ." << std::endl;
			return -1;
		}

		if (!listPathEmpty)	// Uses images to calibrate
		{
			// Read the image path file and insert to the vector
			std::ifstream in(listtxt);

			// Check if object is valid
			if(!in)
			{
				std::cerr << "Cannot open the File : " << listtxt << std::endl;
				return false;
			}

			std::string str;
			// Read the next line from in untill it reaches the end.
			while (std::getline(in, str))
			{
				// Line contains string of length > 0 then save it in vector
				if(str.size() > 0)
				{
					lfiles.push_back(str);
				}

				std::cout << "Image " << lfiles.size() << " inserted." << std::endl;
			}
			std::cout << std::endl;

			//Close The File
			in.close();

			// Create a window to display the images
			cv::namedWindow("ImagePattern", WINDOW_NORMAL);

			for (int fix = 0; fix < lfiles.size(); fix++)
			{
				// TODO: find corners in current image
				// Read the current image from lfiles
				image = cv::imread(lfiles[fix]);
				cv::resize(image, image, cv::Size(image.cols/6, image.rows/6));
				std::cout << "Image " << fix+1 << " read : " << lfiles[fix] << std::endl;

				// Find corners
				bool foundCorners = false;
				foundCorners = cv::findChessboardCorners(image, patternsize, corners, (cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK));

				if(foundCorners)
				{
					std::cout << "Corners found!" << std::endl << std::endl;

					cv::TermCriteria termcrit(cv::TermCriteria::COUNT|cv::TermCriteria::EPS,20,0.03);
					cv::Mat aux;
					cv::cvtColor(image, aux, cv::COLOR_BGR2GRAY);		// Color change to get 1 channel to use cornerSubPix()
					cv::cornerSubPix(aux, corners, winSize, cv::Size(-1,-1), termcrit);
				}

				// TODO: add corners to the vector of image corners
				fsiv_boardPoints3d(sqsize, patternsize, obj_point);
				object_points.push_back(obj_point);
				image_points.push_back(corners);

				cv::drawChessboardCorners(image, patternsize, cv::Mat(corners), foundCorners);
				cv::imshow("ImagePattern", image);

				while (key != 32 /* SPACEBAR */)
				{
					key = cv::waitKey(0);	// Go 1 by 1
				}

				key = 0;	// Wait
			}
			std::cout << std::endl;
		}

		//////////////////////////////////////////////////////////////////////////////

		// VIDEO CAPTURING OPTION

		bool videoPathEmpty = pathToVideo.empty();	// Option to calibrate with video

		if (!videoPathEmpty)	// Uses video to calibrate
		{
			std::cout << "Reading video file for camera calibration . . ." << std::endl << std::endl;

			cv::destroyAllWindows(); // Destroy all windows
			cv::namedWindow("VIDEO");

			cv::VideoCapture video(pathToVideo);	// Open the video file

			if (!video.isOpened())	// Check if is correctly opened
			{
				std::cout << "Video read failed . . ." << std::endl;
				return -1;
			}

			cv::Mat frame;	// Frame of the video

			while (video.grab()) // For each frame of the video
			{
				video.retrieve(frame); // Converts the frame into an image
				cv::resize(frame, frame, cv::Size(frame.cols / 2, frame.rows / 2));

				cv::imshow("VIDEO", frame);

				key = cv::waitKey(0);

				if (key == 110)
				{
					std::cout << "Next frame . . ." << std::endl;
				}

				if (key == 32 /* SPACEBAR */)	// Use the frame to calibrate
				{
					std::cout << "Adding frame to camera calibration . . ." << std::endl;

					// Find corners
					bool foundCorners = false;
					foundCorners = cv::findChessboardCorners(frame, patternsize, corners , (cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK));

					if (foundCorners)
					{
						std::cout << "Corners found!" << std::endl << std::endl;

						cv::TermCriteria termcrit(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, 20, 0.03);
						cv::Mat aux;
						cv::cvtColor(frame, aux, cv::COLOR_BGR2GRAY); // Color change to get 1 channel to use cornerSubPix()
						cv::cornerSubPix(aux, corners, winSize, cv::Size(-1, -1), termcrit);
					}

					// TODO: add corners to the vector of image corners
					fsiv_boardPoints3d(sqsize, patternsize, obj_point);
					object_points.push_back(obj_point);
					image_points.push_back(corners);

					cv::drawChessboardCorners(frame, patternsize, cv::Mat(corners), foundCorners);
					cv::imshow("VIDEO", frame);
				}

				while (key != 110) // Press 'n' to continue
				{
					key = cv::waitKey(0);
				}

				key = 0; // wait
			}

			// Close video
			video.release();
		}

		//////////////////////////////////////////////////////////////////////////////

		// WEBCAM VIDEO OPTION

		// if (live_cam)	// -live option on CLI
		// {
		// 	std::cout << "Using webcam for camera calibration . . ." << std::endl << std::endl;

		// 	cv::destroyAllWindows(); // Destroy all windows
		// 	cv::namedWindow("WEBCAM");

		// 	cv::VideoCapture webcam(0);

		// 	if (!webcam.isOpened())	// Check if is correctly opened
		// 	{
		// 		std::cout << "Cannot open webcam . . ." << std::endl;
		// 		return -1;
		// 	}

		// 	cv::Mat frame;	// Frame of the video

		// 	while (webcam.grab()) // For each frame of the video
		// 	{
		// 		webcam.retrieve(frame); // Converts the frame into an image
		// 		cv::resize(frame, frame, cv::Size(frame.cols / 2, frame.rows / 2));

		// 		cv::imshow("WEBCAM", frame);

		// 		key = cv::waitKey(0);

		// 		if (key == 32 /* SPACEBAR */)	// Use the frame to calibrate
		// 		{
		// 			std::cout << "Adding frame to camera calibration . . ." << std::endl;

		// 			// Find corners
		// 			bool foundCorners = false;
		// 			foundCorners = cv::findChessboardCorners(frame, patternsize, corners , (cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK));

		// 			if (foundCorners)
		// 			{
		// 				std::cout << "Corners found!" << std::endl << std::endl;

		// 				cv::TermCriteria termcrit(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, 20, 0.03);
		// 				cv::Mat aux;
		// 				cv::cvtColor(frame, aux, cv::COLOR_BGR2GRAY); // Color change to get 1 channel to use cornerSubPix()
		// 				cv::cornerSubPix(aux, corners, winSize, cv::Size(-1, -1), termcrit);
		// 			}

		// 			// TODO: add corners to the vector of image corners
		// 			fsiv_boardPoints3d(sqsize, patternsize, obj_point);
		// 			object_points.push_back(obj_point);
		// 			image_points.push_back(corners);

		// 			cv::drawChessboardCorners(frame, patternsize, cv::Mat(corners), foundCorners);
		// 			cv::imshow("WEBCAM", frame);

		// 		}

		// 		while (key != 99) // Press 'c' to continue
		// 		{
		// 			key = cv::waitKey(0);
		// 		}

		// 		key = 0;	// wait
		// 	}

		// 	// Close video
		// 	webcam.release();
		// }

		//////////////////////////////////////////////////////////////////////////////

		std::cout << std::endl << "==================================================" << std::endl << std::endl;
		std::cout << "Objt pts:" << std::endl << object_points.size() << std::endl;
		std::cout << std::endl << "==================================================" << std::endl << std::endl;
		std::cout << "Imag pts:" << std::endl << image_points.size()<< std::endl;

		//////////////////////////////////////////////////////////////////////////////

		// TODO
		// CALIBRATION GOES HERE
		std::cout << "Calibrating camera . . ." << std::endl;

		// TODO: prepare 3D points
		// POINTS PREPARED ON THE PREVIOUS LOOP

		// Calibration parameters
		cv::Mat camMat, distCoeffs;
		cv::Mat rotVec, trasVec;
		double err = 0.0;

		// TODO: run camera calibration
		err = fsiv_calibrateCamera(object_points, image_points, image.size(), camMat, distCoeffs, rotVec, trasVec);

		std::cout << std::endl << "==================================================" << std::endl << std::endl;
		std::cout << "Camera Matrix: " << std::endl << camMat << std::endl;
		std::cout << std::endl << "==================================================" << std::endl << std::endl;
		std::cout << "Dist. Coeff.: " << std::endl << distCoeffs << std::endl;
		std::cout << std::endl << "==================================================" << std::endl << std::endl;
		std::cout << "Rotation Vector: " << rotVec << std::endl;
		std::cout << std::endl << "==================================================" << std::endl << std::endl;
		std::cout << "Translation Vector: " << trasVec << std::endl;
		std::cout << std::endl << "==================================================" << std::endl << std::endl;
		std::cout << "Calibration Error: " << err << std::endl;
		std::cout << std::endl << "==================================================" << std::endl << std::endl;

		/////////////////////////////////////////////////////////////////////////////////////

		// Store the data into a YAML file
		cv::FileStorage fileStore(outname, cv::FileStorage::WRITE);		// Open in write mode

		fileStore << "Camera Matrix" << camMat;
		fileStore << "Dist Coeff" << distCoeffs;
		fileStore << "Rotation Vector" << rotVec;
		fileStore << "Translation Vector" << trasVec;
		fileStore << "Calibration Error" << err;

		fileStore.release();	// Close

		/////////////////////////////////////////////////////////////////////////////////////

        while(key != 27)  // Waits until ESC pressed
        {
            key = cv::waitKey(0);
        }
		// ...
	}
	catch(std::exception& ex)
	{
	  cout<<ex.what()<<endl;
	}

	std::cout << "End of the process!" << std::endl;
	cv::destroyAllWindows(); // Destroy all windows

	return 0;
}