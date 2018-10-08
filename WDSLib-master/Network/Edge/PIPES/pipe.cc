#include <string>
#include <iostream>
#include <iomanip>    
#include "pipe.h"


PIPE::PIPE(){
  ID = new vector<string>();
  length = new vector<double>();
  diameter  = new vector<double>();
  roughness  = new vector<double>();
  scalingIndicator = false;
  MaxPipeIDLength = 0;
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
  roughness->push_back(epmm);
  if (ID_input.length() > MaxPipeIDLength) MaxPipeIDLength = ID_input.length();
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


void PIPE::dispPipes(ostream& stream,vector<int> *SN,vector<int> *EN,NODE* node){
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
  int NodeIDLength,PipeIDLength;
  MaxPipeIDLength>2?PipeIDLength=MaxPipeIDLength:PipeIDLength=2;
  node->getMaxNodeIDLength()>2?NodeIDLength=node->getMaxNodeIDLength():NodeIDLength=2;
  stream<<("==================\n");
  stream<<("|Link Information|\n"); 
  stream<<("==================\n");
    for(int i=0;i<59+PipeIDLength+2*NodeIDLength;i++) stream<<"-";
    stream<<endl;
    stream <<right<<"| " << setw(PipeIDLength) <<"ID"<<" |  " << setw(NodeIDLength) <<"SN"<<"  |  "<< setw(NodeIDLength) <<"EN"<<"  |    "<< setw(6) <<"Length"<<"    |  " << setw(10) <<"Diameter" <<"  |  "<< setw(10) <<"Roughness"<<"  |";
     stream<<endl;
    for(int i=0;i<59+PipeIDLength+2*NodeIDLength;i++) stream<<"-";
    stream<<endl;

  for(unsigned int i=0;i<ID->size();i++){
    stream<<"| "<<setw(PipeIDLength)<<(*ID)[i]<<" |  "<< setw(NodeIDLength) <<node->getNodeID((*SN)[i])<<"  |  "<< setw(NodeIDLength) <<node->getNodeID((*EN)[i])<<"  |  "<< setw(10) <<(*length)[i]*Lscale<<"  |  "
        << setw(10) <<(*diameter)[i]*Dscale<<"  |  "<< setw(10) <<(*roughness)[i]*Rscale <<"  |"<<endl;
    }
    for(int i=0;i<59+PipeIDLength+2*NodeIDLength;i++) stream<<"-";
    stream<<endl;
}

void PIPE::setScales(double L,double D,double R,double G){  
  Lscale=L;
  Dscale=D;
  Rscale=R;
  Gscale=G;

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
    output->setScales(Lscale,Dscale,Rscale,Gscale);
  }
}

