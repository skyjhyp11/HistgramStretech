#ifndef COLORHISTOGRAM_H
#define COLORHISTOGRAM_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class ColorHistogram
{
public:
    ColorHistogram()
    {
        histSize[0]= histSize[1]= histSize[2]=256;
        hranges[0]=0.0;
        hranges[1]=255.0;
        ranges[0]=hranges;//所有通道具有相同的范围
        ranges[1]=hranges;
        ranges[2]=hranges;
        channels[0]=0;//默认考察0通道
        channels[1]=1;
        channels[2]=2;
    }
    cv::MatND getHistogram(const cv::Mat &image);
    cv::Mat colorReduce( cv::Mat &image,int div);
    cv::MatND getHueHistogram (const cv::Mat &image,int minSaturation=0);// hue histogram


    int channels[3];//3通道
private:
    int histSize[3];//直方图项的数量
    float hranges[2];//像素的最小及最大值
    const float *ranges[3];


};

#endif // COLORHISTOGRAM_H
