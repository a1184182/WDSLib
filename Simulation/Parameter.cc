#include "Parameter.h"

Parameter::Parameter()
{
	parameter["maxIter"]=50.0;
    parameter["initV"]=0.30487804878048780488;
    parameter["StopTol"]=1.0e-10;
    parameter["SerP"]=40.0;
    parameter["MinP"]=20.0;
    parameter["NormTyp"]=1.0;
    parameter["StopTest"]=1.0;
    parameter["Demandfuc"]=1.0;
    parameter["MaxNpIterResult"]=1000.0;
    parameter["MinImproTol"]=1.0e-9;
}


void Parameter::setParameter(string name,double value)
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
     map<string,double>::iterator it;
     it=parameter.find(name);
     if(it!=parameter.end()){
        parameter.erase(it);
        parameter[name]=value;
    }

}

double Parameter::getParametervalue(string name)
{
    return parameter[name];
}


void Parameter::dispParameters()
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
    for (map<string , double>::iterator it=parameter.begin();it!=parameter.end();++it){
        cout<<"parameter["<<it->first<<"] = "<<it->second<<endl;
        printf("Parameter[%s]=%lf\n",(it->first).c_str(),it->second);
    }
}

Parameter::~Parameter()
{
}