// FSIV

#include "common_code.hpp"


void apply_filter(const cv::Mat O, const cv::Mat F, cv::Mat& U, const double g)
{
    // Do operation
    U = ((1.0+g)*O) - (g*F);

    // Return to the original type
    // U.convertTo(U, CV_8U);
}


void use_filter(const cv::Mat O, cv::Mat F, const int k, const int option)
{
    switch (option)
    {
        // Box Filter
        case 1:
        {
            std::cout << "Using filter type: " << option << " - Box Filter" << std::endl;
            cv::boxFilter(O, F, -1, cv::Size(k, k));
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