
// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <string.h>
#include <vector>
#include "Simulation.h"

// ---------------------------------------------------------------------------
//  Simulati: Constructors and Destructor
// ---------------------------------------------------------------------------
Simulation::Simulation()
{
	inputDirectory="../Network";
	inputFilename="example.inp";
	flag = new Flag();
	parameter = new Parameter();
	input = new Input();
	gga=NULL;
	net=NULL;
	rctm=NULL;
}

Simulation::~Simulation()
{
	delete flag;
	delete parameter;
	delete input;
	if(net!=NULL) delete net;
	if(gga!=NULL) delete gga;
	if(rctm!=NULL) delete rctm;
}

void Simulation::setInputFile(string value){
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
		inputFilename=value;
		
}
void Simulation::setInputDirectory(string value){
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
		inputDirectory=value;
		
}

string trim(string str){
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
	string::iterator end_pos = remove(str.begin(), str.end(),' ');
	str.erase(end_pos, str.end());
	end_pos = remove(str.begin(), str.end(),'\t');
	str.erase(end_pos, str.end());
	end_pos = remove(str.begin(), str.end(),'\r');
	str.erase(end_pos, str.end());
    return str;
}


int getToken(string *token ,string Line)
//------------------------------------------------------------------------- 
//                             getToken                            
//                                                                          
//  Date:    10/09/2014                                                     
//  Author:  Mengning Qiu                                                   
//  Input:   Line(char):       A line from the config file
//  Output:  token(char):      A tag in the config file
//  Output:  indicator(char):  Indicator of the type of token
//  Purpose: get a line from the config file and return a tag if found             
//  calls:   node                                                   
//------------------------------------------------------------------------- 
{
	*token=trim(Line);
	if(Line.empty())    return 0;	
	for(unsigned int i=0; i<Line.length();i++)
	{
	    size_t Start=Line.find("[")+1;
	    size_t End=Line.find("]");
	    if(Start!=string::npos&&End!=string::npos&&End>Start)
	    {
			*token=Line.substr(Start,End-Start);
	    	return 1;
		}   
	}
	for(unsigned int i=0; i<Line.length();i++)
	{
	    size_t Start=Line.find("<")+1;
	    size_t End=Line.find(">");
	    if(Start!=string::npos&&End!=string::npos&&End>Start)
	    {
	    	*token=Line.substr(Start,End-Start);
			return 2;
	    }
	}
	return 3;
}

void Simulation::readConfig(char* configFile){
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
	string Line;
	ifstream config;
   	string token;
   	string structname,fieldname;
	config.open(configFile);
	string::size_type sz;
	if (config.is_open()){
 		while(getline(config,Line)) 
 		{
 			string::iterator end_pos = find(Line.begin(), Line.end(),'%');
   			if (end_pos!=Line.end())				Line.erase(end_pos, Line.end()); 
   			int i=getToken(&token ,Line);
   			if (i){
	   			switch (i)
	   			{
	        		case 1:
	          	 		structname=token;
	          	 		break;
	        		case 2:
	            		fieldname=token;
		            		if (fieldname.compare("end")==0)	continue;
	          	 		break;
	       			case 3:
	                	if (structname.compare("InputFile")==0)
		                	if (fieldname.compare("directory")==0)	setInputDirectory(token);
		                	if (fieldname.compare("file")==0)	setInputFile(token);
		                else if (structname.compare("Parameter")==0)
		                	parameter->setParameter(fieldname ,atof(token.c_str()));
		                else if (structname.compare("dispFlag")==0){
		                	if (token.compare("true")==0)
								flag->setFlag(fieldname ,1);
							else if (token.compare("false")==0)
		                		flag->setFlag(fieldname ,0);
							else
		                		flag->setFlag(fieldname ,atoi(token.c_str()));
						}
		                else if (structname.compare("controlFlag")==0){
		                	if (token.compare("true")==0)
		                		flag->setFlag(fieldname ,1);
							else if (token.compare("false")==0)
		                		flag->setFlag(fieldname ,0);
							else
		                		flag->setFlag(fieldname ,atoi(token.c_str()));
						}
	          	 		break;
	        	}
	    	}
   		}
   		config.close();
   	}
   	return;
}

