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

// int max_pixels = 0; // Maximun brightest pixels
// float percentage = 0.01;  // Percentage value

////////////////////////////////////////////////////////////////////////////////

//Single pixel WP -> Saves the maximum value's coordinates
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
        // Add the scale value to every pixel
        ptr[0] += B_value;
        ptr[1] += G_value;
        ptr[2] += R_value;

        // CHeck not to surpass the max color value
        if (ptr[0] > 255) {ptr[0] = 255;}
        if (ptr[1] > 255) {ptr[1] = 255;}
        if (ptr[2] > 255) {ptr[2] = 255;}

        ptr += 3; // Moves the pointer to the next pixel
      }

    }

    cv::namedWindow("Image_WP");
    cv::imshow("Image_WP", image);
  }

  //check if a command is present
  if (cml["-p"])
  {
  }

  if (cml["-i"])
  {
  }


  // Waits until ESC pressed
  char c = 0;
  while(c != 27)
  {
    c = cv::waitKey(0);
  }

  return 0;
}
