#include "rule.h"




rule::rule()
{
    //cout<<" "<<endl;
}

rule::~rule()
{
    delete GrayhisMat;
    delete GrayHistogram;
    delete GradhisMat;
    delete GradientHis;
    GrayHistogram=NULL;
    GrayhisMat=NULL;
    GradientHis=NULL;
    GradhisMat=NULL;
}
void intchange(int *a,int *b){
    int m=*a;
    *a=*b;
    *b=m;
}
rule::rule(Point p1, Point p2, const Mat &img,int width)
{
    caledealmat(p1,p2,img,width);
    grayhislength=dealmat.cols;
    gradhislength=dealmat.cols-1;
    GrayHistogram=new int[grayhislength];
    GrayhisMat=new Mat(256,grayhislength,0);
    GradientHis=new int[gradhislength];
    GradhisMat=new Mat(256,gradhislength,0);
    GrayhisMat->setTo(255);
    GradhisMat->setTo(255);
    calgray();
    //cout<<"dis"<<dealmat.cols<<endl;
    //qDebug()<<dealmat.cols;
    //qDebug()<<*(GrayHistogram-4)<<"  "<<dealmat.cols;
    filter(GrayHistogram,dealmat.cols,5);
    calgrad();
    filter(GradientHis,dealmat.cols-1,2);
    calgradhis();
    calgrayhis();
    calminmax(3,-3);
}

void rule::caledealmat(Point p1, Point p2, const Mat &img,int width)
{
    m_pointStart=p1;
    m_PointEnd=p2;
    m_width=width;
    Point rotatepoint;
    rotatepoint=p1;
    int x1=m_pointStart.x;
    int y1=m_pointStart.y;
    int x2=m_PointEnd.x;
    int y2=m_PointEnd.y;
    if(m_pointStart.x>m_PointEnd.x){
        binver=true;
        rotatepoint=p2;
        intchange(&x1,&x2);
        intchange(&y1,&y2);
    }


    angle=atan2(y1-y2,x1-x2)*180/PI;
    //angle=atan(dtan)*180/PI;
    //cout<<angle<<endl;
    Mat rotatedmat;
    int distance=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    //cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
    imrotate(img,rotatedmat,angle+180,rotatepoint);
    //imshow("ro",rotatedmat);
    //dealmat=rotatedmat;
    dealmat=rotatedmat(Rect(Point(x1,y1-width/2),Point(x1+distance,y1+width/2)));
    if(binver){
        flip(dealmat, dealmat,1);
    }
}

void rule::calgrayhis()
{
    int i,j;
    for(i=0;i<dealmat.cols;i++){
        if(i>0){
            line(*GrayhisMat, Point(i-1,GrayHistogram[i-1]), Point(i,GrayHistogram[i]), 0, 1.5, 1);
        }
    }
}

void rule::calgray()
{
    int i,j;
    int last;
    Vec3b p;
    p[0]=0;
    for(i=0;i<dealmat.cols;i++){
        int count=0;
        for(j=0;j<dealmat.rows;j++){
            count+=dealmat.at<Vec3b>(j, i)[0];
        }
        int res=count/dealmat.rows;
        GrayHistogram[i]=res;
        last=res;
    }
}

void rule::calhis()
{
    int i,j;
    int last;
    Vec3b p;
    p[0]=0;
    for(i=0;i<dealmat.cols;i++){
        int count=0;
        for(j=0;j<dealmat.rows;j++){
            count+=dealmat.at<Vec3b>(j, i)[0];
        }
        int res=count/dealmat.rows;
        //cout<<res<<endl;
        GrayHistogram[i]=res;
        if(i>0){
            GradientHis[i-1]=res-last;
        }

        last=res;
    }
}

void rule::calgrad()
{
    int i;
    for(i=0;i<dealmat.cols-1;i++){
            GradientHis[i]=GrayHistogram[i+1]-GrayHistogram[i];

    }
}

Point rule::calpoint(int x,int length)
{
    int addx=(m_PointEnd.x-m_pointStart.x)*x/length;
    int addy=(m_PointEnd.y-m_pointStart.y)*x/length;
    return Point(m_pointStart.x+addx,m_pointStart.y+addy);
}

void rule::calgradhis()
{
    int i,j;
    for(i=0;i<dealmat.cols-1;i++){
        if(i>0){
            line(*GradhisMat, Point(i-1,GradientHis[i-1]+125), Point(i,GradientHis[i]+125), 0, 1.5, 1);
        }
    }
    line(*GradhisMat, Point(0,125), Point(dealmat.cols,125), 0, 1, 1);
}

void rule::imrotate(const Mat &img, Mat &newIm, double angle, Point2f pt)
{
    Mat r = getRotationMatrix2D(pt,angle,1.0);
    warpAffine(img,newIm,r,Size(img.cols,img.rows));
}

Point rule::pointResult() const
{
    return m_pointResult;
}

void rule::setPointResult(const Point &pointResult)
{
    m_pointResult = pointResult;
}

Point rule::PointEnd() const
{
    return m_PointEnd;
}

void rule::setPointEnd(const Point &PointEnd)
{
    m_PointEnd = PointEnd;
}

Point rule::pointStart() const
{
    return m_pointStart;
}

void rule::setPointStart(const Point &pointStart)
{
    m_pointStart = pointStart;
}

