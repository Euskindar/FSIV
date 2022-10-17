#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <cstring>

#include <bits/stdc++.h>  //sort
#include <opencv2/imgproc.hpp>  //cvtColor


using namespace std;

////////////////////////////////////////////////////////////////////////////////

//Class to manage command line arguments.
class CmdLineParser
{
  int argc;
  char **argv;

public:
  CmdLineParser(int _argc, char **_argv):argc(_argc), argv(_argv)
  {
  }

  bool operator[] ( string param )
  {
    int idx = -1;

    for ( int i = 0; i < argc && idx == -1; i++ )
      if ( string ( argv[i] ) == param )
        idx = i;
    return ( idx != -1 );
  }

  string operator() (string param, string defvalue = "-1")
  {
    int idx = -1;

    for ( int i = 0; i < argc && idx == -1; i++ )
      if ( string ( argv[i] ) == param ) idx = i;
        if ( idx == -1 )
          return defvalue;
        else
          return ( argv[idx+1] );
  }
};

////////////////////////////////////////////////////////////////////////////////

//Global variables
cv::Mat image;
cv::Mat image2;

float brightness = 0;
float percentage = 0.01;

int c1_value = 0;

int brightness_slider = 1;
int max_pixels = 0; // Maximun brightest pixels

std::vector<int> pixels;  // Array for the brightest pixels values

////////////////////////////////////////////////////////////////////////////////

//Single pixel WP
void singlePixelWP(int &max_pos_ROW, int &max_pos_COL)
{
  int wpix = 0, actual_pixel = 0;

  // Iterates the whole image
  for (int row = 0; row < image.rows; ++row)  // ROWS
  {
    uchar *ptr = image.ptr<uchar>(row); // pointer to the y-th image row

    for (int col = 0; col < image.cols; ++col)  // COLUMNS
    {
      actual_pixel = ptr[0];
      actual_pixel += ptr[1];
      actual_pixel += ptr[2];

      if (wpix < actual_pixel)  // Save the maximun image value
      {
        wpix = actual_pixel;  // Update the max value

        // Saves the pixel position
        max_pos_ROW = row;
        max_pos_COL = col;
      }

      ptr += 3; // Moves the pointer to the next pixel
    }
  }
}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

void modify()
{

  float *ptr;

  int i = 0; // Iterator

  for (int row = 0; (row < image.rows) && (i < pixels.size()); ++row)  // ROWS
  {
    for (int col = 0; (col < image.cols) && (i < pixels.size()); ++col)  // COLUMNS
    {
      c1_value = image.at<uchar>(row, col);

      pixels[i] = c1_value;

      i++;
    }
  }
  std::cout << "/* message */   " << i << '\n';

  std::sort(pixels.begin(), pixels.end(), greater<int>());  // sort in descending order

  // Calculates the sum and scale
  int sum = 0;
  for (size_t i = 0; i < pixels.size(); i++)
  {
    // std::cout << pixels.at(i)<<"\t";

    sum += pixels.at(i);
  }
  sum /= pixels.size();
  sum = 255-sum;


  image2 += sum;

}

////////////////////////////////////////////////////////////////////////////////

void on_tracback_percentage(int, void*)
{
  brightness = ((float)brightness_slider / 100);

  // image.convertTo(image2, CV_32F, 1.0/255.0, 0);

  std::cout << "Percentage2: " << brightness*100 << "%" << '\n';

  max_pixels = (int)(image.rows*image.cols*(percentage/100));
  pixels.resize(max_pixels);

  modify();

  image2.convertTo(image2, CV_8U, 255.0, 0);

  cv::imshow("Image", image);
  cv::imshow("Processed", image2);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
  CmdLineParser cml(argc,argv);

  // image = cv::imread(argv[1]);
  image = cv::imread(argv[1]);

  std::cout << "\n\tChannels in final image: " << image.channels() << '\n';

  // Only the images, calculates the WP with a single pixel
  if (argc == 3)
  {
    cv::namedWindow("Image");
    cv::imshow("Image", image);

    // Save the position of the max value pixel of the image
    int max_position_ROW = 0, max_position_COL = 0;
    singlePixelWP(max_position_ROW, max_position_COL);

    // Modify the image to scale the max value pixel to (255)
    uchar *max_ptr = image.ptr<uchar>(max_position_ROW, max_position_COL);
    int B_value = 255-max_ptr[0]; // B
    int G_value = 255-max_ptr[1]; // G
    int R_value = 255-max_ptr[2]; // R

    // Iterates the whole image
    for (int row = 0; row < image.rows; ++row)  // ROWS
    {
      uchar *ptr = image.ptr<uchar>(row); // pointer to the y-th image row

      for (int col = 0; col < image.cols; ++col)  // COLUMNS
      {
          ptr[i] = ;
          if (ptr[i] ) {
            /* code */

        }

        ptr += 3; // Moves the pointer to the next pixel

      }

    }
  }

  //check if a command is present
  if (cml["-p"])
  {
    percentage = std::stof(cml("-p"))*100; // Convert to float
    std::cout << "\n\tInitial Percentage: " << percentage << "%" << '\n';

    max_pixels = (int)(image.rows*image.cols*(percentage/100));
    pixels.resize(max_pixels);

    image.convertTo(image2, CV_32F, 1.0/255.0, 0);
    image2 = image.clone();

    modify();

    // image2.convertTo(image2, CV_8U, 255.0, 0);

    cv::imshow("Image", image);
    cv::imshow("Final image", image2);

    // Saving the modified image
    cv::imwrite("IMG_mod.jpg", image2);
  }

  if (cml["-i"])
  {
    cv::namedWindow("Processed");

    // Create trackbar
    cv::createTrackbar("Brightness", "Processed", &brightness_slider, 100, on_tracback_percentage, NULL);
    on_tracback_percentage(brightness_slider, 0);

    cv::imwrite("IMG_mod.jpg", image2);
  }


  // Waits until ESC pressed
  char c = 0;
  while(c != 27)
  {
    c = cv::waitKey(0);
  }

  return 0;
}
