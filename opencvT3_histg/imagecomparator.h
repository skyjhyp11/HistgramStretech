#ifndef IMAGECOMPARATOR_H
#define IMAGECOMPARATOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "colorhistogram.h"
class ImageComparator
{
public:
    ImageComparator():div(32)
    {

    }
    void setColorReduction (int factor)
    {
        div=factor;
    }
    int getcolorReduction()
    {
        return div;
    }
    void setReferenceImage( cv::Mat &image);
    double compare ( cv::Mat &image);

private:
    cv::Mat reference;
    cv::Mat input;
    cv::MatND refH;
    cv::MatND inputH;
    ColorHistogram hist;
    int div;
};

#endif // IMAGECOMPARATOR_H
