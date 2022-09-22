#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <opencv2/core/utility.hpp> //command line parser
#include <iostream>

using namespace std;
//using namespace cv;


const string keys =
	"{help h usage ? |     | All parameters descriptions}"
	"{@image         |     | image to operate with}"
	"{N count        | 50  | Constant to be added}"
;



// Control that the addition doest surpass 255
uchar controlOverflow(int px, int k)
{
	if(px + k > 255)
	{
		return 255;
	}
	else
	{
		return px+k;
	}
}



int main(int argc,char **argv)
{
	try
	{
		cv::CommandLineParser parser(argc, argv, keys);

		parser.about("Exercise 1");
		
		if (parser.has("help"))
		{
		    parser.printMessage();
		    return 0;
		}
		
		cv::String image = parser.get<cv::String>(0);

		int N = parser.get<int>("N");
		
		if (!parser.check())
		{
		    parser.printErrors();
		    return 0;
		}






		cout<<"x,y="<<x<<" "<<y<<endl;
		//set as red a small window around
		int xleft=x-3;
		if( xleft<0) xleft=0;//check not out of image
		int yleft=y-3;
		if( yleft<0) yleft=0;//check not out of image
		int xright=x+3;
		if( xright> image.cols) xright=image.cols-1;//check not out of image
		int yright=y+3;
		if( yright> image.rows) yright=image.rows-1;//check not out of image

		for( int x=xleft;x<=xright;x++)
			for( int y=yleft;y<=yright;y++){
				uchar *ptr=image.ptr<uchar>(y)+3*x;
				ptr[0] = controlOverflow(ptr[0], N);
				ptr[1] = controlOverflow(ptr[1], N);
				ptr[2] = controlOverflow(ptr[2], N);
			}
		






		//creates a window
		cv::namedWindow("image");

		//shows image
		cv::imshow("image",image);
		
		char c=0;
		while(c!=27)  //waits until ESC pressed
		{		
			c = cv::waitKey(0);
		}
	}
	catch(std::exception &ex)
	{
	  cout<<ex.what()<<endl;
	}
}
