// FSIV

#include "common_code.hpp"

#include "convolution.hpp"


///////////////////////////////////////////////////////////////////////////////////////////

void apply_filter(const cv::Mat O, const cv::Mat F, cv::Mat& U, const double g)
{
    // Do operation
    U = ((1.0+g)*O) - (g*F);
}

///////////////////////////////////////////////////////////////////////////////////////////

void use_filter(const cv::Mat O, cv::Mat F, const int k, const int option)
{
    switch (option)
    {
        // Box Filter
        case 1:
        {
            std::cout << "Using filter type: " << option << " - Box Filter" << std::endl;
            cv::boxFilter(O, F, -1, cv::Size(k, k));

            /* 
            // Generate BOX KERNEL => All values to (1/kernel_size*kernel_size)
            cv::Mat box_kernel (k, k, CV_32F, 1.0/(k*k));
            // show_matrix(box_kernel);

            // Use the convolution to apply the kernel
            int pad = (k-1)/2;
            std::cout << "PADDING: " << pad << std::endl;
            fsiv_convolution(O, F, box_kernel, pad); 
            */
        }
        break;
        
        // Gaussian Filter
        case 2:
        {
            std::cout << "Using filter type: " << option << " - Gaussian Filter" << std::endl;
            cv::GaussianBlur(O, F, cv::Size(k, k), 0);
        }
        break;

        // Blur Filter
        default:
            std::cout << "Using filter type: " << option << " - Blur Filter" << std::endl;
            cv::blur(O, F, cv::Size(k, k));
        break;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////