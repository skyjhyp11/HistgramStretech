#include "contentfinder.h"

//ContentFinder::ContentFinder()
//{
//}
void ContentFinder::setHistogram(const cv::MatND h)
{
    histogram=h;//设定要处理的直方图
    cv::normalize(h,histogram,1.0);//归一化直方图，得出了一个给定强度的像素属于这个区域的概率//概率图

}

cv::Mat ContentFinder::find(const cv::Mat &image,float minValue,float maxValue,int *channels,int dim)
{
    cv::Mat result;
    hranges[0]=minValue;
    hranges[1]=maxValue;
    for(int i=0;i<dim;i++)//维度
    {
        this->channels[i]=channels[i];
    }
    //反投影直方图(src,imgnum,通道列表，处理的直方图，反投影的结果histogram > result，值域，缩放因子)
    cv::calcBackProject(&image,1,channels,histogram,result,ranges,255.0);

    if(threshold>0.0)//阈值化图像
    {
         cv::threshold(result,result,255*threshold,255,cv::THRESH_BINARY);
    }
    return result;

}

