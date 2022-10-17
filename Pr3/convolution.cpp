// Handmade convolution algotithm for FSIV

#include "convolution.hpp"


///////////////////////////////////////////////////////////////////////////////////////////

void fsiv_convolution(const cv::Mat& src, cv::Mat& dst, const cv::Mat& kernel, int padding)
{
    // Check if dst image is prepared or not...
    CV_Assert(!src.empty());
    CV_Assert(!dst.empty());
    CV_Assert(src.rows == dst.rows && src.cols == dst.cols);
    CV_Assert(src.depth() == dst.depth());
    CV_Assert(!kernel.empty());

    // Check the padding type == int
    CV_Assert(typeid(padding).name() != "i");

    double sum_B = 0.0; // Variable to store the new value for the pixel
    double sum_G = 0.0; // Variable to store the new value for the pixel
    double sum_R = 0.0; // Variable to store the new value for the pixel

    // Apply the convolution opperation:
    // 1- Dilate the src image with the padding
    cv::copyMakeBorder(src, dst, padding, padding, padding, padding, 0);
    cv::namedWindow("Padding");
    cv::imshow("Padding", dst);

    // 2- Run over the src image without considering the padding
    for (int src_row = padding; src_row < (src.rows-padding); src_row++)
    {
        for (int src_col = padding; src_col < (src.cols-padding); src_col++)
        {
            uchar *ptr_dst = dst.ptr<uchar>(src_row) + 3 * src_col;

            // 3- Run over the kernel to operate per pixel
            for (int ker_row = -padding; ker_row <= padding; ker_row++)
            {
                for (int ker_col = -padding; ker_col <= padding; ker_col++)
                {
                    const uchar *ptr_ker = kernel.ptr<uchar>(ker_row) + 1 * ker_col; // access to the pixel of kernel
                    const uchar *ptr_src = src.ptr<uchar>((src_row + ker_row)) + 3 * (src_col + ker_col); // access to the pixel of src

                    sum_B += ptr_src[0] * ptr_ker[0];
                    sum_G += ptr_src[1] * ptr_ker[0];
                    sum_R += ptr_src[2] * ptr_ker[0];
                }
            }

            // Assign the new value to the pixel
            ptr_dst[0] = sum_B;   //B
            ptr_dst[1] = sum_G;   //G
            ptr_dst[2] = sum_R;   //R

            sum_B = 0.0;  // Restart value
            sum_G = 0.0;  // Restart value
            sum_R = 0.0;  // Restart value
        }
    }

    cv::namedWindow("FILTER");
    cv::imshow("FILTER", dst);
}

///////////////////////////////////////////////////////////////////////////////////////////

void show_matrix(const cv::Mat mat)
{
    CV_Assert(mat.channels() == 1);

    std::cout << "Kernel = " << std::endl;
    std::cout << " "  << mat << std::endl << std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////////