/**
*@projectName
*@documentname  cvgloble.h
*@author        zzJun
*@date          20180422
*@brief         include the opencv function we often use
**/
#ifndef CVGLOBLE_H
#define CVGLOBLE_H
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <QImage>
#include <string>
#include <iostream>

using namespace std;
using namespace cv;
void scalemat(Mat &mat,float scale);
void getimgroi(Mat& mat,const float scale);
QImage Mat2QImage(Mat image1);
void imrotate(Mat& img, Mat& newIm, double angle,Point2f pt,Size size);
double Entropy(Mat img);
double getfuza(Mat &img);
void imshowMany(const std::string& _winName, const vector<Mat>& _imgs);

#endif // CVGLOBLE_H
