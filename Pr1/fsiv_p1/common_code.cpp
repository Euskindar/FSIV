// FSIV

#include "common_code.hpp"

cv::Mat
convert_gray_to_rgb(const cv::Mat& img)
{
    CV_Assert(!img.empty());
    CV_Assert(img.channels()==1);
    cv::Mat out;

    //TODO
    cv::cvtColor(img, out, cv::COLOR_GRAY2RGB);
    //

    CV_Assert(out.channels()==3);
    CV_Assert(img.rows==out.rows && img.cols==out.cols);
    CV_Assert(img.depth()==out.depth());
    return out;
}

cv::Mat
convert_rgb_to_gray(const cv::Mat& img)
{
    CV_Assert(!img.empty());
    CV_Assert(img.channels()==3);
    cv::Mat out;

    //TODO
    cv::cvtColor(img, out, cv::COLOR_RGB2GRAY);
    //

    CV_Assert(out.channels()==1);
    CV_Assert(img.rows==out.rows && img.cols==out.cols);
    CV_Assert(img.depth()==out.depth());
    return out;
}

cv::Mat
generate_rectagle_mask(int img_width, int img_height,
                       int x, int y, int rect_width, int rect_height, int type)
{
    CV_Assert(img_width>0 && img_height>0);
    CV_Assert(x>=0 && x<img_width);
    CV_Assert(y>=0 && y<img_height);
    CV_Assert(rect_width>0 && rect_height>0);
    cv::Mat mask;

    //TODO

    if(mask.rows == 0 || mask.cols == 0)
    {
        // Realocate the mask size to correspond to the image
        mask.create(img_height, img_width, type);

        // Set all pixel as black
        mask.setTo(cv::Scalar(0, 0, 0));
    }

    // Create a white rectangle
    cv::Point cornerTop = cv::Point(x, y);
    cv::Point cornerBottom = cv::Point(rect_width, rect_height);
    rectangle(mask, cornerTop, cornerBottom, cv::Scalar(255, 255, 255), cv::FILLED);
    
    //

    CV_Assert(mask.rows==img_height && mask.cols==img_width);
    CV_Assert(mask.type()==type);
    return mask;
}


cv::Mat
combine_images(const cv::Mat& foreground, const cv::Mat& background,
               const cv::Mat& mask)
{
    CV_Assert(background.rows == foreground.rows &&
              background.cols==foreground.cols);
    CV_Assert(background.type()==foreground.type());
    CV_Assert(mask.rows == foreground.rows &&
              mask.cols==foreground.cols);
    CV_Assert(mask.type()==foreground.type());
    cv::Mat output;

    //TODO
    // Copy the background to modify
    background.copyTo(output);

    for (int i = 0; i < mask.rows; i++) {
        for (int j = 0; j < mask.cols; j++) {
            const uchar *ptr = mask.ptr<uchar>(i) + 3 * j; // access to the pixel

            if(ptr[0] == 255 && ptr[1] == 255 && ptr[2] == 255)
            {
                // std::cout<<"HOLA"<<std::endl;
                uchar *ptrO = output.ptr<uchar>(i) + 3 * j; // access to the pixel
                const uchar *ptrF = foreground.ptr<uchar>(i) + 3 * j; // access to the pixel

                ptrO[0] = (uchar)ptrF[0];
                ptrO[1] = (uchar)ptrF[1];
                ptrO[2] = (uchar)ptrF[2];
            }
        }
    }


    //

    CV_Assert(output.rows == foreground.rows && output.cols==foreground.cols);
    CV_Assert(output.type()==foreground.type());
    return output;
}