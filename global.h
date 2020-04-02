#ifndef GLOBAL_H
#define GLOBAL_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QImage>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>

#if $CV_VERSION_MAJOR > 2
#include <opencv2/imgproc/types_c.h>
#include <opencv2/videoio/videoio_c.h>
#endif

using namespace std;
using namespace cv;

#include <QDebug>

struct CalibInfo
{
    Size size;
    Mat M0, M1, D0, D1, R, T, R1, R2, P1, P2, Q, L;
    Rect validRoi[3];
    Mat rmap[2][2];
    double f;
};

#define SerialPortName  "/dev/ttyUSB0"

void msleep(unsigned int msec);
QImage mat2qimage(const cv::Mat &mat);
cv::Mat qimage2mat(const QImage &qimage);

#endif // GLOBAL_H