void rule::filter(int *func,int sizefunc,int num)
{
    int *buff=new int[sizefunc];
    //int sizefunc=sizeof(func)/sizeof(int);
    //cout<<"das"<<sizefunc<<endl;
    int i;

    for(i=0;i<sizefunc-num+1;i++){
        int j;
        int all=0;
        for(j = 0; j < num; j++) {
            all+=func[i+j];
        }

        buff[i]=all/num;
    }
    for(i=0;i<sizefunc-num+1;i++){
        func[i]=buff[i];
    }
    delete buff;
    buff=NULL;
}


int *rule::getGradientHis() const
{
    return GradientHis;
}

void rule::setGradientHis(int *value)
{
    GradientHis = value;
}


int *rule::getGrayHistogram() const
{
    return GrayHistogram;
}

void rule::setGrayHistogram(int *value)
{
    GrayHistogram = value;
}

void rule::showHistogram()
{
    imshow("grad",*GradhisMat);
    imshow("gray",*GrayhisMat);
}


Mat rule::getDealmat() const
{
    return dealmat;
}

void rule::setDealmat(const Mat &value)
{
    dealmat = value;
}

double rule::getAngle() const
{
    return angle;
}

void rule::setAngle(double value)
{
    angle = value;
}

Mat *rule::getGrayhisMat() const
{
    return GrayhisMat;
}

void rule::setGrayhisMat(Mat *value)
{
    GrayhisMat = value;
}

Mat *rule::getGradhisMat() const
{
    return GradhisMat;
}

void rule::setGradhisMat(Mat *value)
{
    GradhisMat = value;
}

void rule::calminmax(int zero_up,int zero_down)
{
    int i;
    for(i=0;i<dealmat.cols-1;i++){
        if(GradientHis[i]>max){
            maxindex=i;
            max=GradientHis[i];
        }
        if(GradientHis[i]<min){
            minindex=i;
            min=GradientHis[i];
        }
    }

    int j=0;
    bool bleft=false,bright=false;
    while (!(bleft&&bright)) {
        j++;
        if(!bleft){
            bleft=GradientHis[minindex-j]>zero_down;
            minxa=minindex-j+1;
        }
        if(!bright){
           bright=GradientHis[minindex+j]>zero_down;
           minxb=minindex+j-1;
        }
    }
    j=0;
    bleft=false,bright=false;
    while (!(bleft&&bright)) {
        j++;
        if(!bleft){
            bleft=GradientHis[maxindex-j]<zero_up;
            maxxc=maxindex-j+1;
        }
        if(!bright){
           bright=GradientHis[maxindex+j]<zero_up;;
           maxxd=maxindex+j-1;
        }
    }

}

int rule::getMinxa() const
{
    return minxa;
}

void rule::setMinxa(int value)
{
    minxa = value;
}


int rule::getMinxb() const
{
    return minxb;
}

void rule::setMinxb(int value)
{
    minxb = value;
}

int rule::getMaxxc() const
{
    return maxxc;
}

void rule::setMaxxc(int value)
{
    maxxc = value;
}

int rule::getMaxxd() const
{
    return maxxd;
}

void rule::setMaxxd(int value)
{
    maxxd = value;
}

int rule::getGrayhislength() const
{
    return grayhislength;
}

void rule::setGrayhislength(int value)
{
    grayhislength = value;
}

int rule::getGradhislength() const
{
    return gradhislength;
}

void rule::setGradhislength(int value)
{
    gradhislength = value;
}

int rule::getMaxindex() const
{
    return maxindex;
}

void rule::setMaxindex(int value)
{
    maxindex = value;
}

int rule::getMinindex() const
{
    return minindex;
}

void rule::setMinindex(int value)
{
    minindex = value;
}

int rule::getMax() const
{
    return max;
}

void rule::setMax(int value)
{
    max = value;
}

int rule::getMin() const
{
    return min;
}

void rule::setMin(int value)
{
    min = value;
}
void circleLeastFit(const std::vector<cv::Point> points, cv::Point &center, double &radius)
{
    radius = 0.0f;
    double sum_x = 0.0f, sum_y = 0.0f;
    double sum_x2 = 0.0f, sum_y2 = 0.0f;
    double sum_x3 = 0.0f, sum_y3 = 0.0f;
    double sum_xy = 0.0f, sum_x1y2 = 0.0f, sum_x2y1 = 0.0f;
    int N = points.size();
    for (int i = 0; i < N; i++)
    {
        double x = points[i].x;
        double y = points[i].y;
        double x2 = x * x;
        double y2 = y * y;
        sum_x += x;
        sum_y += y;
        sum_x2 += x2;
        sum_y2 += y2;
        sum_x3 += x2 * x;
        sum_y3 += y2 * y;
        sum_xy += x * y;
        sum_x1y2 += x * y2;
        sum_x2y1 += x2 * y;
    }
    double C, D, E, G, H;
    double a, b, c;
    C = N * sum_x2 - sum_x * sum_x;
    D = N * sum_xy - sum_x * sum_y;
    E = N * sum_x3 + N * sum_x1y2 - (sum_x2 + sum_y2) * sum_x;
    G = N * sum_y2 - sum_y * sum_y;
    H = N * sum_x2y1 + N * sum_y3 - (sum_x2 + sum_y2) * sum_y;
    a = (H * D - E * G) / (C * G - D * D);
    b = (H * C - E * D) / (D * D - G * C);
    c = -(a * sum_x + b * sum_y + sum_x2 + sum_y2) / N;
    center.x = a / (-2);
    center.y = b / (-2);
    radius = sqrt(a * a + b * b - 4 * c) / 2;

}
