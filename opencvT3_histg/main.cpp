#include <QCoreApplication>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>  // for use meanshift

#include <stdio.h>
#include <QTextStream>

#include "colorhistogram.h"
#include "contentfinder.h"
#include "histogram1d.h"
#include "imagecomparator.h"

int main(int argc, char *argv[])
{
    QTextStream cin( stdin,  QIODevice::ReadOnly);
    QTextStream cout( stdout,  QIODevice::WriteOnly);
    QTextStream cerr(stderr,  QIODevice::WriteOnly);

    QCoreApplication a(argc, argv);

    cv::Mat image = cv::imread("../TestPic/baboon1.jpg",1);   // cow sky

    // Histogram1D h;
    //cv::MatND histo = h.getHistogram(image);

    //for(int i=0;i<256;i++) cout << "Value" << i << "=" << histo.at<float>(i) << endl;

    //cv::namedWindow("src");
    //cv::imshow("src",image);

    //1.测试直方图
    //cv::namedWindow("histImg");
    //cv::imshow("histImg",h.getHistogramImage(image));

    //2.测试拉伸直方图图像
    //cv::Mat streteched=h.stretch(image,100);
    //cv::namedWindow("strehistImg");
    //cv::imshow("strehistImg",streteched);//
    //cv::namedWindow("strehistHist");
    //cv::imshow("strehistHist",h.getHistogramImage(streteched));//

    //3.测试直方图均衡化
    //cv::namedWindow("equalizeImg");
    //cv::imshow("equalizeImg",h.equalizeHist(image));// cv::equalizeHist Image
    //cv::namedWindow("equalizeHist");
    //cv::imshow("equalizeHist",h.getHistogramImage(h.equalizeHist(image)));//

    //4.测试：反投影直方图以检测特定的图像内容
    //步骤：
    //1）.源图像减色，减少灰度数目-色块化
    //2）.设定感兴趣区域ROI-确定搜索目标
    //3）.获取ROI的直方图，并归一化
    //4）.反投影ROI归一化的直方图到源图像，阈值化输出二值图像
/*
    //ColorHistogram hc;
    //image=hc.colorReduce(image,32);

    //cv::namedWindow("colorReduce");
    //cv::imshow("colorReduce",image);//减色图像

    //cv::Mat imgROI=image(cv::Rect(45,5,20,20));//设置感兴趣区域
    //cv::MatND hist=hc.getHistogram(imgROI);

    //ContentFinder finder;
    //finder.setThreshold(0.05f);
    //finder.setHistogram(hist);//归一化直方图，得到特定像素属于某个区域的概率图

    //cv::Mat result=finder.find(image,0.0,255.0,hc.channels,3);//反投影，阈值化

    //cv::namedWindow("result");
    //cv::imshow("result",result);

*/
    //5.均值漂移法 查找物体-Mean shift to find target
/*
    cv::Rect rect(110,260,35,40);// target area
    cv::Mat imageROI=image(rect);// get baboon's face
    cv::rectangle(image,rect,cv::Scalar(0,255,0));
    cv::namedWindow("src");
    cv::imshow("src",image);

    int minSat = 65;
    ColorHistogram hcc;
    cv::MatND colorhist=hcc.getHueHistogram(imageROI,minSat);

    cv::Mat image1=cv::imread("../TestPic/baboon3.jpg",1);
    cv::Mat hsv;
    std::vector<cv::Mat> v;
    cv::cvtColor(image1,hsv,CV_BGR2HSV); //change color space
    cv::split(hsv,v);
    cv::threshold(v[1],v[1],minSat,255,cv::THRESH_BINARY); // threshold to the binary image(only two-value)

    //cv::namedWindow("hsv");
    //cv::imshow("hsv",v[1]);  //OK

    ContentFinder finder;
    finder.setThreshold(0.05f);
    finder.setHistogram(colorhist);//归一化直方图，得到特定像素属于某个区域的概率图
    cv::Mat result=finder.find(hsv,0.0f,180.0f,hcc.channels,1);//反投影，阈值化 finder.channels

    //去除低相似度概率的像素们
    cv::bitwise_and(result,v[1],result); //reduce low-saturation pixel

    cv::rectangle(image1,rect,cv::Scalar(0,125,0)); //draw rect in src

    //cv::namedWindow("imageRec");
    // cv::imshow("imageRec",image1);//ok

    // (criteria,maximum number of iterations,accuracy)
    cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER,10,0.01);
    cv::meanShift(result,rect,criteria);//得到相似度最高的区域rect

    cv::rectangle(image1,rect,cv::Scalar(0,0,255));//draw rect-finding in src
    cv::namedWindow("image1res");
    cv::imshow("image1res",image1);
*/
   //6.比较直方图检索相似图像 cv::compareHist to find similar pic
    cv::Mat imagesrc= cv::imread("../TestPic/baboon1.jpg",1);   // cow sky
    cv::Mat imagedst1= cv::imread("../TestPic/baboon4.jpg",1);
    cv::Mat imagedst2= cv::imread("../TestPic/cow.jpg",1);
    cv::Mat imagedst3= cv::imread("../TestPic/sky.jpg",1);       // cow sky

    cv::namedWindow("imagesrc");
    cv::imshow("imagesrc",imagesrc);
    cv::namedWindow("imagedst1");
    cv::imshow("imagedst1",imagedst1);
    cv::namedWindow("imagedst2");
    cv::imshow("imagedst2",imagedst2);
    cv::namedWindow("imagedst3");
    cv::imshow("imagedst3",imagedst3);

    ImageComparator c;
    c.setColorReduction(50);
    c.setReferenceImage(imagesrc);
    double res1_double=c.compare(imagedst1);
    double res2_double=c.compare(imagedst2);
    double res3_double=c.compare(imagedst3);

    cout << "res1" << "=" <<res1_double << "\n"
         << "res2" << "=" <<res2_double << "\n"
         << "res3" << "=" <<res3_double  << endl;


    //cv::waitKey(0);
    //system("pause");

    return a.exec();
}

