#include "node.h"

NODE::NODE()
{
	nodeID = new vector<string>();
	sourceID = new vector<string>();
	dm = new vector<double>();
	zs = new vector<double>();
	zu = new vector<double>();
	scalingIndicator = false;
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


void NODE::dispNodes(){
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
	for(unsigned int i=0;i<nodeID->size();i++){
		printf("node[%s]zu=%f,demand=%f\n",((*nodeID)[i]).c_str(),(*zu)[i],(*dm)[i]);
	}

	for(unsigned int i=0;i<sourceID->size();i++)
		cout<<"source["<<(*sourceID)[i]<<"]"<<"zs="<<(*zs)[i]<<endl;
}
