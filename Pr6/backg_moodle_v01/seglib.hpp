// ----------------------------------------
// seglib.hpp
// (c) FSIV, University of Cordoba
// ----------------------------------------

#include <iostream>

using namespace std;


#ifndef _SEGLIB_H_
#define _SEGLIB_H_ 1

#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


/**
 * @brief Removes segmentation noise using morphological operations.
 * @param img target image where removing the noise.
 * @param r is the radius of the structuring element.
 * @pre img.type()==CV_8UC1
 * @pre r>0
 */
void fsiv_remove_segmentation_noise(cv::Mat & img, int r);

/**
 * @brief Applies a segmentation method based on image difference
 * @param[in] prevFrame Previous image frame (RGB)
 * @param[in] curFrame  Current image frame (RGB)
 * @param[out] difimg  Single-channel generated mask
 * @param[in] thr Theshold used to decide if a pixel contains enough motion to be considered foreground.
 * @param[in] r  Radius of the structuring element for opening+closing.
 */
void fsiv_segm_by_dif(const cv::Mat & prevFrame, const cv::Mat & curFrame, cv::Mat & difimg, int thr=11, int r=0);


/**
 * @brief Applies a mask to an RGB image
 * @param[in] frame RGB input image.
 * @param[in] mask  Single-channel mask.
 * @param[out] outframe Output RGB frame.
 */
void fsiv_apply_mask(const cv::Mat & frame, const cv::Mat & mask, cv::Mat & outframe);

/*********************** OPTIONAL PART ***********************/

/**
 * @brief Learns a background model given an input stream. You might want to use fsiv_acc_model.
 * @param[in] input     RGB input image.
 * @param[in] maxframes Number of frames used to estimated the model
 * @param[out] MeanI This is normalized by the number of frames used to compute it (i.e. maxframes) --> E[I]
 * @param[out] I2    This is normalized by the number of frames used to compute it (i.e. maxframes) --> E[I^2]
 * @param[out] VarI  Suggestion, use the following equation: E[I^2] - (E[I])^2
 * @param[out] StdI  Standard deviation per pixel and RGB component.
 */
void fsiv_learn_model(cv::VideoCapture & input, int maxframes, cv::Mat & MeanI, cv::Mat & I2, cv::Mat & VarI, cv::Mat & StdI);

/**
 * @brief Accumulates data from the input frame into MeanI and I2
 * @param[in] frame RGB input image.
 * @param[out] MeanI Sum of all input frames (unnormalized)
 * @param[out] I2    Sum of squares of all input frames (unnormalized)
 */
void fsiv_acc_model(const cv::Mat & frame, cv::Mat & MeanI, cv::Mat & I2);

/**
 * @brief Applies a segmentation method based on a Gaussian model of the background
 * @param[in] frame RGB input image.
 * @param[out] theMask  Single-channel mask.
 * @param[in] mean Mean model of each RGB pixel
 * @param[in] std Standard deviation model of each RGB pixel
 * @param[in] t Theshold to weight the standard deviation of each pixel in the model.
 * @param[in] r Radius of the structuring element for opening+closing.
 */
void fsiv_segm_by_model(const cv::Mat & frame, cv::Mat & theMask, const cv::Mat & mean, const cv::Mat & std, float t, int r);

/**
 * @brief Updates the Gaussian model of the background
 * @param[in] frame RGB input image.
 * @param[out] mean Mean model of each RGB pixel
 * @param[out] I2 Squared image model
 * @param[out] std Standard deviation model of each RGB pixel
 * @param[in] alpha Weight for updating the model components. 
 * @param[in] theMask  Single-channel mask.
 */

void fsiv_update_model(const cv::Mat & frame, cv::Mat & mean, cv::Mat & I2, cv::Mat &std,  float alpha, const cv::Mat & theMask);

#endif
