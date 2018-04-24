#include "filtertool_g.h"

toolsbase *creatfiltertool(int node)
{

    toolsbase* tool=new Filtertool(node);
    //Filtertool *erw=new Filtertool();
    cout<<"creat filter"<<endl;
    return tool;
}

void destroytool()
{

}
