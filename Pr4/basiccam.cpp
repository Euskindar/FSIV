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

////////////////////////////////////////////////////////////////////////

#define FSIV_IMCOLS 640
#define FSIV_IMROWS 480

#define FSIV_CX FSIV_IMCOLS/2
#define FSIV_CY FSIV_IMROWS/2

// Create an image to display the projected cube
cv::Mat img(FSIV_IMROWS, FSIV_IMCOLS, CV_8UC3, cv::Scalar(0,0,0));
cv::Mat cube2d;

// TODO: Create the global variables to store the trackbar values
const int angle_slider_max = 360;
const int focal_slider_max = 200;
const int cx_slider_max = 640;
const int cy_slider_max = 480;

int angle_slider;
int focal_slider = 100;
int cx_slider;
int cy_slider;
// ...

////////////////////////////////////////////////////////////////////////

const String keys =
"{help h usage ? |      | print this message   }"
"{@out o O       | output.jpg | output name }"
;

////////////////////////////////////////////////////////////////////////

/**
  * @brief Compute the 2D points given the current parameters
*/
void fsiv_computeCube2d(cv::Mat & cube2d, float lfocal, float rangle)
{
	// Create a 3D cube
	cv::Mat cube = fsiv_cube3d();

	// OPTIONAL:
	// TODO: create the rotation matrix and apply it to the cube
	// Use the following expression: cube_rot <-- (cube * Rot) - 0.5; // The -0.5 helps to vizualize the cube

	// ...

	// Create a camera matrix
	cv::Mat cam = fsiv_cameraMatrix(lfocal, FSIV_CX, FSIV_CY);

	// Project the cube
	cube2d = fsiv_projectPoints(cube, cam);
}

////////////////////////////////////////////////////////////////////////

void fsiv_recomputeCube2d(void)
{
	fsiv_computeCube2d(cube2d, 100, 0);

	// TODO: Clean the window --> set img matrix to all black
	img.setTo(cv::Scalar(0, 0, 0));
	// ...

	// Update the image
	fsiv_drawFullCubeOnImage(img, cube2d);
}

////////////////////////////////////////////////////////////////////////
// -------------- Event handlers for the trackbars ----------------
////////////////////////////////////////////////////////////////////////

void on_trackbar_angle(int, void*)
{
	// TODO: get the new focal length
	// ...
	int focal = 100;

	// Update the image
	fsiv_recomputeCube2d();

	cv::imshow("Cube", img);
}

////////////////////////////////////////////////////////////////////////

void on_trackbar_focal(int, void*)
{
	// TODO: get the new focal length
	// ...
	int focal = 100;

	// Update the image
	fsiv_recomputeCube2d();

	cv::imshow("Cube", img);
}

////////////////////////////////////////////////////////////////////////

void on_trackbar_cx(int, void*)
{
	// TODO: get the new focal length
	// ...
	int focal = 100;

	// Update the image
	fsiv_recomputeCube2d();

	cv::imshow("Cube", img);
}

////////////////////////////////////////////////////////////////////////

void on_trackbar_cy(int, void*)
{
	// TODO: get the new focal length
	// ...
	int focal = 100;

	// Update the image
	fsiv_recomputeCube2d();

	cv::imshow("Cube", img);
}

////////////////////////////////////////////////////////////////////////

// ===================================================================
// =============================== THE MAIN ==========================
// ===================================================================

int main(int argc,char **argv)
{
	CommandLineParser parser(argc, argv, keys);
	parser.about("Camera projection simple");

	// Default output file name
	cv::String out_name = "output.jpg";

	if (parser.has("help"))
	{
		parser.printMessage();
		return 0;
	}

	// Save the output name
	if (parser.has("@out"))
	{
		out_name = parser.get<cv::String>("@out");
	}

	try {

		// Create a window to display the projected cube
		cv::namedWindow("Cube");

		// TODO: create trackbars
		// cv::createTrackbar("Angle", "Cube", &angle_slider, angle_slider_max, on_trackbar_angle);
		cv::createTrackbar("Focal", "Cube", &focal_slider, focal_slider_max, on_trackbar_focal);
		cv::createTrackbar("Cx", "Cube", &cx_slider, cx_slider_max, on_trackbar_cx);
		cv::createTrackbar("Cy", "Cube", &cy_slider, cy_slider_max, on_trackbar_cy);
		// ...

		// Display the projected cube
		cv::imshow("Cube", img);
		// cv::waitKey(0);

		// TODO Control keyboard to save current image into file
        char key = 0;
        while(key != 27)  // Waits until ESC pressed
        {
            if(key == 's' || key == 'S')
            {
                // Saves to file
                cv::imwrite(out_name, img);
                cout << "Image saved!" << endl;
            }

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