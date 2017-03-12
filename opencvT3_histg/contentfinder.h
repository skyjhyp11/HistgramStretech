#ifndef CONTENTFINDER_H
#define CONTENTFINDER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class ContentFinder
{
public:
    ContentFinder():threshold(-1.0f)
    {
        ranges[0]=hranges;
        ranges[1]=hranges;
        ranges[2]=hranges;

        channels[0]=0;
        channels[1]=1;
        channels[2]=2;
    }
    void setThreshold(float t)
    {
        threshold=t;
    }
    float getThreshold()
    {
        return threshold;
    }

    void setHistogram(const cv::MatND h);
    cv::Mat find(const cv::Mat &image,float minValue,float maxValue,int *channels,int dim);
    int channels[3];
private:
    float hranges[2];
    const float *ranges[3];

    float threshold;
    cv::MatND histogram;
};

#endif // CONTENTFINDER_H
