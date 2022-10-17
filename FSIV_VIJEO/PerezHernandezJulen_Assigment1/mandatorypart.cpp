#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>
#include <opencv2/imgproc.hpp>

using namespace std;

cv::Mat image;
cv::Point p1;
cv::Point p2;

char reset[255];

int flag = 0;


void on_mouse(int event, int x, int y, int flags, void* param)
{
  if(event == cv::EVENT_LBUTTONDOWN)
  {
    if(flag == 0)
    {
      cout<<"First click"<<endl;

      p1.x = x;
      p1.y = y;

      flag++;
    }
    else if(flag == 1)
    {
      cv::Size s = image.size();

      int x_max = s.width;
      int y_max = s.height;

      image = cv::imread(reset);

      cout<<"Second click"<<endl;

      p2.x = x;
      p2.y = y;

      //Now we have to know what are the biggest values
      int x_top, x_low;
      int y_top, y_low;

      if(p1.y < p2.y)
      {
        y_top = p2.y;
        y_low = p1.y;
      }
      else
      {
        y_top = p1.y;
        y_low = p2.y;
      }

      if(p1.x < p2.x)
      {
        x_top = p2.x;
        x_low = p1.x;
      }
      else
      {
        x_top = p1.x;
        x_low = p2.x;
      }

      uchar *ptr;
      int avg;

      for(int i = 0; i < x_max; i++)
      {
        for(int j = 0; j < y_max; j++)
        {
          if(((i < x_low)||(i > x_top)) || ((j < y_low)||(j > y_top)))
          {
            ptr = image.ptr<uchar>(j) + 3*i; //pinter to go throw to the matrix
            avg = ptr[0] + ptr[1] + ptr[2];
            avg = avg / 3;

            ptr[0] = avg;
            ptr[1] = avg;
            ptr[2] = avg;
          }
        }
      }

      cv::imshow("Modded image", image);

      flag++;
    }
    else if(flag == 2)
    {
      cout<<"Image closed"<<endl<<endl;
      image = cv::imread(reset);

      cv::destroyWindow("Modded image");

      cv::imshow("Image", image);

      flag = 0;
    }
  }
}

int main(int argc, char **argv)
{
  strcpy(reset, argv[1]);
  //We show the image we ask for in the terminal
  image = cv::imread(argv[1]);
  cv::namedWindow("Image");
  //Indicates what callback function it has to call
  cv::setMouseCallback("Image", on_mouse, 0);

  cv::imshow("Image", image);
  cv::waitKey(0);
}
