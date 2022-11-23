// ----------------------------------------
// common_code.cpp
// (c) FSIV, University of Cordoba
// ----------------------------------------

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "common_code.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>

#ifndef NDEBUG


const std::string __Debug_Padding =
"                                                                              "
"                                                                              "
"                                                                              "
"                                                                              "
"                                                                              ";
size_t __Debug_PPL = 3;
#endif

bool fsiv_load_dbdata(const std::string & filename, std::vector<std::string> & limages, cv::Mat & labels)
{

    std::vector<int> labels_tmp;

    // Open text file and read lines. Each line contains the path to an image and its label
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string image;
        int label;
        if (!(iss >> image >> label))
        {
            std::cerr << "Error reading file " << filename << std::endl;
            return false;
        }
        limages.push_back(image);
        labels_tmp.push_back(label);
    }

    labels = cv::Mat(labels_tmp).clone();

    return true;
}

cv::Mat
fsiv_normalize_mean_var(cv::Mat const& src)
{
    assert(!src.empty() && src.channels()==1);
    cv::Mat dst;

    //TODO: normalize source image so its mean will be equal to 0.0 and
    // its var equal to 1.0.
    // Hint: use cv::meanStdDev() to get the source mean and stdev.


    //
#ifndef NDEBUG
    assert(!dst.empty());
    {
        std::vector<double> mean, stdev;
        cv::meanStdDev(dst, mean, stdev);
        assert(std::abs(mean[0])<=1.0e-5 && std::abs(stdev[0]-1.0)<=1.0e-5);
    }
#endif
    return dst;
}

cv::Mat
fsiv_normalize_minmax(cv::Mat const& src)
{
    assert(!src.empty() && src.channels()==1);
    cv::Mat dst;

    //TODO: normalize the source image so its mininum value will be 0.0 and its
    // maximun value be 1.0
    // Hint: use cv::normalize()



    //

#ifndef NDEBUG
    assert(!dst.empty());
    {
        assert(dst.type()==CV_32FC1);
        double min,max;
        cv::minMaxLoc(dst, &min, &max);
        assert(std::abs(min)<=1.0e-6 && std::abs(max-1.0)<=1.0e-6);
    }
#endif
    return dst;
}

bool
string_to_ncells(const std::string& str, int n_cells[])
{
    bool ret_val = true;
    std::istringstream input(str);
    char sep;
    input >> n_cells[0] >> sep >> n_cells[1];
    if (!input)
        ret_val = false;
    else
        ret_val = ((n_cells[0]*n_cells[1]) > 0);
    return ret_val;
}


bool fsiv_desc_simple_gray(const cv::Mat & image, cv::Mat & desc)
{
    std::vector<float> vimg(image.begin<float>(), image.end<float>());
            
    cv::Mat vimg_mat(vimg);
    
    desc = vimg_mat.t();

    return true;
}


bool
fsiv_compute_desc_from_list(const std::vector<std::string> & lfiles, 
                      const std::string & dbdir,                     
                      const cv::Size& canonical_size,
                      cv::Mat & l_descs, const int desctype,
                      const int img_norm, bool hist_norm)
{
    DEBUG(1, "Computing ft descriptors from files" << std::endl);
    bool ret_val = true;
    for (size_t i =0; i < lfiles.size() && ret_val; i++)
    {
        DEBUG(2, "\t Processing image: '" << lfiles[i] << "'." << std::endl);

    // Concatenate dbdir to filename
    std::string imgname = dbdir + "/" + lfiles[i];

    cv::Mat image = cv::imread(imgname, cv::IMREAD_GRAYSCALE);

        if (!image.empty())
        {
            image.convertTo(image, CV_32F, 1.0/255.0, 0.0);
#ifndef NDEBUG
            if (__Debug_Level>=3)
            {
                cv::imshow("IMAGE", image);
                cv::imshow("ROI", image(rois[i]));
            }
#endif
            if (img_norm==1)
                image = fsiv_normalize_minmax(image);
            else if (img_norm==2)
                image = fsiv_normalize_mean_var(image);
            cv::Mat canonical_img;
            cv::resize(image, canonical_img, canonical_size);
            cv::Mat ft_img;

            cv::Mat vimg_mat;
			// TODO: use 'desc_type' to choose your descriptors
			// EXAMPLE:
            fsiv_desc_simple_gray(canonical_img, vimg_mat);

            if (i==0)
            {
                l_descs = cv::Mat(lfiles.size(), vimg_mat.cols, CV_32FC1);
                vimg_mat.copyTo(l_descs.row(0));
            }
            else
                vimg_mat.copyTo(l_descs.row(i));
                
#ifndef NDEBUG
            if (__Debug_Level>=3)
            {
                if ((cv::waitKey(0)&0xff)==27)
                    return false;
            }
#endif
        }
        else
            ret_val = false;
    }
#ifndef NDEBUG
            if (__Debug_Level>=3)
                cv::destroyAllWindows();
#endif
    return ret_val;
}


float
compute_file_size(std::string const& fname, const long units)
{
    float size = -1.0;
    std::ifstream file (fname);
    if (file)
    {
        file.seekg (0, file.end);
        long length = file.tellg();
        size = static_cast<float>(length) / static_cast<float>(units);
    }
    return size;
}
