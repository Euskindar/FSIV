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

#include "common_code.hpp"

using namespace std;
using namespace cv;

cv::Size patternsize = cv::Size(5, 4);
cv::Size winSize = cv::Size(11, 9); // patternsize*2+1

const String keys =
"{help h usage ? |                    | print this message }"
"{list           | ../data/images.txt | path to txt with filenames }"
"{out            | ../intrinsics.yml  | output name }"
"{size           |        50          | size of the squares of the chessboard in milimeters }"
"{video          |                    | path of the video with the chessboard }"
"{live           |      false         | set to record a live camera }"
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

	cv::String listtxt = parser.get<cv::String>("list");

	std::vector<String> lfiles;

	// Read the image rotue file and insert to the vector
	std::ifstream in(listtxt);

	// Check if object is valid
    if(!in)
    {
        std::cerr << "Cannot open the File : " << listtxt << std::endl;
        return false;
    }

	std::string str;
	// Read the next line from File untill it reaches the end.
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

	cv::Size imageSize;
	cv::Mat image;

	try
	{
		// Create a window to display the images
		cv::namedWindow("ImagePattern");

		std::vector<cv::Point2f> corners;	// Image corners
		std::vector< std::vector<cv::Point2f> > total_corners;	// Image corners

		for (int fix = 0; fix < lfiles.size(); fix++)
		{
			// TODO: find corners in current image

			// Read the current image from lfiles
			image = cv::imread(lfiles[fix]);
			std::cout << "Image " << fix+1 << " read : " << lfiles[fix] << std::endl;

			// Find corners
			bool foundCorners = false;
			foundCorners = cv::findChessboardCorners(image, patternsize, corners/* , (cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK) */);

			if(foundCorners)
			{
				std::cout << "Corners found!" << std::endl << std::endl;

				cv::TermCriteria termcrit(cv::TermCriteria::COUNT|cv::TermCriteria::EPS,20,0.03);
				cv::Mat aux;
				cv::cvtColor(image, aux, cv::COLOR_BGR2GRAY);		// Color change to get 1 channel to use cornerSubPix()
				cv::cornerSubPix(aux, corners, winSize, cv::Size(-1,-1), termcrit);
			}

			// TODO: add corners to the vector of image corners
			total_corners.push_back(corners);

			cv::drawChessboardCorners(image, patternsize, cv::Mat(corners), foundCorners);
			cv::imshow("ImagePattern", image);

			key = cv::waitKey(0);	// Go 1 by 1
		}
		std::cout << std::endl;

		//////////////////////////////////////////////////////////////////////////////

		// TODO
		// CALIBRATION GOES HERE
		std::cout << "Calibrating camera . . ." << std::endl;

		// TODO: prepare 3D points
		std::vector<cv::Point3f> points3d;

		fsiv_boardPoints3d(sqsize, patternsize, points3d);
		// std::cout << "SQ size: " << std::endl << sqsize << std::endl << std::endl;
		// std::cout << "Patt. size: " << std::endl << patternsize << std::endl << std::endl;
		std::cout << "Points 3D: " << std::endl << points3d << std::endl << std::endl;

		// Calibration parameters
		cv::Mat calib, dist_coeffs;		// Camera matrix and distorsion coefficents
		// std::vector<cv::Mat> rotVec, trasVec;	// Rotation and traslation vectors
		double err = 0.0;	// Calibration error

		std::vector< std::vector<cv::Point3f> > object_points;

		////////////////////////////////////////////////////////////// NOSENSE ???????
		// for (size_t i = 0; i < lfiles.size(); i++)
		// {
		// 	object_points.push_back(points3d);
		// 	std::cout << "Object 3D points: " << std::endl << "Size: " << object_points.size() << std::endl << object_points[i] << std::endl << std::endl;
		// }
		//////////////////////////////////////////////////////////////

		// TODO: run camera calibration
		fsiv_calibrateCamera(object_points, total_corners, image.size(), calib, dist_coeffs/* , rotVec, trasVec */);

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

	return 0;
}