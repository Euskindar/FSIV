/***********************************
 * Autor: Manuel J Marin-Jimenez
 * Universidad de Córdoba (Spain)
 * Grado en Ing Informatica
 * Asignatura: FSIV
 * Info:
 * Shows how to project 3D points
* ******************************************/

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>

#include "common_code.hpp"

using namespace std;
using namespace cv;

const String keys =
"{help h usage ? |      | print this message   }"
"{out            | output.jpg | output name }"
;

#define FSIV_CX 320
#define FSIV_CY 240

#define FSIV_IMROWS 480
#define FSIV_IMCOLS 640

// Create an image to display the projected cube
cv::Mat img(FSIV_IMROWS, FSIV_IMCOLS, CV_8UC3,cv::Scalar(0,0,0));
cv::Mat cube2d;

// TODO: Create the global variables to store the trackbar values
// ...

/**
  * @brief Compute the 2D points given the current parameters
*/
void fsiv_computeCube2d(cv::Mat & cube2d, float lfocal, float rangle)
{
	// Create a 3D cube
	cv::Mat cube = fsiv_cube3d();

	// TODO: create the rotation matrix and apply it to the cube
	// Use the following expression: cube_rot <-- (cube * Rot) - 0.5; // The -0.5 helps to vizualize the cube
	// ...

	// Create a camera matrix
	cv::Mat cam = fsiv_cameraMatrix(lfocal, FSIV_CX, FSIV_CY);

	// Project the cube
	cube2d = fsiv_projectPoints(cube, cam);
}

void fsiv_recomputeCube2d(void)
{
	fsiv_computeCube2d(cube2d, 100, 0);

	// TODO: Clean the window --> set img matrix to all black
	// ...

	// Update the image
	fsiv_drawFullCubeOnImage(img, cube2d);
}

// -------------- Event handlers for the trackbars ----------------

void on_trackbar_focal(int, void*)
{
	// TODO: get the new focal length
	// ...
	int focal = 100;

	// Update the image
	fsiv_recomputeCube2d();

	cv::imshow("Cube", img);
}

// ===================================================================
// =============================== THE MAIN ==========================
// ===================================================================

int main(int argc,char **argv)
{
	CommandLineParser parser(argc, argv, keys);
	parser.about("Camera projection simple");

	if (parser.has("help"))
	{
		parser.printMessage();
		return 0;
	}

	try {

		// Create a window to display the projected cube
		cv::namedWindow("Cube");

		// TODO: create trackbars
		// ...

		// Display the projected cube
		cv::imshow("Cube", img);
		cv::waitKey(0);

		// TODO Control keyboard to save current image into file
		// ...

	}catch(std::exception &ex)
	{
	  cout<<ex.what()<<endl;
	}

	return 0;
}