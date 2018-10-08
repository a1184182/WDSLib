#include "Flag.h"

Flag::Flag()
{     
    //printf("Flag Created\n");
    flag["SolverFlag"]=1;
    flag["NetFlag"]=0;
    flag["FCPAFlag"]=0;
    flag["SPAFlag"]=0;
    flag["ScalingFlag"]=0;
    flag["BasicFlag"]=0;
    flag["NetInfoFlag"]=0;
    flag["ConvergenceFlag"]=0;
    flag["StatFlag"]=0;
    flag["DiaryFlag"]=0;
    flag["Reflag"]=0;
    flag["NodalResultflag"]=0;
    flag["LinkResultflag"]=0;
    flag["GFflag"]=0;
    flag["ItersGF"]=0;
    flag["QitersFlag"]=0;
    flag["HitersFlag"]=0;
    flag["ItersNorm"]=0;
    flag["ResidueFlag"]=0;
    flag["IterOutFlag"]=0;
    flag["timeFlag"]=0;
}


void Flag::setFlag(string name,int value)
{
//-------------------------------------------------------------------------
//  Date:    10/09/2014
//  Author:  Mengning Qiu
//  Input:   
//  Output:  
//  Purpose: 
//  calls:   
//  called from: 
//-------------------------------------------------------------------------
     map<string,int>::iterator it;
     flag[name]=value;
}


int Flag::getFlagvalue(string name)
{
    return flag[name];
}

Flag::~Flag()
{    

}

void Flag::dispFlags()
{
//-------------------------------------------------------------------------
//                               
//
//  Date:    10/09/2014
//  Author:  Mengning Qiu
//  Input:   
//  Output:  
//  Purpose: 
//  calls:   
//  called from: 
//-------------------------------------------------------------------------
    for (map<string,int>::const_iterator it=flag.begin();it!=flag.end();++it){
        cout<<"Flag["<<it->first<<"] = "<<it->second<<endl;
        printf("Flag[%s]=%d\n",(it->first).c_str(),it->second);
    }


}