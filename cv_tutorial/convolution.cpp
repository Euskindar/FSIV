void fsiv_convolution(const cv::Mat& src, cv::Mat& dst, const cv::Mat& kernel, int padding)
{
    // Check if dst image is prepared or not...
    CV_Assert(!src.empty());
    CV_Assert(src.rows == dst.rows && src.cols == dst.cols);
    CV_Assert(!kernel.empty());

    // Check the padding type == int and odd number
    CV_Assert(typeid(padding).name() != i);
    CV_Assert(padding % 2 == 0);

    // Apply the convolution opperation -> BOX FILTER


    // Select the pixels of the source image
    for (int src_row = 0; src_row < src.rows; src_row++) {
        for (int src_col = 0; src_col < src.cols; src_col++) {
            const uchar *ptr = src.ptr<uchar>(src_row) + 3 * src_col; // access to the pixel
            uchar *ptrO = dst.ptr<uchar>(src_row) + 3 * src_col;    // Output image pixel

            // Select pixels of the kernel
            for (int k = 0; k < kernel.rows; k++) {
                for (int z = 0; z < kernel.cols; z++) {

                    // Primera posicion del kernel = (i - ((int)kernel.rows/2) , j - ((int)kernel.cols/2))

                }
            }

            // Controls overflow
            ptrO[0] = std::min(255, ptr[0]+val);
            ptrO[1] = std::min(255, ptr[1]+val);
            ptrO[2] = std::min(255, ptr[2]+val);
        }
    }


}