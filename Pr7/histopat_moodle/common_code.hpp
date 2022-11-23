// ----------------------------------------
// common_code.hpp
// (c) FSIV, University of Cordoba
// ----------------------------------------

#ifndef __COMMON_CODE_HPP__
#define __COMMON_CODE_HPP__

#include <string>
#include <vector>
#include <opencv2/core.hpp>

#ifdef NDEBUG
#define DEBUG(l, x) while(0){};
#else
#include <iostream>
#include <iomanip>
extern const std::string __Debug_Padding;
extern size_t __Debug_PPL; //Pad per level.
extern int __Debug_Level;

#define DEBUG(l, x) {if (l <= __Debug_Level) std::cerr << '[' << std::setw(3) << l << "] " << __Debug_Padding.substr(0, __Debug_PPL*size_t(std::max(0, (l-1)))) << x;}
#endif

bool fsiv_load_dbdata(const std::string & filename, std::vector<std::string> &limages, cv::Mat &labels);


/**
 * @brief Decode a string like "RxC" to set a grid shape.
 * @param[in] str is the string coding the grid shape.
 * @param[out] n_cells a vector with rows and cols.
 * @return True if success.
 */
bool string_to_ncells(const std::string& str, int n_cells[]);


/**
 * @brief Normalize an image so mean=0.0 and var=1.0
 * @param src is the input image.
 * @return the normalized versión of src.
 * @pre src.channels()==1
 * @post ret_val.type()==CV_32FC1;
 * @post ret_val's mean is equal to 0.0 +- 1.0e-6
 * @post ret_val's var is equal to 1.0 +- 1.0e-6
 */
cv::Mat fsiv_normalize_mean_var(cv::Mat const& src);

/**
 * @brief Normalize an image so min=0.0 and max=1.0
 * @param src is the input image.
 * @return the normalized versión of src.
 * @pre src.channels()==1
 * @post ret_val.type()==CV_32FC1;
 * @post ret_val's mininum val is equal to 0.0 +- 1.0-e6
 * @post ret_val's maximum val is equal to 1.0 +- 1.0-e6
 */
cv::Mat fsiv_normalize_minmax(cv::Mat const& src);

/**
 * @brief A simple descriptor: concatenation of gray pixels
 * 
 * @return true if success.
 */

 bool fsiv_desc_simple_gray(const cv::Mat & image, cv::Mat & desc);

/**
 * @brief Compute the selected image descriptors for a set of images.
 * @param[in] lfiles are the filenames of the images. 
 * @param[in] canonical_size is size to resize the input roi.
 * @param[out] l_descs the output descriptors, one row per image. 
 * @param[in] desctype code representing the selected type of descriptor (0: gray, 1:???)
 * @param[in] img_norm sais how normalize the input image (0: not normalize, 1:minmax, 2:mean_stdev).
 * @param[in] hist_norm if its true, the histograms are normalized. 
 * @return true if success.
 */
bool fsiv_compute_desc_from_list(const std::vector<std::string> & lfiles,  
                            const std::string & dbdir,
                           const cv::Size &canonical_size,
                           cv::Mat & l_descs,
                           const int desctype=0,
                           const int img_norm=0,
                           const bool hist_norm=true
                           );


/**
 * @brief Compute the size of a file.
 * @param fname is the pathname for the file.
 * @param units is a divisor for get file units. Eg. 1 for bytes, 1024 for Kb, ...
 * @return the file size using the units or -1 if it could not open the file.
 * @pre units > 0
 */
float compute_file_size(const std::string &fname, const long units=1);


#endif //__COMMON_CODE_HPP__
