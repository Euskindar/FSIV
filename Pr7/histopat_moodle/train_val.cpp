// ----------------------------------------
// train.cpp
// (c) FSIV, University of Cordoba
// ----------------------------------------

#include <iostream>
#include <exception>

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

#include "common_code.hpp"
// #include "lbp.hpp"
#include "metrics.hpp"

#define FSIV_VALIDATE_RATIO 0.2   // Percentage of data for validation: default 0.2

#ifndef NDEBUG
int __Debug_Level = 0;
#endif

const cv::String keys =
    "{help h usage ? |      | print this message   }"        
    "{img_norm       |0    | Image normalization: 0: none, 1:minmax, 2:mean_stdDev.}"
    "{v validate     |      | Use the training/validation partitions to train "
    "and validate, else use both partitions to train again an already trained model.}"
    "{t test         |      | Only test a trained model.}"
    "{class        |0     | Classifier to train/test. 0: K-NN, 1:SVM, 2:RTREES.}"
    "{d desc       |0     | Descriptor type. 0: gray, 1: ???}"
    "{knn_K        |1     | Parameter K for K-NN class.}"
    "{svm_C        |1.0   | Parameter C for SVM class.}"
    "{svm_K        |0     | Kernel to use with SVM class. 0:Linear, 1:Polinomial. "
    "2:RBF, 3:SIGMOID, 4:CHI2, 5:INTER}"
    "{svm_D        |3.0   | Degree of svm polinomial kernel.}"
    "{svm_G        |1.0   | Gamma for svm RBF kernel.}"
    "{rtrees_V     |0     | Num of features random sampled per node. "
    "Default 0 meas sqrt(num. of total features).}"
    "{rtrees_T     |50    | Max num. of rtrees in the forest.}"
    "{rtrees_E     |0.1   | OOB error to stop adding more rtrees.}"
    "{@dataset_path  |<none>| Dataset pathname.}"
    "{@model         |<none>| Model filename.}"
#ifndef NDEBUG
    "{verbose        |0     | Set the verbose level.}"
#endif
    ;

