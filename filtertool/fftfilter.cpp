#include "fftfilter.h"



double pixelDistance(double u, double v)
{
    return sqrt(u*u + v*v);
}

double gaussianCoeff(double u, double v, double d0)
{
    double d = pixelDistance(u, v);
    return 1.0 - exp((-d*d) / (2*d0*d0));
}

void bandpass_filter(cv::Mat &dft_Filter, int D,int d, int n)
{
    dft_Filter = cv::Mat(dft_Filter.rows,dft_Filter.cols,CV_32F,cv::Scalar::all(0));

    cv::Point centre = cv::Point(dft_Filter.rows / 2, dft_Filter.cols / 2);
    double radius;
    for(int i = 0; i < dft_Filter.rows; i++)
    {
        for(int j = 0; j < dft_Filter.cols; j++)
        {
            radius = (double) std::sqrt(std::pow((i - centre.x), 2.0) + std::pow((double) (j - centre.y), 2.0));
            dft_Filter.at<float>(i,j) = (float) ( 1 / (1 + std::pow((double) (radius /  D),   (double) (2 * n))));
        }
    }

    Mat dft_Filter2 = cv::Mat(dft_Filter.rows,dft_Filter.cols,CV_32F,cv::Scalar::all(0));
    for(int i = 0; i < dft_Filter2.rows; i++)
    {
        for(int j = 0; j < dft_Filter2.cols; j++)
        {
            radius = (double) std::sqrt(std::pow((i - centre.x), 2.0) + std::pow((double) (j - centre.y), 2.0));
            dft_Filter2.at<float>(i,j) = (float) ( 1 / (1 + std::pow((double) (radius /  d),   (double) (2 * n))));
        }
    }
    dft_Filter=dft_Filter-dft_Filter2;
    cv::Mat toMerge[] = {dft_Filter, dft_Filter};

    cv::merge(toMerge, 2, dft_Filter);
}
void lowhighpass_filter(cv::Mat &dft_Filter, int D, int n, bool highpass)
{
    dft_Filter = cv::Mat(dft_Filter.rows,dft_Filter.cols,CV_32F,cv::Scalar::all(0));

    cv::Point centre = cv::Point(dft_Filter.rows / 2, dft_Filter.cols / 2);
    double radius;

    // based on the forumla in the IP notes (p. 130 of 2009/10 version)
    for(int i = 0; i < dft_Filter.rows; i++)
    {
        for(int j = 0; j < dft_Filter.cols; j++)
        {
            radius = (double) std::sqrt(std::pow((i - centre.x), 2.0) + std::pow((double) (j - centre.y), 2.0));
            dft_Filter.at<float>(i,j) = (float) ( 1 / (1 + std::pow((double) (radius /  D),   (double) (2 * n))));
        }
    }

    if (highpass)
    {
        dft_Filter = cv::Scalar::all(1) - dft_Filter;
    }
    //imshow("highpass_filter", dft_Filter);
    cv::Mat toMerge[] = {dft_Filter, dft_Filter};
    cv::merge(toMerge, 2, dft_Filter);
}

Mat CreateGaussianHighPassFilter(cv::Size size, double cutoffInPixels)
{
    Mat ghpf(size, CV_32F);

    cv::Point center2((size.height/2), size.width/2);
    //cv::Point center2(0,0);

    for(int u = 0; u < ghpf.rows; u++)
    {
        for(int v = 0; v < ghpf.cols; v++)
        {
            ghpf.at<float>(u, v) = 255-gaussianCoeff(u - center2.x, v - center2.y, cutoffInPixels);
        }
    }
    Mat planes[] = {ghpf,ghpf};
    Mat complexImg;
    merge(planes, 2, complexImg);
    return complexImg;
}

Mat ForierTransform(const Mat &img)
{
   Mat padded;
   int M = getOptimalDFTSize( img.rows );
   int N = getOptimalDFTSize( img.cols );
   copyMakeBorder(img, padded, 0, M - img.rows, 0, N - img.cols, BORDER_CONSTANT, Scalar::all(0));

   Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), 5)};
   Mat complexImg;
   merge(planes, 2, complexImg);
   dft(complexImg, complexImg);

   return complexImg;
}
void change(Mat &mag){

    int cx = mag.cols/2;
    int cy = mag.rows/2;
    Mat q0(mag, Rect(0, 0, cx, cy));
    Mat q1(mag, Rect(cx, 0, cx, cy));
    Mat q2(mag, Rect(0, cy, cx, cy));
    Mat q3(mag, Rect(cx, cy, cx, cy));
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    //变换右上角和左下角象限
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
}
void bandpass(const Mat &img,Mat &inverseTransform, int D, int d, int n)
{

    Mat complexImg=ForierTransform(img);
    Mat ghpf(Size(complexImg.cols, complexImg.rows),5);
    bandpass_filter(ghpf,D,d,n);
    Mat planes[] = { Mat::zeros(ghpf.size(), 5), Mat::zeros(ghpf.size(), 5)};
    split(ghpf, planes);
    change(planes[0]);
    change(planes[1]);
    merge(planes, 2, ghpf);
    mulSpectrums(complexImg,ghpf,inverseTransform,DFT_COMPLEX_OUTPUT);
    dft(inverseTransform, inverseTransform, cv::DFT_INVERSE|cv::DFT_REAL_OUTPUT);
    normalize(inverseTransform, inverseTransform, 0, 1, CV_MINMAX);
}

void showfft(String str,const Mat &img)
{

    Mat planes[] = { Mat::zeros(img.size(), 5), Mat::zeros(img.size(), 5)};
    split(img, planes);
    magnitude(planes[0], planes[1], planes[0]);
    Mat mag = planes[0];
    mag += Scalar::all(1);
    log(mag, mag);
    mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));
    normalize(mag, mag, 1, 0, CV_MINMAX);
    change(mag);
    imshow(str,mag);
}
