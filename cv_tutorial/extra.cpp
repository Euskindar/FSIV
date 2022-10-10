/*  Create a program that shows a colour image (given by the command line) and, while displayed, if the user presses the
 key 'i', all values of the image are multiplied by 1.2. But when user presses the key 'd', all values of the image are 
 divided by 1.2. REMEMBER: the matrix only stores unsigned char values, so the allowed range is [0,255]. NOTE: it is 
 expected that the student uses the pointer logic to loop over the pixels
 */
#include <opencv2/core/core.hpp>	   //core routines
#include <opencv2/highgui/highgui.hpp> //imread,imshow,namedWindow,waitKey
#include <iostream>

using namespace std;


int brightModif(int val) {

	if (val > 255)
	{
		val = 255;
	}
	if (val < 0)
	{
		val = 0;
	}
	// cout << val << endl;
	return (int)val;
}


int main(int argc, char **argv)
{
	try
	{
		if (argc != 2)
		{
			cerr << "Usage:image" << endl;
			return 0;
		}

		// loads the image from file
		// Modificacion -> Lee la imagen en escala de grises
		cv::Mat image = cv::imread(argv[1]);
		if (image.rows == 0)
		{
			cerr << "Error reading image" << endl;
			return 0;
		}

		// creates a window
		cv::namedWindow("My Image");

		// shows image
		cv::imshow("My Image", image);

		char c = 0;

		while (c != 27) // waits until ESC pressed
		{
			if (c == 'i')
			{
				cout << "INCREMENTO x1.2" << endl;

				for (int i = 0; i < image.rows; i++) {
					for (int j = 0; j < image.cols; j++) {
						uchar *ptr = image.ptr<uchar>(i) + 3 * j; // access to the pixel

						ptr[0] = brightModif(ptr[0] * 1.2);
						ptr[1] = brightModif(ptr[1] * 1.2);
						ptr[2] = brightModif(ptr[2] * 1.2);
					}
				}
			}

			if (c == 'd')
			{
				cout << "DECREMENTO x1.2" << endl;

				for (int i = 0; i < image.rows; i++)
				{
					for (int j = 0; j < image.cols; j++)
					{
						uchar *ptr = image.ptr<uchar>(i) + 3 * j; // access to the pixel

						ptr[0] = brightModif(ptr[0] / 1.2);
						ptr[1] = brightModif(ptr[1] / 1.2);
						ptr[2] = brightModif(ptr[2] / 1.2);
					}
				}
			}

			// Refresh
			cv::imshow("My Image", image);

			c = cv::waitKey(0);
		}
	}
	catch (std::exception &ex)
	{
		cout << ex.what() << endl;
	}
}
