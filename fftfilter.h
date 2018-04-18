#ifndef FFTFILTER_H
#define FFTFILTER_H
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <string>
using namespace cv;
using namespace std;
//计算像素的距离
double pixelDistance(double u, double v);
//计算高斯参数
double gaussianCoeff(double u, double v, double d0);
//获得带通滤波的滤波器
void bandpass_filter(Mat &dft_Filter, int D, int d, int n);
//获得低通/高通滤波的滤波器
void lowhighpass_filter(Mat &dft_Filter, int D, int n, bool highpass);
//旋转频谱图，让低频在图像中间
void change(Mat &mag);
//进行傅里叶变化
Mat ForierTransform(int M, int N,const Mat &img);
//获得高斯高通滤波器
Mat CreateGaussianHighPassFilter(Size size, double cutoffInPixels);
//带通滤波
void bandpass(const Mat &img,Mat &Outputmat, int D, int d, int n);
void showfft(String str,const Mat &img);

#endif // FFTFILTER_H
