/***********************************
 * Autor: Manuel J Marin-Jimenez
 * Universidad de Córdoba (Spain)
 * Grado en Ing Informatica
 * Asignatura: FSIV
 * 
 * Info:
 * Shows how to modify pixels
 * 
 * ******************************************/

#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

const String keys =
"{help h usage ? |      | print this message   }"
"{@image         |      | image to process   }"
"{out            | output.jpg | output name }"
; 

// You have to allocate memory for hist before calling this function
void fsiv_compute_histogram(const cv::Mat& I, const int nbins, int* hist)
{
	;
}

int main(int argc,char **argv)
{
	CommandLineParser parser(argc, argv, keys);
	parser.about("FSIV program");

	if (parser.has("help"))
	{
		parser.printMessage();
		return 0;
	}

	//String imname = parser.get<String>(0);

	//String outname = parser.get<String>("out");

	try{
			
		//cv::Mat image = cv::imread(imname, cv::IMREAD_GRAYSCALE);
		uchar Idata[] = {0,0, 1,1, 100,100, 130,130, 150,150, 200,200, 225, 226, 255, 255};
		cv::Mat image = cv::Mat(4, 4, CV_8UC1, Idata);

		if (image.rows == 0)
		{
			std::cerr << "ERROR: cannot load image" << std::endl;
			exit(-1);
		}
		
		std::cout << image << std::endl;

		// Call the function to compute the histogram
		int* hist;

		if (0)
		{
			cv::namedWindow("Image");
			cv::imshow("Image", image);
			cv::waitKey(0);
		}
		  
		// Assert that you have computed the histogram correctly

	}catch(std::exception &ex)
	{
	  cout<<ex.what()<<endl;
	}

	return 0;
}
 
