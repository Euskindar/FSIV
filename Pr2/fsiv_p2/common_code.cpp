// FSIV

#include "common_code.hpp"


cv::Mat convert_gray_to_rgb(const cv::Mat& img)
{
    CV_Assert(!img.empty());
    CV_Assert(img.channels()==1);
    cv::Mat out;

    cv::cvtColor(img, out, cv::COLOR_GRAY2RGB);

    CV_Assert(out.channels()==3);
    CV_Assert(img.rows==out.rows && img.cols==out.cols);
    CV_Assert(img.depth()==out.depth());
    return out;
}


void fsiv_mult_safe(const cv::Mat& src, cv::Mat& dst, int val)
{
    CV_Assert(!src.empty());
    CV_Assert(src.rows == dst.rows && src.cols == dst.cols);

    //TODO

    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            const uchar *ptr = src.ptr<uchar>(i) + 3 * j; // access to the pixel
            uchar *ptrO = dst.ptr<uchar>(i) + 3 * j;

            // Controls overflow
            ptrO[0] = std::min(255, ptr[0]*val);
            ptrO[1] = std::min(255, ptr[1]*val);;
            ptrO[2] = std::min(255, ptr[2]*val);;
        }
    }

    //
}


void fsiv_add_safe(const cv::Mat& src, cv::Mat& dst, int val)
{
    CV_Assert(!src.empty());
    CV_Assert(src.rows == dst.rows && src.cols == dst.cols);

    //TODO

    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            const uchar *ptr = src.ptr<uchar>(i) + 3 * j; // access to the pixel
            uchar *ptrO = dst.ptr<uchar>(i) + 3 * j;

            // Controls overflow
            ptrO[0] = std::min(255, ptr[0]+val);
            ptrO[1] = std::min(255, ptr[1]+val);
            ptrO[2] = std::min(255, ptr[2]+val);
        }
    }

    //
}


void fsiv_sub_safe(const cv::Mat& src, cv::Mat & dst, int val)
{
        CV_Assert(!src.empty());
    CV_Assert(src.rows == dst.rows && src.cols == dst.cols);

    //TODO

    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            const uchar *ptr = src.ptr<uchar>(i) + 3 * j; // access to the pixel
            uchar *ptrO = dst.ptr<uchar>(i) + 3 * j;

            // Controls overflow
            ptrO[0] = std::max(0, ptr[0]-val);
            ptrO[1] = std::max(0, ptr[1]-val);
            ptrO[2] = std::max(0, ptr[2]-val);
        }
    }

    //
}