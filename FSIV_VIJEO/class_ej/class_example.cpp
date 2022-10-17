#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>
#include <opencv2/imgproc.hpp>

using namespace std;

cv::Mat image;

int main(int argc, char **argv)
{
  cv::Mat image = cv::imread("image.jpg", 0);
  cv::namedWindow("Grayscale_Image", 1);
  cv::imshow("Grayscale_Image", image);
  cv::waitKey(0);

  std::vector<int> histogram(256);  // Array to save histogram values
  std::vector<int> C_histogram(image.rows * image.cols);  // Comulative histogram

  uchar* ptr; //pointer to go throw to the matrix
  for (size_t row = 0; row < image.rows; row++)
  {
    for (size_t cols = 0; cols < image.cols; cols++)
    {
      ptr = image.ptr<uchar>(cols) + row;

      for (size_t i = 0; i < 256; i++)
      {
        if (*ptr == i)
        {
          histogram[i]++;
        }
      }
    }
  }

  std::cout << "HISTOGRAM" << '\n';
  for (size_t i = 0; i < 256; i++) {
    std::cout << histogram[i] << '\n';
  }






  cv::waitKey(0);
}
