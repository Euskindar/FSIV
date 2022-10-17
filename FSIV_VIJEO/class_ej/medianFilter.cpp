#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <cstring>

////////////////////////////////////////////////////////////////////////////////

// Global variables
int sobel_vec_x[3][3] = {-1,0,1, -2,0,2, -1,0,1};
int sobel_vec_y[3][3] = {-1,-2,-1, 0,0,0, 1,2,1};

cv::Mat float_image;

cv::Mat sobel_kernel_X = cv::Mat(3, 3, CV_8U, &sobel_vec_x);
cv::Mat sobel_kernel_Y = cv::Mat(3, 3, CV_8U, &sobel_vec_y);

cv::Mat result_image_X;
cv::Mat result_image_Y;

cv::Mat final_image;

////////////////////////////////////////////////////////////////////////////////

// Box filter
void convolve(const cv::Mat &input, const cv::Mat &filter, cv::Mat &out)
{
  assert((!input.empty()) && (input.type() == CV_32FC1));
  assert((!filter.empty()) && (filter.type() == CV_32FC1));
  assert(((filter.rows%2) != 0) && ((filter.cols%2) != 0));

  float value = 0;
  float sum = 0.0;

  cv::Mat aux = input.clone();
  cv::Mat aux2 = filter.clone();

  int r = (filter.rows-1) / 2;

  out = cv::Mat::zeros(input.rows, input.cols, input.type());

  for (int row = r; row < (input.rows-r); row++)
  {
    float *outPtr = out.ptr<float>(row);

  	for(int col = r; col < (input.cols-r); col++)
    {
      for (int k = row-r, xx = 0; k <= (row+r); k++, xx++)
      {
        float *inPtr = aux.ptr<float>(k);
        float *filterPtr = aux2.ptr<float>(xx);

        for (int l = col-r, yy = 0; l <= (col+r); l++, yy++)
        {
          sum += inPtr[l]*filterPtr[yy];
  			}
  		}

  		outPtr[col] = sum;
  		sum = 0.0;
  	}
  }
}

////////////////////////////////////////////////////////////////////////////////

// Median filter
void medianFilter(const cv::Mat &input, cv::Mat &output, const int size)
{
  output = cv::Mat::zeros(input.rows, input.cols, input.type());

  for (size_t row = 0; row < input.rows; row++)
  {
    for (size_t col = 0; col < input.cols; col++)
    {




    }
  }
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
  // Read image in grayscale
  float_image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

  // Convert image and kernel to floating point
  float_image.convertTo(float_image, CV_32FC1);

  sobel_kernel_X.convertTo(sobel_kernel_X, CV_32FC1, 1/255.0);
  sobel_kernel_Y.convertTo(sobel_kernel_Y, CV_32FC1, 1/255.0);

  // Do the convolution
  convolve(float_image, sobel_kernel_X, result_image_X);
  convolve(float_image, sobel_kernel_Y, result_image_Y);

  cv::imshow("Image", float_image);
  // cv::imshow("Image X", result_image_X);
  // cv::imshow("Image Y", result_image_Y);

  // Join both result images in one
  unify_images(result_image_X, result_image_Y, final_image);



  cv::imshow("Final image", final_image);

  // Waits until ESC pressed
  char c = 0;
  while(c != 27)
  {
    c = cv::waitKey(0);
  }

  // Saving the modified image
  // cv::imwrite("IMG_mod.jpg", float_image);

  return 0;
}
