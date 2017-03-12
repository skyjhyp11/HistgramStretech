#include "colorhistogram.h"

//ColorHistogram::ColorHistogram()
//{

//}
 cv::MatND ColorHistogram::getHistogram(const cv::Mat &image)
 {
     cv::MatND hist;
     //(计算一张图，通道数量，不使用掩码，返回直方图到hist，3维直方图，项的个数，像素范围)
     cv::calcHist(&image,1,channels,cv::Mat(),hist,3,histSize,ranges);
     return hist;
 }
 cv::MatND ColorHistogram::getHueHistogram (const cv::Mat &image,int minSaturation)
 {
     cv::MatND hist;
     cv::Mat hsv;
     cv::cvtColor(image,hsv,CV_BGR2HSV);
     cv::Mat mask;
     if(minSaturation>0)
     {
         std::vector<cv::Mat> v;
         cv::split(hsv,v);
         cv::threshold(v[1],mask,minSaturation,255,cv::THRESH_BINARY);//v[1] is S channel | saturation
     }
     hranges[0]=0.0;// v channel's value:0~180
     hranges[1]=180.0;
     //channels[0]=0;// h channel | Hue
     cv::calcHist(&hsv,1,channels,mask,hist,1,histSize,ranges);

     return hist;

 }
 //颜色缩减函数 colorReduce(缩减图像,缩减因子)_指针遍历
 //最快的方法—单层循环+位运算+三通道同步处理---
 cv::Mat ColorHistogram::colorReduce(  cv::Mat &img, int div = 64)
 {
         cv::Mat_<cv::Vec3b>::iterator it = img.begin<cv::Vec3b>();//开始位置迭代器
         cv::Mat_<cv::Vec3b>::iterator itend = img.end<cv::Vec3b>();//开始位置迭代器
         for (; it != itend; ++it)
         {
             (*it)[0] = (*it)[0] / div*div + div / 2;//该方法不限于2的幂数
             (*it)[1] = (*it)[1] / div*div + div / 2;
             (*it)[2] = (*it)[2] / div*div + div / 2;

         }

     /*
         int nl = img.rows;//行数
         int nc = img.cols*img.channels();//列*通道
         for (int j = 0; j < nl; j++)
         {
             uchar *data = img.ptr<uchar>(j);
             for (int i = 0; i < nc; i++)
             {
                 //int n;
                 //div = pow(2, n);
                 uchar mask = 0xFF << 4;//11111111左移4位变成11110000
                 data[i] = (data[i] & mask) + div / 2;//取高位
             }
         }

     */

     /*
     int nl = img.rows;//行数
     int nc = img.cols;//列
     if (img.isContinuous())
     {
         //图像若不是连续存储，则对行进行填补
         nc = nc*nl;
         nl = 1;//将图像变成一维数组，减少遍历成单层循环
     }

     int n = static_cast<int>(log(static_cast<double>(div) / log(2.0)));
     //log以2为低，div的对数,强制转换成int类型
     //static_cast依靠类型转换语句中提供的信息来进行转换，
     //而dynamic_cast则会遍历整个类继承体系进行类型检查,因此dynamic_cast在执行效率上比static_cast要差一些

     uchar mask = 0xFF << n;
     for (int j = 0; j < nl; j++)
     {
         uchar *data = img.ptr<uchar>(j);
         for (int i = 0; i < nc; i++)
         {
             //qt中使用 ++运算符和&运算符 无效果？？？
            // *data++ = *data & mask + div / 2;//一次处理三个数值，即一个元素（BGR），提高效率
            // *data++ = *data & mask + div / 2;
            // *data++ = *data & mask + div / 2;

         }

     }
     */

     return img;
 }


