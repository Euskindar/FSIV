// ----------------------------------------
// seglib.cpp
// (c) FSIV, University of Cordoba
// ----------------------------------------

#include "seglib.hpp"
#include <opencv2/imgproc.hpp>

void fsiv_remove_segmentation_noise(cv::Mat & img, int r)
{
    CV_Assert(img.type()==CV_8UC1);
    CV_Assert(r>0);
    //TODO
    //Apply closing+opening using a square structuring element with radius r.

    //
}

void fsiv_segm_by_dif(const cv::Mat & prevFrame, const cv::Mat & curFrame, cv::Mat & difimg, int thr, int r)
{
   CV_Assert(prevFrame.type()==CV_8UC3 && prevFrame.type()==curFrame.type());
   CV_Assert(prevFrame.size()==prevFrame.size());
   // WRITE ME

   CV_Assert(difimg.type()==CV_8UC1);
   CV_Assert(difimg.size()==curFrame.size());   
}

void fsiv_apply_mask(const cv::Mat & frame, const cv::Mat & mask, cv::Mat & outframe)
{
   CV_Assert(frame.type()==CV_8UC1 || frame.type()==CV_8UC3);
   CV_Assert(mask.type()==CV_8UC1);
   CV_Assert(frame.size()==mask.size());
   
   // WRITE ME

   CV_Assert(outframe.type()==frame.type());
   CV_Assert(outframe.size()==frame.size());   
}

// ================= OPTIONAL PART STARTS HERE =======================

void fsiv_learn_model(cv::VideoCapture & input, int maxframes, cv::Mat & MeanI, cv::Mat & I2, cv::Mat & VarI, cv::Mat & StdI)
{
   CV_Assert(input.isOpened());
   
   // WRITE ME

}

void fsiv_acc_model(const cv::Mat & frame, cv::Mat & MeanI, cv::Mat & I2)
{
   // WRITE ME
}

void fsiv_segm_by_model(const cv::Mat & frame, cv::Mat & theMask, const cv::Mat & mean, const cv::Mat & std, float t, int r)
{
   CV_Assert(frame.type()==CV_32FC3);
   // WRITE ME

   CV_Assert(theMask.type()==CV_8UC1);
}

void fsiv_update_model(const cv::Mat & frame, cv::Mat & mean, cv::Mat & I2, cv::Mat &std,  float alpha, const cv::Mat & theMask)
{
   CV_Assert(frame.type()==CV_32FC3);
   CV_Assert(theMask.type()==CV_8UC1);

   CV_Assert(mean.type()==CV_32FC3);
   CV_Assert(std.type()==CV_32FC3);

   // WRITE ME
}
