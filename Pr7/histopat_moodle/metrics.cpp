// ----------------------------------------
// metrics.cpp
// (c) FSIV, University of Cordoba
// ----------------------------------------

#include <cmath>
#include "metrics.hpp"
#include "common_code.hpp"

float
fsiv_chisquared_dist(const cv::Mat & h1, const cv::Mat & h2)
{
    assert(!h1.empty() && h1.type()==CV_32FC1);
    assert(!h2.empty() && h2.type()==CV_32FC1);
    assert(h1.rows==1);
    assert(h2.rows==1);
    assert(h1.cols==h2.cols);
    float ret_v = 0.0;

    //TODO: implement The Chi^2 distance between h1 y h2.
    // chi2 = 0.5 * SUM_i [(h1[i]-h2[i])^2 / (h1[i]+h2[i])]
    //Hint: try not to use loops, only OpenCV mat arithmetics and functions.
    //Remember to avoid dividing by zero.


    //
    assert(!std::isnan(ret_v) && (ret_v >= 0.0f));
    return ret_v;
}

cv::Mat
compute_confusion_matrix(const cv::Mat& true_labels,
                         const cv::Mat& predicted_labels)
{
    assert(true_labels.rows == predicted_labels.rows);
    assert(true_labels.type()==CV_32FC1);
    assert(predicted_labels.type()==CV_32FC1);
    cv::Mat cmat;

    //Compute the confussion matrix.

    double max_true_label=0.0;

    //TODO: First find the max class label used in true_labels
    
    //    
    const int n_categories = static_cast<int>(max_true_label)+1;
    assert(n_categories>1);

    //TODO: create a square matrix with zeros for n_categories.
    
    //
    assert(!cmat.empty() && cmat.type()==CV_32FC1
           && cmat.rows==n_categories && cmat.rows==cmat.cols);
    assert(std::abs(cv::sum(cmat)[0])<=1.e-6);

    //TODO: Compute the confussion matrix given the ground truth (true_labels)
    // and the predictions (predicted_labels).
    //Remember: Rows are the Ground Truth. Cols are the predictions.
    

    //
    assert(std::abs(cv::sum(cmat)[0]-static_cast<double>(true_labels.rows)) <=
            1.0e-6);
    return cmat;
}

float
compute_recognition_rate(const cv::Mat& cmat, int category)
{
    assert(!cmat.empty() && cmat.type()==CV_32FC1);
    assert(cmat.rows == cmat.cols);
    assert(category<cmat.rows);

    float RR = 0.0;
    //TODO: compute the recognition rate (RR) for the category.
    //Hint: try to avoid any loop. Use Opencv mat methods and functions.
    //Remember to avoid dividing by zero.
  cv::Mat row_sum;

  
    //
    assert(!std::isnan(RR) && RR>=0.0f && RR<=1.0f);
    return RR;
}

float
compute_mean_recognition_rate(const cv::Mat& cmat,
                              std::vector<int> const& categories)
{
    assert(!cmat.empty() && cmat.depth()==CV_32F);
    assert(cmat.rows == cmat.cols && cmat.rows>1);

    float MRR = 0.0;


    assert(!std::isnan(MRR) && MRR>=0.0f && MRR<=1.0f);
    return MRR;
}

float
compute_accuracy(const cv::Mat& cmat,
                 std::vector<int> const& categories)
{
    assert(!cmat.empty() && cmat.depth()==CV_32F);
    assert(cmat.rows == cmat.cols && cmat.rows>1);

    float acc = 0.0;

    //TODO: compute the accurracy only for the categories given.
    //Remember to avoid dividing by zero.

    //
    assert(!std::isnan(acc) && acc >0.0f && acc <= 1.0f);
    return acc;
}


