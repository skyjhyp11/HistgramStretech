#include "histogram1d.h"
#include <QTextStream>
 cv::MatND Histogram1D::getHistogram(const cv::Mat &image)//获取直方图数据
{
    cv::MatND hist;
    //重载2（src,单张图像，通道数量,不使用掩码，返回到hist,1D直方图，项数，像素范围）
    cv::calcHist(&image,1,channels,cv::Mat(),hist,1,histSize,ranges);
    return hist;
}

 cv::Mat Histogram1D::getHistogramImage(const cv::Mat &image)//画出直方图
 {
     cv::MatND hist=getHistogram(image);//得到直方图数组
     double maxVal=0;
     double minVal=0;
     cv::minMaxLoc(hist,&minVal,&maxVal);//获取最大最小值
     double scaX=2;//缩放倍数rows
     double scaY=1;//cols
     double rows[1],cols[1];
     rows[0]=scaY*histSize[0];
     cols[0]=scaX*histSize[0];

     cv::Mat histImg (rows[0],cols[0],CV_8U,cv::Scalar(255));//设置要显示的直方图//（行,列..)
     //int hpt=static_cast<int>(0.9*histSize[0]);
     for(int h=0;h<histSize[0];h++)
     {
         float binVal=hist.at<float>(h);
         int intensity=static_cast<int>(binVal*rows[0]/maxVal);
         cv::line(histImg,cv::Point(scaX*h,rows[0]),cv::Point(scaX*h,rows[0]-intensity),cv::Scalar(0));
     }
     return histImg;
 }

 cv::Mat Histogram1D::applyLookUP(const cv::Mat &image,const cv::Mat &lookup)
  {
      cv::Mat result;
      cv::LUT(image,lookup,result);//(src,查找换算表，result)
      return result;
  }

 cv::Mat Histogram1D::stretch(const cv::Mat &image,int minValue=0)
 {
     //QTextStream cin( stdin,  QIODevice::ReadOnly);
     QTextStream cout( stdout,  QIODevice::WriteOnly);
     //QTextStream cerr(stderr,  QIODevice::WriteOnly);

     cv::MatND hist=getHistogram(image);
     int imin=0;
     for(;imin<histSize[0];imin++)
     {
         cout<<imin<<"="<<hist.at<float>(imin)<<endl;

         if(hist.at<float>(imin)>minValue)
         {
             //minValue 像素的最小个数如100，此处从灰度为imin=0的像素开始检索
             //得到像素个数大于100的第一个灰度值索引：imin
             break;
         }
     }

     int imax=histSize[0]-1;
     for(;imax>=0;imax--)
     {
         cout<<imax<<"="<<hist.at<float>(imax)<<endl;
         if (hist.at<float>(imax)>minValue)
         {
             //minValue 像素的最小个数如100，此处从灰度为imin=255的像素开始检索
             //得到像素个数大于100的第一个灰度值索引：imax
             break;
         }

     }
     //创建查找换算表
     int dim(256);//初始换dim=256;
     cv::Mat lookup(1,&dim,CV_8U);//(1维dimension，256条目entries,uchar)
     for(int i=0;i<256;i++)
     {
         if(i<imin)      //两头灰度值对应数量变成0,中间灰度值线性映射
             lookup.at<uchar>(i)=0;

         else if(i>imax)
             lookup.at<uchar>(i)=0;

         else
             lookup.at<uchar>(i)=static_cast<uchar>(255.0*(i-imin)/(imax-imin)+0.5);
     }
     cv::Mat result;
     result=applyLookUP(image,lookup);
     return result;


















 }
