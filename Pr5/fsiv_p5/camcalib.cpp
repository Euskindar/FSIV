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
//#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>
#include <fstream>
#include <string>

#include "common_code.hpp"

using namespace std;
using namespace cv;

const String keys =
"{help h usage ? |                    | print this message   }"
"{list           | ../data/images.txt | path to txt with filenames }"
"{out            | ../intrinsics.yml  | output name }"
"{size           |                    | size of the squares of the chessboard in milimeters}"
"{video          |                    | path of the video with the chessboard }"
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

	float sqsize = 100;
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

	try
	{
		// Create a window to display the images
		cv::namedWindow("ImagePattern");

		std::vector< std::vector<Point2f> > corners;	// Image corners

		cv::Size patternsize = cv::Size(6, 5);

		for (int fix = 0; fix < lfiles.size(); fix++)
		{
			// TODO: find corners in current image

			// Read the current image from lfiles
			cv::Mat image = cv::imread(lfiles[fix]);
			std::cout << "Image " << fix+1 << " read : " << lfiles[fix] << std::endl;

			cv::namedWindow("Image Read");

			// Find corners
			bool foundCorners = false;
			foundCorners = findChessboardCorners(image, patternsize, corners, (cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK));

			// TODO: add corners to the vector of image corners



			if(foundCorners)
			{
				cv::Size winSize = cv::Size(13, 11);		// patternsize*2+1
				cv::TermCriteria termcrit(cv::TermCriteria::COUNT|cv::TermCriteria::EPS,20,0.03);
				cv::cornerSubPix(image, corners, winSize, cv::Size(-1,-1), termcrit);
			}

			cv::drawChessboardCorners(image, patternsize, corners, foundCorners);
			cv::imshow("Image Read", image);

			key = cv::waitKey(0);	// Go 1 by 1
		}
		std::cout << std::endl;

		// TODO
		// CALIBRATION GOES HERE

		// TODO: prepare 3D points

		// TODO: run camera calibration

        while(key != 27)  // Waits until ESC pressed
        {
            // if(key == 's' || key == 'S')
            // {
            //     // Saves to file
            //     cv::imwrite(outname, img);
            //     cout << "Image saved!" << endl;
            // }

            key = cv::waitKey(0);
        }
		// ...

	}
	catch(std::exception &ex)
	{
	  cout<<ex.what()<<endl;
	}

	std::cout << "End of the process!" << std::endl;

	return 0;
}