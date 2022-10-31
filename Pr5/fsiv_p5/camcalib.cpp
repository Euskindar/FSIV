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
#include <string>

#include "common_code.hpp"

using namespace std;
using namespace cv;

const String keys =
"{help h usage ? |      | print this message   }"
"{list           | images.txt | path to txt with filenames }"
"{out            | intrinsics.yml | output name }"
;


// ===================================================================
// =============================== THE MAIN ==========================
// ===================================================================

int main(int argc,char **argv)
{
	CommandLineParser parser(argc, argv, keys);
	parser.about("Camera calibration");

	if (parser.has("help"))
	{
		parser.printMessage();
		return 0;
	}

	float sqsize = 100;
	String outname = parser.get<String>("out");

	String listtxt = parser.get<String>("list");

	std::vector<String> lfiles;

	cv::Size imageSize;

	try
	{
		// Create a window to display the images
		cv::namedWindow("ImagePattern");
		vector<vector<Point2f> > imagePoints;
		cv::Size patternsize = cv::Size(5, 4);

		for (int fix = 0; fix < lfiles.size(); fix++)
		{

			// TODO: find corners in current image


			// TODO: add corners to the vector of image corners

		}

		// TODO
		// CALIBRATION GOES HERE

		// TODO: prepare 3D points

		// TODO: run camera calibration

	}
	catch(std::exception &ex)
	{
	  cout<<ex.what()<<endl;
	}

	return 0;
}