#include <string>
#include <iostream>
#include "pipe.h"


PIPE::PIPE(){
  ID = new vector<string>();
  length = new vector<double>();
  diameter  = new vector<double>();
  roughness  = new vector<double>();
  scalingIndicator = false;
}

PIPE::~PIPE(){
  delete ID;
  delete length;
  delete diameter;
  delete roughness;
}


void PIPE::setPIPE(string ID_input,double L,double D,double epmm){
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
//-------------------------------------------------------------------------s
  ID->push_back(ID_input);  
  length->push_back(L);
  diameter->push_back(D);
 // cout<<D<<endl;
  roughness->push_back(epmm);

}
    
void PIPE::pipeScale(string hdlss,string unit){
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
  if (!scalingIndicator){
    Lscale= *max_element(&(*length)[0],&(*length)[0]+length->size());
    Dscale= *max_element(&(*diameter)[0],&(*diameter)[0]+diameter->size());
    if(hdlss.compare("HW")==0){
        Rscale=*max_element(&(*roughness)[0],&(*roughness)[0]+roughness->size());
        Gscale=Lscale/pow(Rscale,1/0.54)/pow(Dscale,(2.63/0.54))*pow(pow(Dscale,2),1/0.54-1);  
    }else if(hdlss.compare("DW")==0){
        Rscale=Dscale;
        Gscale=Lscale/pow(Dscale,5)*pow(Dscale,2);
    }
    for(unsigned int i=0;i<length->size();i++){
      (*length)[i]=(*length)[i]/Lscale;
      if(unit.compare("US")==0)        (*diameter)[i]=(*diameter)[i]/Dscale*0.3048;
      else if(unit.compare("SI")==0)   (*diameter)[i]=(*diameter)[i]/Dscale;
      (*roughness)[i]=(*roughness)[i]/Rscale;
    }
    scalingIndicator=true;
  }
}


void PIPE::dispPipes(vector<int> *SN,vector<int> *EN){
//------------------------------------------------------------------------
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
  cout<<"pipe size="<<ID->size();
  for(unsigned int i=0;i<ID->size();i++)
    cout<<"pipe["<<(*ID)[i]<<"]"<<"from("<<(*SN)[i]<<")to"<<"("<<(*EN)[i]<<")"<<"length="<<(*length)[i]
      <<"diameter="<<(*diameter)[i]<<"roughness"<<(*roughness)[i]<<endl;
}


void PIPE::permutePipe(PIPE* output,vector<int>* p){
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
  for(unsigned int i=0;i<p->size();i++){
    int pipeIndex=(*p)[i];
    output->setPIPE((*ID)[pipeIndex],(*length)[pipeIndex],
    (*diameter)[pipeIndex],(*roughness)[pipeIndex]);
  }
}

