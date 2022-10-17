#include "task3.hpp"

///////////////////////////////////////////////////////////////////////////

cv::Mat create_sharp_filter(int &f, float &g)
{
    //creamos el filtro 3x3 rellenado con -1
    cv::Mat filter(3,3,CV_32FC1,-1);

    if(f == 1)
    {
        std::cerr<<"Entro if\n";
        //devolver filtro 9 puntos
        for(int x = 0; x < filter.rows; x++)
        {
            float *ptr = filter.ptr<float>(x);
        
            for(int y = 0; y < filter.cols; y++)
            {
                if( (x == 1) && (y == 1) )
                {
                    // Coloca el valor de la ganancia +8 en el centro del 3x3
                    ptr[y] = g+8;
                }
            }
        }
    }

    //devolver filtro 9 puntos
    else
    {
        for(int x = 0; x < filter.rows; x++)
        {
            float *ptr = filter.ptr<float>(x);
        
            for(int y = 0; y < filter.cols; y++)
            {
                if( (x == 1) && (y == 1) )
                {
                    // Coloca el valor de ganancia +4 en el centro
                    ptr[y] = g+4;
                }
                if( ((x == 0) && (y == 0)) || ((x == 0) && (y == 2)) || ((x == 2) && (y == 0)) || ((x == 2) && (y == 2)) )
                {
                    // Coloca 0 en el resto de pixeles
                    ptr[y] = 0;
                }
            }
        }
    }

    return filter;
}

///////////////////////////////////////////////////////////////////////////

void convolve(const cv::Mat &image, cv::Mat &filter, cv::Mat result)
{
    #ifndef NDEBUG
        assert( filter.type() == 5 );
        assert ( image.type() == 5 );
    #endif

    image.copyTo(result);
    
    //making the convolution
    for(int x = 1; x < result.rows - 1; x++)
    {
        float *ptr = result.ptr<float>(x);
        
        for(int y = 1; y < result.cols - 1; y++)
        {
            cv::Mat subImage = get_sub_image(result,x,y);
            ptr[y] = apply_filter(filter,subImage);
        }
    }

    //filling borders with zeros
    for(int x = 0; x < result.rows+1; x++)
    {
        float *ptr = result.ptr<float>(x);
        
        for(int y = 0; y < result.cols+1; y++)
        {
            if( (x == 0) || (x == result.rows) )
            {
                ptr[y] = 0;
            }
            if( (y == 0) || (y == result.cols) )
            {
                ptr[y] = 0;
            }
        }
    }

    cv::imshow("Convolved",result);
}

///////////////////////////////////////////////////////////////////////////

float apply_filter(cv::Mat &filter, cv::Mat &subImage)
{
    #ifndef NDEBUG
        assert( (filter.rows * filter.cols) == (subImage.rows * subImage.cols) );
    #endif

    float result = 0;

    for(int x = 0; x < filter.rows; x++)
    {
        float *ptr1 = filter.ptr<float>(x);
        float *ptr2 = subImage.ptr<float>(x);
        
        for(int y = 0; y < filter.cols; y++)
        {
            result += ptr1[y] * ptr2[y];
        }
    }

    return result / 9;
}

///////////////////////////////////////////////////////////////////////////

//pilla bien las submatrices
cv::Mat get_sub_image(cv::Mat &image, int i, int j)
{
    cv::Mat sub(3,3,CV_32FC1);
 
    for(int x = 0; x < 3; x++)
    {
        float *ptr_image = image.ptr<float>(x+i-1);
        float *ptr_sub_image = sub.ptr<float>(x);
        
        for(int y = 0; y < 3; y++)
        {
            ptr_sub_image[y] = ptr_image[y+j-1];
        }
    }

    return sub;
}

///////////////////////////////////////////////////////////////////////////