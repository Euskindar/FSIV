#ifndef TASK3_HPP
#define TASK3_HPP

#include <opencv2/core/core.hpp> //core routines
#include <opencv2/imgproc.hpp>//to draw rectangles
#include <opencv2/core/types.hpp>//to add points
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey

#include <iostream>
#include <vector>//to use stl vectors
#include <cmath>//for pow function
#include <cassert>

using namespace std;

class CmdLineParser{
   int argc;
   char **argv;
public:
   CmdLineParser(int _argc,char **_argv):argc(_argc),argv(_argv){}
   bool operator[] ( string param ) {
     int idx=-1;
     for ( int i=0; i<argc && idx==-1; i++ )
     if ( string ( argv[i] ) == param ) idx=i;
     return ( idx!=-1 ) ;
   }
   string operator()(string param,string defvalue="-1"){
     int idx=-1;
     for ( int i=0; i<argc && idx==-1; i++ )
     if ( string ( argv[i] ) ==param ) idx=i;
     if ( idx==-1 ) return defvalue;
     else  return ( argv[  idx+1] );
   }
};

cv::Mat create_sharp_filter(int &f, float &g);
void convolve(const cv::Mat &image, cv::Mat &filter, cv::Mat result);
float apply_filter(cv::Mat &filter, cv::Mat &subImage);
cv::Mat get_sub_image(cv::Mat &image, int i, int j);

#endif