Net* Simulation::getInputData(){
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
	char* filename;
	file=inputDirectory+inputFilename;
    filename = (char *)malloc(file.size() + 1);
    memcpy(filename, file.c_str(), file.size() + 1);
    input->setInput(filename,"a.txt");
    Net* net =input->getNetInfo();
	free(filename);
	return net;
}

Net* Simulation::L1a(Result *result,char * config){
//-------------------------------------------------------------------------
//  Date:    10/09/2014
//  Author:  Mengning Qiu
//  Input:   
//  Output:  
//  Purpose: 
//  calls:   
//  called from: 
//-------------------------------------------------------------------------
	readConfig(config);
 	net=getInputData();
	int SolverFlag=flag->getFlagvalue("SolverFlag");
	bool FCPAFlag=flag->getFlagvalue("FCPAFlag");
	Topology *topology=net->getTopology();
	topology->NetworkDecomposition(result,net->getNODE()->getDM(),SolverFlag,FCPAFlag);	
  	if(SolverFlag==1){ 		
  		gga=new GGAsolver(net,parameter,flag);
		gga->getscale(1);
		gga->amd(result);
  	}else if(SolverFlag==2){	
  		rctm=new RCTMsolver(net,parameter,flag);
		rctm->getscale(2);
		rctm->amd(result);
  	}
 	return net;
}


void Simulation::solve(Result *result){
//-------------------------------------------------------------------------
//  Date:    10/09/2014
//  Author:  Mengning Qiu
//  Input:   
//  Output:  
//  Purpose: 
//  calls:   
//  called from: 
//-------------------------------------------------------------------------
	int SolverFlag=flag->getFlagvalue("SolverFlag");
	if(SolverFlag==1){ 		
		gga->runH(result);
  	}else if(SolverFlag==2){	
		rctm->runH(result);
  	}

}
/*
void Simulation::L3(Result *result,Net * net){


}
void Simulation::L2b(Result *result,Net * net){


}*/
void Simulation::L1b(Result *result){
//-------------------------------------------------------------------------
//  Date:    10/09/2014
//  Author:  Mengning Qiu
//  Input:   
//  Output:  
//  Purpose: 
//  calls:   
//  called from: 
//-------------------------------------------------------------------------

	int SolverFlag=flag->getFlagvalue("SolverFlag");
	if(SolverFlag==1){ 		
		gga->reverseH(result);
  	}else if(SolverFlag==2){	
		rctm->reverseH(result);
  	}
}

void Simulation::dispResult(Result *result){
//-------------------------------------------------------------------------
//  Date:    10/09/2014
//  Author:  Mengning Qiu
//  Input:   
//  Output:  
//  Purpose: 
//  calls:   
//  called from: 
//-------------------------------------------------------------------------
	if(flag->getFlagvalue("BasicFlag")) input->basicInfo();
	if(flag->getFlagvalue("NetInfoFlag")) input->NetInfo(net);
	if(flag->getFlagvalue("ScalingFlag")) input->ScalingInfo(net);
	if(flag->getFlagvalue("ConvergenceFlag")) input->ConverInfo(parameter,result);
	if(flag->getFlagvalue("LinkResultflag")) input->LinkResult(net,parameter,result->getQsol());
	if(flag->getFlagvalue("NodalResultflag")) input->NodeResult(net,parameter,result->getHsol());
	if(flag->getFlagvalue("StatFlag")) input->StatInfo(net,result->getQsol(),result->getHsol());
	if(flag->getFlagvalue("QitersFlag")) 	result->dispQiter();
	if(flag->getFlagvalue("HitersFlag")) 	result->dispHiter();
	if(flag->getFlagvalue("timeFlag")) 	result->DispCPUtime();
}


void Simulation::setD(vector<int> *p,vector<double> *D,double Dscale){
	int SolverFlag=flag->getFlagvalue("SolverFlag");
	for(int i=0;i<p->size();i++){
		double diameter=(*D)[(*p)[i]]/Dscale/1000;
		net->getPIPE()->setD(i,diameter);
	}
	vector<int> *pRow=net->getTopology()->getcorePipes(); 
	Net* core;
	if(SolverFlag==1)	
		core=gga->getNet();
	else if(SolverFlag==2)
		core=rctm->getNet();
	for(int i=0;i<pRow->size();i++){
		double diameter=(*D)[(*pRow)[(*p)[i]]]/Dscale/1000;
		core->getPIPE()->setD(i,diameter);
	}
	//core->dispNet();
}