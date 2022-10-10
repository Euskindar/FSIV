/***********************************
 * Autor: Rafael Muñoz Salinas
 * Universidad de Córdoba (Spain)
 * Master en Sistemas Inteligentes
 * Asignatura: Realidad Virtual y Aumentada
 *
 * Info:
 * Shows how to randomly access to the elements in an image and writes to file
 *
 *
 * ******************************************/

#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>
using namespace std;
int main(int argc,char **argv){
	try{
		//Creates an image of size 320x240 3 channels (RGB)
		//cv::Mat image(240,320,CV_8UC3);

		//Modificacion -> Nueva imagen mas grande de 640x480
		cv::Mat image(480,640,CV_8UC3);

		//move through the image  setting values
		for(int y=0; y<image.rows; y++)
		{
			uchar *ptr=image.ptr<uchar>(y);//pointer to the y-th image row
			
			for(int x=0;x<image.cols;x++)
			{
				ptr[0]=y%256;
				ptr[1]=255%256;
				ptr[2]=(255-y)%256;
				ptr+=3;//moves the pointer 3 elements
			}
		}

		//saves to file
		cv::imwrite("out.jpg",image);

	//cv::Mat image=cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
	if(image.rows==0) {cerr<<"Error reading image"<<endl;return 0;}

	//creates a window
	cv::namedWindow("myimage");

	//displays the image in the window
	cv::imshow("myimage",image);

	//wait for a key to be pressed
	cv::waitKey(0);


	}
	catch(std::exception &ex)
	{
	  cout<<ex.what()<<endl;
	}
}
