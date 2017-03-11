#ifndef HISTOGRAM1D_H
#define HISTOGRAM1D_H


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>




class Histogram1D
{
public:
    Histogram1D()
    {
        histSize[0]=256;
        hranges[0]=0;
        hranges[1]=255;
        ranges[0]=hranges;
        channels[0]=0;//默认考察0通道
    }
    cv::MatND getHistogram(const cv::Mat &image);//获取直方图数据
    cv::Mat getHistogramImage(const cv::Mat &image);//绘制直方图
    cv::Mat applyLookUP(const cv::Mat &image,const cv::Mat &lookup);//使用查找表方式对图像进行换算
    cv::Mat stretch(const cv::Mat &image,int minValue);//中间强度线性映射//拉伸直方图，提高对比度

private:
    int histSize[1];//直方图项的数量
    float hranges[2];//像素的最小及最大值
    const float *ranges[1];
    int channels[1];//仅使用一个通道





};

#endif // HISTOGRAM1D_H
