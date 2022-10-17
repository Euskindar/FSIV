#include "task3.hpp"

int main(int argc,char **argv)
{
    cv::Mat image,filter,result;

    float g = 0;
    int f = 0;
    CmdLineParser cml(argc,argv);

    //check if a command is present
    try
    {
        if(argc < 3)
        {
            cerr<<"Usage: <input img> <output img>\n Options:\n \t[-f filter type: [0-1]] \n \t[-g gain > 0.0]"<<endl;
            return 0;
        }

        image = cv::imread(argv[1]);
        image.convertTo(image,CV_32FC1,1./255.);
        image.copyTo(result);

        cv::imshow("Original",image);


        if( image.rows==0)
        {
            cerr<<"Error reading image"<<endl;
            return 0;
        }

        if(cml["-f"])
        {
            if( (stoi(cml("-f")) >= 0) && (stoi(cml("-f")) <= 1) )
            {
                f = std::stoi( cml("-f"));//convert to int
            }
            else
            {
                f = 0;
            }
        }

        if(cml["-g"])
        {
            if (stof(cml("-g")) >= 0)
            {
                g = std::stof(cml("-g"));//convert to float
            }
            else
            {
                g = 1;
            }
        }

        //do things
        std::cerr<<"f == "<<f<<"\n";
        std::cerr<<"g == "<<g<<"\n";
        filter = create_sharp_filter(f,g);

        std::cerr<<"Type of 'Image' = "<<image.type()<<"\n";
        std::cerr<<"Type of 'Filter' = "<<filter.type()<<"\n";

        //filter2D(image,result,-1,filter);
        //make convolution
        convolve(image,filter,result);

        char c=0;
        while(c!=27)  //waits until ESC pressed
            c=cv::waitKey(0);
    }
    catch(const std::exception& ex)
    {
        std::cerr << ex.what() << '\n';
    }
}