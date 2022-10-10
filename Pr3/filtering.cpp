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
const int gamma_slider_max = 100;
int gamma_slider;

const int kernel_slider_max = 100;
int kernel_slider;

double gamma_value;
int kernel_size;

int filter_type;

// Images
cv::Mat Original;
cv::Mat Filtered;
cv::Mat Unsharp;


////////////////////////////////////////////////////////////////////

const string keys =
	"{help h usage ?     |     | All parameters descriptions}"
	"{@image             |     | Image to operate with}"
    "{@Output Out o O    |     | Output image file name}"
    "{@Gamma gamma g G   | 0.0 | Indicates the Gamma value}"
    "{@Kernel kernel k K |  1  | Indicates the Kernel size (ODD values only)}"
    "{@Filter filter f F |  0  | Indicates the type of filter used -> 0 - BLUR FILTER, 1 - BOX FILTER, 2 - GAUSSIAN FILTER}"
;

////////////////////////////////////////////////////////////////////

// Trackbar
static void on_trackbar_gamma(int, void*)
{
    double g = (double) gamma_slider / gamma_slider_max;
    gamma_value = g;

    std::cout << "Gamma: " << gamma_value << std::endl;

    // Apply
    apply_filter(Original, Filtered, Unsharp, gamma_value);

    // Update images
    cv::imshow("Unsharp", Unsharp);
}

////////////////////////////////////////////////////////////////////

// Trackbar
static void on_trackbar_kernel(int, void*)
{
    int k = kernel_slider;

    if(k%2 == 1)
    {
        kernel_size = k;
    }

    std::cout <<"Kernel: " << kernel_size << std::endl;
    // cv::blur(Original, Filtered, cv::Size(kernel_size, kernel_size));
    use_filter(Original, Filtered, kernel_size, filter_type);

    // Apply
    apply_filter(Original, Filtered, Unsharp, gamma_value);

    // Update images
    cv::imshow("Filtered", Filtered);
    cv::imshow("Unsharp", Unsharp);
}

////////////////////////////////////////////////////////////////////


int main (int argc, char* const* argv)
{
    int retCode = EXIT_SUCCESS;

    try
    {
        // Default output file name
        cv::String out_name = "Unsharp.jpg";

        cv::CommandLineParser parser(argc, argv, keys);

        parser.about("Assignment 2");

        if (parser.has("help"))
        {
            parser.printMessage();
            return 0;
        }

        // Get the gamma value from command line
        if (parser.has("@Gamma"))
        {
            gamma_value = parser.get<double>("@Gamma");
            cout << "Gamma: " << gamma_value << endl;
        }

        // Get the kernel size from command line
        if(parser.has("@Kernel"))
        {
            kernel_size = parser.get<int>("@Kernel");
            CV_Assert(kernel_size%2 == 1);  // Only works with odd values
            cout << "Kernel: " << kernel_size << endl;
        }

        // Save the output name
        if (parser.has("@Output"))
        {
            out_name = parser.get<cv::String>("@Output");
        }

        // Get the gamma value from command line
        if (parser.has("@Filter"))
        {
            filter_type = parser.get<int>("@Filter");
            cout << "Using filter type: " << filter_type << endl;
        }


        if (!parser.check())
        {
            parser.printErrors();
            return 0;
        }

        // Read the image as default
        cv::String image = parser.get<cv::String>(0);
        Original = cv::imread(image);

        // Convert uchar image to float for operations
        // Original.convertTo(Original, CV_32F, 1/255.0);

        // Copy the original image to the output
        Original.copyTo(Unsharp);

        // Create Window for the original image
        cv::namedWindow("Original"); 
        cv::imshow("Original", Original);
        
        // Create Window for the blured image
        cv::namedWindow("Filtered", cv::WINDOW_AUTOSIZE); 
        // Apply the filter
        cv::blur(Original, Filtered, cv::Size(kernel_size, kernel_size));
        cv::imshow("Filtered", Filtered);

        // Create Window for the output image
        cv::namedWindow("Unsharp", cv::WINDOW_AUTOSIZE); 
        cv::createTrackbar("Gamma", "Unsharp", &gamma_slider, gamma_slider_max, on_trackbar_gamma);
        cv::createTrackbar("Kernel", "Unsharp", &kernel_slider, kernel_slider_max, on_trackbar_kernel);
        cv::imshow("Unsharp", Unsharp);

        char key = 0;
        while(key != 27)  // Waits until ESC pressed
        {
            if(key == 's' || key == 'S')
            {
                // Saves to file
                cv::imwrite(out_name, Unsharp);
                cout << "Image saved!" << endl;
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
