#include "node.h"
#include <iomanip>      


NODE::NODE()
{
	nodeID = new vector<string>();
	sourceID = new vector<string>();
	dm = new vector<double>();
	zs = new vector<double>();
	zu = new vector<double>();
	scalingIndicator = false;
	MaxNodeIDLength = 0;
}

NODE::~NODE(){
	delete nodeID;
	delete zu;
	delete sourceID;
	delete dm;
	delete zs;
}

void NODE::setNODE(string ID_input,double dm_input,double zu_input){
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
	nodeID->push_back(ID_input);
	dm->push_back((double)dm_input);
	zu->push_back((double)zu_input);
	if (ID_input.length() > MaxNodeIDLength) MaxNodeIDLength = ID_input.length();

}

void NODE::setSOURCE(string ID_input,double zs_input){
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
	sourceID->push_back(ID_input);
	zs->push_back((double)zs_input);

}

void NODE::nodeScale(){
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
		dmScale=*max_element(dm->begin(),dm->end());
		zsScale=*max_element(zs->begin(),zs->end());
		for(unsigned int i=0;i<dm->size();i++){
			(*dm)[i]=(*dm)[i]/dmScale;
		}
		for(unsigned int i=0;i<zs->size();i++){
			(*zs)[i]=(*zs)[i]/zsScale;
		}
		scalingIndicator=true;
	}
	
}


void NODE::permuteNode(NODE* output,vector<int>* v){
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
	for(unsigned int i=0;i<v->size();i++){
    	int nodeIndex=(*v)[i];
    	output->setNODE((*nodeID)[nodeIndex],(*dm)[nodeIndex],(*zu)[nodeIndex]);
  	}
  	for(unsigned int i=0;i<zs->size();i++){
	  	output->setSOURCE((*sourceID)[i],(*zs)[i]);
  	} 

}


void NODE::dispNodes(ostream& stream){
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
	int MaxFieldLength;
	MaxNodeIDLength>2?MaxFieldLength=MaxNodeIDLength:MaxFieldLength=2;
	stream<<("==================\n");
 	stream<<("|Node Information|\n");
	stream<<("==================\n");
    for(int i=0;i<40+MaxNodeIDLength;i++) stream<<"-";
    stream<<endl;
	stream <<right<<"| " << setw(MaxFieldLength) <<"ID"  <<" |  " << "Elevation Head"<<"  |  "<< "Nodal Demand"<<"  |"<<endl;
    for(int i=0;i<40+MaxNodeIDLength;i++) stream<<"-";
    stream<<endl;
	for(unsigned int i=0;i<nodeID->size();i++)	stream<<scientific<<setprecision(3)<<right<<"| "<<setw(MaxFieldLength)<<((*nodeID)[i]).c_str()<<" |    " <<setw(10)<<(*zu)[i]*zsScale<<"    |    "<< (*dm)[i]*dmScale<<"   |"<<endl;
    for(int i=0;i<40+MaxNodeIDLength;i++) stream<<"-";
    stream<<"\n\n\n";
	stream<<("====================\n");
 	stream<<("|Source Information|\n");
	stream<<("====================\n");
    for(int i=0;i<23+MaxNodeIDLength;i++) stream<<"-";
    stream<<endl;
	stream <<right<<"| " << setw(MaxFieldLength) <<"ID"  <<" |  " << "Elevation Head"<<"  |"<<endl;
	for(int i=0;i<23+MaxNodeIDLength;i++) stream<<"-";
    stream<<endl;
	for(unsigned int i=0;i<sourceID->size();i++)
		stream<<scientific<<setprecision(3)<<right<<"| "<<setw(MaxFieldLength)<<(*sourceID)[i].c_str()<<" |  "<<setw(14)<<(*zs)[i]*zsScale<<"  |"<<endl;
	    for(int i=0;i<23+MaxNodeIDLength;i++) stream<<"-";
    stream<<endl;
    stream<<"\n\n\n";

	
}
