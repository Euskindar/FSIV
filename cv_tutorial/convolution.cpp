#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <opencv2/imgproc.hpp>


/**
 * @brief The convolution algorithm to run a kernel over a image
 * @param src input image.
 * @param dst output image.
 * @param kernel kernel matrix.
 * @param padding the padding of the src image to operate with the kernel at the edges of the image.
 */
void fsiv_convolution(const cv::Mat& src, cv::Mat& dst, const cv::Mat& kernel, int padding)
{
    // Check if dst image is prepared or not...
    CV_Assert(!src.empty());
    CV_Assert(!dst.empty());
    CV_Assert(src.rows == dst.rows && src.cols == dst.cols);
    CV_Assert(src.depth() == dst.depth());
    CV_Assert(!kernel.empty());

    // Check the padding type == int and odd number
    CV_Assert(typeid(padding).name() != "i");
    CV_Assert(padding % 2 == 0);
    CV_Assert(kernel.depth() == ((padding*padding)+1));

    double sum; // Variable to store the new value for the pixel

    // Apply the convolution opperation:
    // 1- Dilate the src image with the padding
    cv::copyMakeBorder(src, src, padding, padding, padding, padding, CV_HAL_BORDER_REPLICATE);
    cv::namedWindow("Padding");
    cv::imshow("Padding", src);

    // 2- Run over the src image without considering the padding
    for (int src_row = padding; src_row < (src.rows-padding); src_row++)
    {
        for (int src_col = padding; src_col < (src.cols-padding); src_col++)
        {
            const uchar *ptr = src.ptr<uchar>(src_row) + 3 * src_col; // access to the pixel of src
            uchar *ptrO = dst.ptr<uchar>(src_row) + 3 * src_col;

            // 3- Run over the kernel to operate per pixel
            for (int ker_row = -padding; ker_row <= padding; ker_row++)
            {
                for (int ker_col = -padding; ker_col <= padding; ker_col++)
                {
                    const uchar *ptr = kernel.ptr<uchar>(ker_row) + 3 * ker_col; // access to the pixel of kernel

                    // Consider the different channels of the images
                    if (src.channels() == 1)    // Grayscale, 1 channel
                    {
                        
                        


                    }
                    else    // Color, BGR, 3 channels
                    {
                        
                        
                    }
                    


                }
            }
        }
    }
}



