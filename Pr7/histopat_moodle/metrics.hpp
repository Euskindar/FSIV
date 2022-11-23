// ----------------------------------------
// metrics.hpp
// (c) FSIV, University of Cordoba
// ----------------------------------------

#ifndef FSIV_METRICS_HPP
#define FSIV_METRICS_HPP

#include <vector>
#include <opencv2/core.hpp>

/**
 * @brief Compute the confusion matrix of a supervised classification problem.
 * The confusion matrix will has a row per "True" class label and a
 * column per "Predicted" class label.
 * @param[in] true_labels is a row vector with the ground truth label per sample.
 * @param[in] predicted_labels is a row vector with the predicted label per sample.
 * @return The matrix.
 * @pre true_labels.rows == predicted_labels.rows
 * @pre true_labels.type()==CV_32FC1
 * @pre predicted_labels.type()==CV_32FC1
 * @post std::abs(cv::sum(cmat)[0]-static_cast<double>(true_labels.rows)) <= 1.0e-6
 */
cv::Mat compute_confusion_matrix(const cv::Mat& true_labels,
                         const cv::Mat& predicted_labels);

/**
 * @brief Compute the recognition rate (RR) for a class label.
 * @param[in] cmat is the confusion matrix.
 * @param[in] category is the category to be rated.
 * @return the RR (recoginition rate).
 * @pre !cmat.empty() && cmat.type()==CV_32FC1
 * @pre cmat.rows == cmat.cols
 * @pre 0<=category && category<cmat.rows
 * @post RR>=0.0f && RR<=1.0
 */
float compute_recognition_rate(const cv::Mat& cmat, int category);

/**
 * @brief Compute the Mean Recognition Rate (MRR) for a set of class labels.
 * @param[in] cmat is the confusion matrix.
 * @param[in] categories is a optional vector with the labels used to computed the MRR.
 * @warning if catergories is empty, means to compute MRR for all the labels.
 * @return the MRR.
 * @pre !cmat.empty() && cmat.depth()==CV_32F
 * @pre cmat.rows == cmat.cols && cmat.rows>1
 * @pre categories.size()==0 || for l in categories.size(), 0<=l<cmat.rows
 * @post MRR>=0.0f && MRR<=1.0f
 */
float compute_mean_recognition_rate(const cv::Mat& cmat,
                                    std::vector<int> const& categories=std::vector<int>());

/**
 * @brief Compute the accuracy (ACC) metric.
 * @param[in] cmat is the confusion matrix.
 * @return the ACC.
 * @pre !cmat.empty() && cmat.depth()==CV_32F
 * @pre cmat.rows == cmat.cols && cmat.rows>1
 * @post ACC>=0.0f && ACC<=1.0f
 */                                    
float compute_accuracy(const cv::Mat& cmat,
                       std::vector<int> const& categories=std::vector<int>());

/**
 * @brief Compute chi2 distance between two histograms.
 * Note: Code from scratch. Do not use cv::compareHist().
 * @param[in] h1 the first descriptor.
 * @param[in] h2 the second descriptor.
 * @return the chi2 distance.
 * @pre h1.rows==1 and h2.rows==1
 * @pre h1.cols == h2.cols
 * @posrt !isnan(ret_v) && (ret_v >= 0.0)
 */
float fsiv_chisquared_dist(const cv::Mat & h1, const cv::Mat & h2);

#endif // FSIV_METRICS_HPP
