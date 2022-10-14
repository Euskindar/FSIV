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

// Global variables
const int mult_slider_max = 100;
int mult_slider;
double mult;

const int add_slider_max = 255;
int add_slider;
int add;

bool sub_flag = false;

int R_slider;
int G_slider;
int B_slider;

int mult_R_slider;
int mult_G_slider;
int mult_B_slider;
double mult_R;
double mult_G;
double mult_B;

// Images
cv::Mat img;
cv::Mat out;


////////////////////////////////////////////////////////////////////

const string keys =
	"{help h usage ?  |     | All parameters descriptions}"
	"{@image          |     | Image to operate with}"
    "{@Output Out o O |     | Output image file name}"
    "{Grayscale g G   |     | Load image in grayscale}"
    "{Invert i I      |     | Load image in inverted}"
;

////////////////////////////////////////////////////////////////////

// Trackbar to multiply
static void on_trackbar_mult(int, void*)
{
    mult = (double) mult_slider / mult_slider_max;

    std::cout << mult << std::endl;
    // TO DO

    fsiv_mult_safe(img, out, mult);

    cv::imshow("Processed", out);
}

////////////////////////////////////////////////////////////////////

// Trackbar to add
static void on_trackbar_add(int, void*)
{
    add = add_slider;

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

////////////////////////////////////////////////////////////////////

// Trackbar to multiply RGB
static void on_trackbar_mult_RGB(int, void*)
{
    mult_R = (double)mult_R_slider / mult_slider_max;
    mult_G = (double)mult_G_slider / mult_slider_max;
    mult_B = (double)mult_B_slider / mult_slider_max;

    std::cout << "R mult: " << (double)mult_R << std::endl;
    std::cout << "G mult: " << (double)mult_G << std::endl;
    std::cout << "B mult: " << (double)mult_B << std::endl;
    // TO DO

    fsiv_mult_safe_RGB(img, out, mult_R, mult_G, mult_B);

    cv::imshow("Processed", out);
}

////////////////////////////////////////////////////////////////////

// Trackbar to add RGB
static void on_trackbar_add_RGB(int, void*)
{
    std::cout << "R add: " << R_slider << std::endl;
    std::cout << "G add: " << G_slider << std::endl;
    std::cout << "B add: " << B_slider << std::endl;
    // TO DO

    if(sub_flag == false)
    {
        fsiv_add_safe_RGB(img, out, R_slider, G_slider, B_slider);
    }
    else
    {
        fsiv_sub_safe_RGB(img, out, R_slider, G_slider, B_slider);
    }

    cv::imshow("Processed", out);
}

////////////////////////////////////////////////////////////////////

int main (int argc, char* const* argv)
{
    int retCode = EXIT_SUCCESS;

    try
    {
        // Flag to control grayscale
        bool gray_flag = false;
        
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
            gray_flag = true;
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
        img.copyTo(out);

        cv::namedWindow("Original"); // Create Window
        cv::imshow("Original", img);
        
        cv::namedWindow("Processed", cv::WINDOW_AUTOSIZE); // Create Window

        cv::createTrackbar("Mult", "Processed", &mult_slider, mult_slider_max, on_trackbar_mult);
        cv::createTrackbar("Add", "Processed", &add_slider, add_slider_max, on_trackbar_add);

        if (gray_flag == false)
        {
            cv::createTrackbar("R Mult", "Processed", &mult_R_slider, mult_slider_max, on_trackbar_mult_RGB);
            cv::createTrackbar("G Mult", "Processed", &mult_G_slider, mult_slider_max, on_trackbar_mult_RGB);
            cv::createTrackbar("B Mult", "Processed", &mult_B_slider, mult_slider_max, on_trackbar_mult_RGB);

            cv::createTrackbar("R Add", "Processed", &R_slider, add_slider_max, on_trackbar_add_RGB);
            cv::createTrackbar("G Add", "Processed", &G_slider, add_slider_max, on_trackbar_add_RGB);
            cv::createTrackbar("B Add", "Processed", &B_slider, add_slider_max, on_trackbar_add_RGB);
        }

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

            if((key == 'm' || key == 'M') && sub_flag == false)
            {
                sub_flag = true;
                cout<<"Subtract mode ON"<<endl;
            }
            else if((key == 'm' || key == 'M') && sub_flag == true)
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
