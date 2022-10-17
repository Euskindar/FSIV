#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <cstring>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////

//Class to manage command line arguments.
// Copy in your program!
class CmdLineParser{
  int argc;
  char **argv;
public:
  CmdLineParser(int _argc, char **_argv):argc(_argc), argv(_argv)
  {
  }

  bool operator[] ( string param )
  {
    int idx = -1;

    for (int i = 0; i < argc && idx == -1; i++)
      if (string (argv[i]) == param) idx = i;
        return(idx != -1);
  }

  string operator()(string param, string defvalue = "-1")
  {
    int idx = -1;

    for (int i = 0; i < argc && idx == -1; i++)
      if (string(argv[i]) == param)
        idx = i;

      if (idx == -1)
        return defvalue;
      else
        return(argv[idx+1]);
  }
};

///////////////////////////////////////////////////////////////////////////////////

// Global variables
cv::Mat input_image;
cv::Mat output_image;
cv::Mat final_image;

int threshold = 0;

std::string morphological;

///////////////////////////////////////////////////////////////////////////////////

// Threshold function
void threshold_transformation()
{
  for (size_t row = 0; row < input_image.rows; row++)
  {
    for (size_t col = 0; col < input_image.cols; col++)
    {
      if (input_image.at<int>(row, col) < threshold)
      {
        output_image.at<int>(row, col) = 255;
      }
      else
      {
        output_image.at<int>(row, col) = 0;
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////

// Erode function
void erode()
{

}

///////////////////////////////////////////////////////////////////////////////////

// Dilate function
void dilate()
{

}

///////////////////////////////////////////////////////////////////////////////////

// Close function
void close()
{

}

///////////////////////////////////////////////////////////////////////////////////

// Open function
void open()
{

}

///////////////////////////////////////////////////////////////////////////////////

// Calls the corresponding function
void morph_transformation()
{
  if (morphological == "erode")
  {
    erode();
  }

  if (morphological == "dilate")
  {
    dilate();
  }

  if (morphological == "close")
  {
    close();
  }

  if (morphological == "open")
  {
    open();
  }
}

///////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
  CmdLineParser cml(argc,argv);

  // Check if a command is present
  if (cml["-thres"])
  {
    // Convert to int
    threshold = std::stoi(cml("-thres"));
    std::cout << "\n\tThreshold = " << threshold << '\n';
  }

  // Check if a command is present
  if (cml["-op"])
  {
    morphological = cml("-op");
    std::cout << "\n\tMorphological transformation = " << morphological << "\n\n";
  }

  // Read input image in grayscale
  input_image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
  cv::imshow("INPUT Image", input_image);

  // Read output image in grayscale
  output_image = cv::imread(argv[2], cv::IMREAD_GRAYSCALE);

  threshold_transformation();
  cv::imshow("OUTPUT Image", output_image);

  morph_transformation();

  // cv::imshow("Final image", final_image);

  // Waits until ESC pressed
  char c = 0;
  while(c != 27)
  {
    c = cv::waitKey(0);
  }

  // Saving the modified image
  // cv::imwrite("IMG_mod.jpg", image);

  return 0;
}