int
main (int argc, char* const* argv)
{
  int retCode=EXIT_SUCCESS;

  try {

      cv::CommandLineParser parser(argc, argv, keys);
      parser.about("Train a histopathology classifier.");
      if (parser.has("help"))
      {
          parser.printMessage();
          return 0;
      }

#ifndef NDEBUG
      __Debug_Level = parser.get<int>("verbose");
#endif      
      bool validate = parser.has("v");
      bool only_testing = parser.has("t");
      if (validate && only_testing)
      {
          std::cerr << "Error: Validating and only testing are not "
                       "compatible options." << std::endl;
          return EXIT_FAILURE;
      }
      int img_norm = parser.get<int>("img_norm");

      std::string dataset_path = parser.get<std::string>("@dataset_path");
      std::string model_fname = parser.get<std::string>("@model");
      int classifier = parser.get<int>("class");
      int desctype = parser.get<int>("desc");
      int knn_K = parser.get<int>("knn_K");
      float svm_C = parser.get<float>("svm_C");
      int svm_K = parser.get<int>("svm_K");
      float svm_D = parser.get<float>("svm_D");
      float svm_G = parser.get<float>("svm_G");
      int rtrees_V = parser.get<int>("rtrees_V");
      int rtrees_T = parser.get<int>("rtrees_T");
      double rtrees_E = parser.get<double>("rtrees_T");
      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }

      cv::Mat train_descs, train_labels;
      cv::Mat val_descs, val_labels;      
      cv::Mat test_descs, test_labels;
      bool hist_norm = true;      
      cv::Size canonical_size(64, 64);

      std::string filename = dataset_path + "/" + "train_labels.txt";
      std::string dbdir = dataset_path + "/" + "train_128"; 
	  
      std::string filename_test = dataset_path + "/" + "test_labels.txt";
      std::string dbdir_test = dataset_path + "/" + "test_128"; 
      
      std::vector<std::string> train_images, test_images;      
      std::vector<int> categories;
      for (int i = 0; i < 4; i++) categories.push_back(i);
      std::vector <std::string> category_descs = { "0", "1", "2", "3" }; // TODO set names of classes

      bool dbloaded = fsiv_load_dbdata(filename, train_images, train_labels);

      std::cout << "DB loaded? " << dbloaded << std::endl;
      std::cout << train_labels.size() << std::endl;
      std::cout << "Last one: " << train_images[train_labels.rows - 1] << std::endl;

      // VALIDATION partition
      std::vector<int> idx_val, idx_train;

      if (validate)
      {
          // TODO: split training data into training and validation
          std::cout << FSIV_VALIDATE_RATIO * 100 << "% used for validation." << std::endl;

          // Populate idx_val and idx_train
          // . . . 
      }

      bool dbloaded_test;
      if (only_testing)
      {
          std::cout << "Preparing test data...";
          dbloaded_test = fsiv_load_dbdata(filename_test, test_images, test_labels);
          if (dbloaded_test)
            std::cout << "done!" << std::endl;
          else
            std::cout << " ERROR: couldn't load test data!" << std::endl;

          // Extract features
          if (!fsiv_compute_desc_from_list(test_images,
              dbdir_test,
              canonical_size,
              test_descs,
              desctype,
              img_norm,
              hist_norm))
          {
              std::cerr << "Error: could not compute test features."
                  << std::endl;
              return EXIT_FAILURE;
          }
          else
              std::cerr << "Computed test features." << std::endl;

          std::cout << test_descs.size() << std::endl;
      }
      else {
          // Extract features
          if (!fsiv_compute_desc_from_list(train_images,
              dbdir,
              canonical_size,
              train_descs,
              desctype,
              img_norm,
              hist_norm))
          {
              std::cerr << "Error: could not compute training features."
                  << std::endl;
              return EXIT_FAILURE;
          }
          else
              std::cerr << "Computed training features." << std::endl;

          std::cout << train_descs.size() << std::endl;
      }


      // TRAINING
      cv::Ptr<cv::ml::StatModel> clsf;
      int train_flags = 0;

      if (validate)
      {
          //  TYPE OF CLASSIFIER
          if (classifier == 0)
          {
              //cv::Ptr<cv::ml::KNearest> knn;

              //TODO: Create an KNN classifier.
              //Set algorithm type to BRUTE_FORCE.
              //Set it as a classifier (setIsClassifier)
              //Set hyperparameter K.

              //
              assert(knn != nullptr);
              clsf = knn;
          }
          else if (classifier == 1)
          {
              cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();

              //TODO: Create an SVM classifier.
              //Set algorithm type to C_SVC.              
              //Set hyperparameters: C, kernel, Gamma, Degree.
              
              //
              assert(svm != nullptr);
              clsf = svm;              
          }
          else if (classifier == 2)
          {
              cv::Ptr<cv::ml::RTrees> rtrees;
              //TODO: Create an RTrees classifier.
              //Set hyperparameters: Number of features used per node (ActiveVarCount).
              //Remenber that rtrees_V=0 means to use the default value.
              //Set the max num of trees rtrees_T, and required OOB error rtrees_E
              //using a cv::TermCriteria object.


              //
              assert(rtrees != nullptr);
              clsf = rtrees;
          }
          else
          {
              std::cerr << "Error: unknown classifier." << std::endl;
              return EXIT_FAILURE;
          }


          // TODO: train only with the samples from the training subset (excluding the validation ones)

          std::cout << "Training with " << train_labels.rows << " samples ... ";

          

          //TODO: train the classifer using training data.        
          
          //
          CV_Assert(clsf->isClassifier());
          assert(clsf->isTrained());
          std::cout << "done." << std::endl;
      }
      else
      {
          train_flags = cv::ml::StatModel::UPDATE_MODEL;
          if (classifier == 0)
              //TODO: load a KNN classifier.
              
          //
          else if (classifier == 1)
              //TODO: load a SVM classifier.
              
          //
          else if (classifier == 2)
              //TODO: load a RTrees classifier.
              ;
          //
          else
          {
              std::cerr << "Error: unknown classifier." << std::endl;
              return EXIT_FAILURE;
          }
          if (clsf == nullptr || !clsf->isTrained())
          {
              std::cerr << "Error: Non valid mode selected. I need a trained model!" << std::endl;
              return EXIT_FAILURE;
          }
      }


      //TODO: make the predictions over the validation/test data.
      std::cout << "--- PREDICTING ---" << std::endl;
      cv::Mat predict_labels, target_labels, target_descs;
      if (only_testing)
      {
          // TODO
      }
      else
      {
          // TODO 
      }
            
      //
      assert(!predict_labels.empty() && predict_labels.rows == target_descs.rows);

      //Compute the confusion matrix.
      cv::Mat cmat = compute_confusion_matrix(cv::Mat_<float>(target_labels),
          predict_labels);

      float mrr = compute_mean_recognition_rate(cmat, categories);
      float acc = compute_accuracy(cmat);

      std::cout << "##############################" << std::endl;
      std::cout << "# Model metrics: ";
      if (validate)
          std::cout << " VALIDATION" << std::endl;
      else
          std::cout << " TESTING" << std::endl;
      std::cout << "##############################" << std::endl;
      std::cout << std::endl;
      std::cout << "Accuracy : " << acc << std::endl;
      std::cout << "Mean RR  : " << mrr << std::endl;
      std::cout << "RR per class: " << std::endl;
      for (size_t c = 0; c < categories.size(); c++)
          std::cout << "\t[" << category_descs[c] << "]: "
          << compute_recognition_rate(cmat, categories[c])
          << std::endl;
      std::cout << std::endl;

      if (!only_testing)
      {
          std::cout << "Saving the model to '" << model_fname << "'." << std::endl;
          clsf->save(model_fname);
      }

      std::cout << "Model size: " << compute_file_size(model_fname, 1024 * 1024)
          << " MB." << std::endl;

  }
  catch (std::exception& e)
  {
    std::cerr << "Exception caught: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
