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

const int mult_slider_max = 100;
int mult_slider;
double mult;

const int add_slider_max = 255;
int add_slider;
int add;

bool sub_flag = false;

const int RGB_slider_max = 255;
int R_slider;
int G_slider;
int B_slider;
int R;
int G;
int B;


cv::Mat img;
cv::Mat out;


const string keys =
	"{help h usage ?  |     | All parameters descriptions}"
	"{@image          |     | Image to operate with}"
    "{@Output Out o O |     | Output image file name}"
    "{Grayscale g G   |     | Load image in grayscale}"
    "{Invert i I      |     | Load image in inverted}"
;


// Trackbar to multiply
static void on_trackbar_mult(int, void*)
{
    mult = (double) mult_slider / mult_slider_max;
    
    // Do something to the proc image
    std::cout << mult << std::endl;
    // TO DO

    fsiv_mult_safe(img, out, mult_slider);
    
    cv::imshow("Processed", out);
}


// Trackbar to add
static void on_trackbar_add(int, void*)
{
    add = add_slider;
    
    // Do something to the proc image
    std::cout << add << std::endl;
    // TO DO

    if(sub_flag == false)
    {
        fsiv_add_safe(img, out, add_slider);       
    }
    else
    {
        fsiv_sub_safe(img, out, add_slider);       
    }
    
    cv::imshow("Processed", out);
}


int main (int argc, char* const* argv)
{
    int retCode = EXIT_SUCCESS;

    try
    {
        // Default output file name
        cv::String out_name = "out.jpg";

        cv::CommandLineParser parser(argc, argv, keys);

        parser.about("Assignment 2");

        if (parser.has("help"))
        {
            parser.printMessage();
            return 0;
        }

        // Read the image as Grayscale image
        if (parser.has("Grayscale"))
        {
            cv::String image = parser.get<cv::String>(0);
            img = cv::imread(image, cv::IMREAD_GRAYSCALE);
            img = convert_gray_to_rgb(img);
        }
        // Read the image as Inverted image
        else if(parser.has("Invert"))
        {
            cv::String image = parser.get<cv::String>(0);
            img = cv::imread(image);
            img = cv::Scalar(255, 255, 255) - img;
        }
        // Otherwise read as default
        else
        {
            cv::String image = parser.get<cv::String>(0);
            img = cv::imread(image);
        }

        // Save the output name
        if (parser.has("@Output"))
        {
            out_name = parser.get<cv::String>("@Output");
        }

        if (!parser.check())
        {
            parser.printErrors();
            return 0;
        }

        // Type your code here and within 'common_code.cpp'

        img.copyTo(out);

        cv::namedWindow("Original", cv::WINDOW_AUTOSIZE); // Create Window
        cv::namedWindow("Processed", cv::WINDOW_AUTOSIZE); // Create Window

        cv::createTrackbar("Mult", "Processed", &mult_slider, mult_slider_max, on_trackbar_mult);
        cv::createTrackbar("Add", "Processed", &add_slider, add_slider_max, on_trackbar_add);

        cv::createTrackbar("R", "Processed", &R_slider, RGB_slider_max, on_trackbar_add);
        cv::createTrackbar("G", "Processed", &G_slider, RGB_slider_max, on_trackbar_add);
        cv::createTrackbar("B", "Processed", &B_slider, RGB_slider_max, on_trackbar_add);

        cv::imshow("Original", img);
        cv::imshow("Processed", out);

        char key = 0;
        while(key != 27)  // Waits until ESC pressed
        {
            if(key == 's' || key == 'S')
            {
                // Saves to file
                cv::imwrite(out_name, out);
                cout << "Image saved!" << endl;
            }

            if(key == 'm' && sub_flag == false)
            {
                sub_flag = true;
                cout<<"Subtract mode ON"<<endl;
            }
            else
            {
                sub_flag = false;
                cout<<"Subtract mode OFF"<<endl;
            }

            key = cv::waitKey(0);
        }
    }
    catch(std::exception &ex)
    {
        cout<<ex.what()<<endl;
    }

    std::cout << "End of the process!" << std::endl;
    return retCode;
}
