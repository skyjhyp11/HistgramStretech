#include "imagecomparator.h"

//ImageComparator::ImageComparator()
//{

//}
void ImageComparator::setReferenceImage( cv::Mat &image)
{
    reference=hist.colorReduce(image,div);
    refH=hist.getHistogram(reference);//获取相关查询图像的直方图refH
}

double ImageComparator::compare ( cv::Mat &image)
{
    input =hist.colorReduce(image,div);
    inputH=hist.getHistogram(input);
    return cv::compareHist(refH,inputH,CV_COMP_INTERSECT);
}
