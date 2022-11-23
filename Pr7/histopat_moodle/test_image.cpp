// ----------------------------------------
// test.cpp
// (c) FSIV, University of Cordoba
// ----------------------------------------

#include <iostream>
#include <exception>
#include <vector>

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

#include "common_code.hpp"


#ifndef NDEBUG
int __Debug_Level = 0;
#endif

const cv::String keys =
    "{help h usage ? |      | print this message   }"    
    "{img_norm       |0    | Image normalization: 0: none, 1:minmax, 2:mean_stdDev.}"    
    "{class        |0     | Classifier to train. 0: K-NN, 1:SVM, 2:RTREES.}"
    "{d desc       |0     | Descriptor type. 0: gray, 1: ???}"
    "{@dataset       |<none>| Dataset pathname.}"
    "{@model         |<none>| Model filename.}"
    "{@image         |<none>| Input image.}"
#ifndef NDEBUG
    "{verbose        |0     | Set the verbose level.}"
#endif
    ;

int
main (int argc, char* const* argv)
{
  int retCode=EXIT_SUCCESS;
  cv::Size canonical_size(64, 64);

  try {

      cv::CommandLineParser parser(argc, argv, keys);
      parser.about("Test the traffic sign classifier on a input image.");
      if (parser.has("help"))
      {
          parser.printMessage();
          return 0;
      }

#ifndef NDEBUG
      __Debug_Level = parser.get<int>("verbose");
#endif

      int img_norm = parser.get<int>("img_norm");
      int desctype = parser.get<int>("desc");

      std::string model_fname = parser.get<std::string>("@model");
      int classifier = parser.get<int>("class");
      cv::Mat input_img = cv::imread(parser.get<std::string>("@image"), cv::IMREAD_COLOR);
      if (input_img.empty())
      {
          std::cerr << "Error: could not read the input image '"
                    << parser.get<std::string>("@image") << "'." << std::endl;
          return EXIT_FAILURE;
      }
      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }
      std::vector<int> categories;
      for (int i = 0; i < 4; i++) categories.push_back(i);
      std::vector<std::string> categories_names = { "0", "1", "2", "3" }; // TODO: insert names


      std::cout << "Loading classifier's model ... ";
      cv::Ptr<cv::ml::StatModel> clsf;
      if (classifier==0)
          //TODO: Load a KNearest model.
          clsf = cv::Algorithm::load<cv::ml::KNearest>(model_fname);
          //
      else if (classifier==1)
          //TODO: Load a SVM model.
          ;
          //
      else if (classifier==1)
          //TODO: Load a RTrees model.
          ;
          //
      else
      {
          std::cerr << "Error: unknown classifier." << std::endl;
          return EXIT_FAILURE;
      }
      assert(clsf!=nullptr && clsf->isTrained());
      std::cout << " ok." << std::endl;      

      bool go_out = false;
      while (! go_out)
      {
        cv::Rect roi = cv::selectROI("SELECT THE ROI", input_img);
        cv::destroyWindow("SELECT THE ROI");
        if (roi.area()==0)
            go_out = true;
        else
        {
            cv::Mat roi_img_color, roi_img;
            //TODO: Get the ROI and convert to gray
            roi_img_color = input_img(roi);
#if (CV_VERSION_MAJOR > 3)
            cv::cvtColor(roi_img_color, roi_img, cv::COLOR_BGR2GRAY);
#else
            cv::cvtColor(roi_img_color, roi_img, CV_BGR2GRAY);
#endif
            // cv::convertTo()

            //
            assert(!roi_img.empty() && roi_img.type()==CV_8UC1);
            if (img_norm == 0)
            {
                //TODO: convert ROI to range to [0, 1]
                roi_img.convertTo(roi_img, CV_32F, 1.0/255.0, 0.0);
                //
#ifndef NDEBUG
                {
                    double min,max;
                    assert(roi_img.type()==CV_32FC1);
                    cv::minMaxLoc(roi_img, &min, &max);
                    assert(min>=0.0 && max <= 1.0);
                }
#endif
            }
            else if (img_norm == 1)
                roi_img = fsiv_normalize_minmax(roi_img);
            else if (img_norm == 2)
                roi_img = fsiv_normalize_mean_var(roi_img);
            else
            {
                std::cerr << "Error: unknown image normalization method."
                          << std::endl;
                return EXIT_FAILURE;
            }

            
            cv::Mat canonical_img, ft_desc;
            cv::resize(roi_img, canonical_img, canonical_size);
            cv::Mat vimg_mat;
            fsiv_desc_simple_gray(canonical_img, ft_desc);

            cv::Mat y_pred;

            //TODO: get the classifier prediction.
            clsf->predict(ft_desc, y_pred);
            std::cout << y_pred << std::endl;
            //
            assert(!y_pred.empty() && y_pred.rows==1);


            auto cat_it = std::find(categories.begin(), categories.end(),
                                    static_cast<size_t>(y_pred.at<float>(0)));
            std::string sign_name = "Unknown!!!";
            if (cat_it != categories.end())
                    sign_name = categories_names[cat_it-categories.begin()];
            cv::Mat aux_img;
            input_img.copyTo(aux_img);
            cv::rectangle(aux_img, roi.tl(), roi.br(), cv::Scalar(0,255,0));
            cv::putText(aux_img, sign_name,
                        cv::Point(roi.x+1, roi.y+roi.height/2),
                        cv::FONT_HERSHEY_SIMPLEX, 1.0,
                        cv::Scalar(0,255,0),
                        3);

            cv::imshow("PREDICTION", aux_img);
            cv::waitKey(0);
            cv::destroyWindow("PREDICTION");
        }
      }
  }  
  catch (std::exception& e)
  {
    std::cerr << "Exception caught: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
