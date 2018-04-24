#include "cvcamera_g.h"
//dll接口 以c形式创建对象，返回对象（唯一）

//全局静态变量，标志数据类是否被实例化，防止重复操作
static bool bbuilded=false;
static bool threaded=false;
void creatcvcam()
{
    if(!bbuilded){
        cvcam=new cvcamera();
        //return zvdata;
        cout<<"creat"<<endl;
        bbuilded=true;
    }
}

cvcamera *destroycvcam()
{
    if(bbuilded){
        cvcam->release();
        cvcam=NULL;
        cout<<"destroy"<<endl;
        bbuilded=false;
    }
    return cvcam;
}

cvcamera *getcvcam()
{
    if(bbuilded){
        return cvcam;
    }else{
        return NULL;
    }
}
void showcamDialog(){
    CamsetDialog *setdia=new CamsetDialog();
    setdia->show();
}



controlthread* creatimgthread()
{
        controlthread* conthread=new controlthread();
        //return zvdata;
        cout<<"creat thread class"<<endl;
        return conthread;
}

