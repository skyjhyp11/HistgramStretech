#include <QCoreApplication>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <stdio.h>
#include <QTextStream>

#include "histogram1d.h"

int main(int argc, char *argv[])
{
    QTextStream cin( stdin,  QIODevice::ReadOnly);
    QTextStream cout( stdout,  QIODevice::WriteOnly);
    QTextStream cerr(stderr,  QIODevice::WriteOnly);

    QCoreApplication a(argc, argv);

    cv::Mat image = cv::imread("../TestPic/cow.jpg",0);
    Histogram1D h;
    cv::MatND histo = h.getHistogram(image);

    //for(int i=0;i<256;i++) cout << "Value" << i << "=" << histo.at<float>(i) << endl;



    cv::namedWindow("src");
    cv::imshow("src",image);

    cv::namedWindow("histImg");
    cv::imshow("histImg",h.getHistogramImage(image));

    cv::Mat streteched=h.stretch(image,100);
    cv::namedWindow("strehistImg");
    cv::imshow("strehistImg",h.getHistogramImage(streteched));




    return a.exec();
}

