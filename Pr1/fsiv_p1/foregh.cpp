/*!
  Template program for the Computer Vision course.

  Author: Manuel J Marin-Jimenez, University of Cordoba
*/

#include <iostream>
#include <exception>
#include <sstream>

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/calib3d/calib3d.hpp>

#include "common_code.hpp"

using namespace std;

cv::Mat img;
cv::Mat mask;
cv::Mat out;
cv::Mat gray;
cv::Mat rgb;


const string keys =
	"{help h usage ? |     | All parameters descriptions}"
	"{@image         |     | Image to operate with}"
  "{Invert I i     |     | Select inverted option}"
;


int main (int argc, char* const* argv)
{
  int retCode = EXIT_SUCCESS;

  // Type your code here and within 'common_code.cpp' 

  try
  {
		cv::CommandLineParser parser(argc, argv, keys);

		parser.about("Assignment 1");
		
		if (parser.has("help"))
		{
		    parser.printMessage();
		    return 0;
		}
		
		cv::String image = parser.get<cv::String>(0);
    img = cv::imread(image);

		if (!parser.check())
		{
		    parser.printErrors();
		    return 0;
		}
// -----------------------------------------------
    //creates a window
    cv::namedWindow("Original");
    //shows image
    cv::imshow("Original", img);

    // -----------------------------------------------
    //creates a window
    // cv::namedWindow("Grayscale 3Channels");
    
    // Create the auxiliar matrixes
    gray = convert_rgb_to_gray(img);
    rgb = convert_gray_to_rgb(gray);
    //shows image
    // cv::imshow("Grayscale 3Channels", gray);
    // -----------------------------------------------

    // Realocate the mask size to correspond to the image
    mask.create(img.rows, img.cols, img.type());

    // Create the rectangles selection
    vector<cv::Rect> r;
    cv::selectROIs("Original", img, r, false, false);

    for (int i = 0; i < r.size(); i++)
    {
      cv::rectangle(mask, r.at(i), cv::Scalar(255,255,255), cv::FILLED);
    }

    // Show mask
    cv::namedWindow("Mask");
    cv::imshow("Mask", mask);

    if (parser.has("Invert"))
    {
      // Invert the original image
      img.copyTo(rgb);
      rgb = cv::Scalar(255, 255, 255) - rgb;

      // Combine with mask
      out = combine_images(rgb, img, mask);
      cv::namedWindow("Combined");
      cv::imshow("Combined", out);
    }
    else
    {
      // Combine with mask
      out = combine_images(img, rgb, mask);
      cv::namedWindow("Combined");
      cv::imshow("Combined", out);
    }
    
    char c = 0;
    while(c != 27)  // Waits until ESC pressed
    {
      if (c == 's')
      {
        // Saves to file
        cv::imwrite("out.jpg", out);

        cout << "Image saved!" << endl;
      }

      c = cv::waitKey(0);
    }
  }
  catch(std::exception &ex)
  {
    cout<<ex.what()<<endl;
  }

  std::cout << "End of the process!" << std::endl;
  return retCode;
}
