
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

int Simulation::readConfig(char* configFile){
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
   	}else return 0;
   	return 1;
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
    int error=input->setInput(inputDirectory,inputFilename);
    if(error!=0) return NULL;
    Net* net =input->getNetInfo();
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
	if(readConfig(config)){
	 	net=getInputData();
	 	if(net==NULL){ 
			cout<<"Error: EPANET input file specified does not exist"<<endl;
			return NULL;
		}
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
	}else{ 
		cout<<"Error: configuration file specified does not exist"<<endl;
		return NULL;
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
	string folder = inputFilename.substr(0, inputFilename.size()-4);
	string resultPath="./"+folder+" Result";
	struct stat info;
	if( stat( resultPath.c_str(), &info ) != 0 )
		mkdir(resultPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	if(flag->getFlagvalue("BasicFlag")==1||flag->getFlagvalue("BasicFlag")==3){
		input->basicInfo(cout);
	}
	if(flag->getFlagvalue("BasicFlag")==2||flag->getFlagvalue("BasicFlag")==3){
		ofstream myfile;
  		string filename=resultPath+"/basicInfo.txt";
  		myfile.open (filename);
		input->basicInfo(myfile);
 		myfile.close();
	}

	if(flag->getFlagvalue("NetInfoFlag")==1||flag->getFlagvalue("NetInfoFlag")==3){
		input->NetInfo(cout,net);
	}

	if(flag->getFlagvalue("NetInfoFlag")==2||flag->getFlagvalue("NetInfoFlag")==3){
		ofstream myfile;
  		string filename=resultPath+"/NetInfo.txt";
  		myfile.open(filename);
		input->NetInfo(myfile,net);
 		myfile.close();
	}



	if(flag->getFlagvalue("ScalingFlag")==1||flag->getFlagvalue("ScalingFlag")==3){
		input->ScalingInfo(cout,net);
	}

	if(flag->getFlagvalue("ScalingFlag")==2||flag->getFlagvalue("ScalingFlag")==3){
		ofstream myfile;
  		string filename=resultPath+"/ScalingInfo.txt";
  		myfile.open(filename);
		input->ScalingInfo(myfile,net);
 		myfile.close();
	}


	if(flag->getFlagvalue("ConvergenceFlag")==1||flag->getFlagvalue("ConvergenceFlag")==3){
		input->ConverInfo(cout,parameter,flag,result);
	}
	if(flag->getFlagvalue("ConvergenceFlag")==2||flag->getFlagvalue("ConvergenceFlag")==3){
		ofstream myfile;
  		string filename=resultPath+"/Convergence.txt";
  		myfile.open(filename);
		input->ConverInfo(myfile,parameter,flag,result);
 		myfile.close();
	}
	
	if(flag->getFlagvalue("LinkResultflag")==1||flag->getFlagvalue("LinkResultflag")==3){
		input->LinkResult(cout,net,flag,parameter,result);
	}
	if(flag->getFlagvalue("LinkResultflag")==2||flag->getFlagvalue("LinkResultflag")==3){
		ofstream myfile;
  		string filename=resultPath+"/LinkResult.txt";
  		myfile.open(filename);
		input->LinkResult(myfile,net,flag,parameter,result);
 		myfile.close();
	}

	if(flag->getFlagvalue("NodalResultflag")==1||flag->getFlagvalue("NodalResultflag")==3){
		input->NodeResult(cout,net,parameter,result->getHsol());
	}
	if(flag->getFlagvalue("NodalResultflag")==2||flag->getFlagvalue("NodalResultflag")==3){
		ofstream myfile;
  		string filename=resultPath+"/NodeResult.txt";
  		myfile.open(filename);
		input->NodeResult(myfile,net,parameter,result->getHsol());
 		myfile.close();
	}

	if(flag->getFlagvalue("StatFlag")==1||flag->getFlagvalue("StatFlag")==3){
		input->StatInfo(cout,net,result->getQsol(),result->getHsol());
	}
	if(flag->getFlagvalue("StatFlag")==2||flag->getFlagvalue("StatFlag")==3){
		ofstream myfile;
  		string filename=resultPath+"/StatInfo.txt";
  		myfile.open(filename);
		input->StatInfo(myfile,net,result->getQsol(),result->getHsol());
 		myfile.close();
	}


	if(flag->getFlagvalue("QitersFlag")==1||flag->getFlagvalue("QitersFlag")==3){
		result->dispQiter(cout,net->getPIPE());
	}
	if(flag->getFlagvalue("QitersFlag")==2||flag->getFlagvalue("QitersFlag")==3){
		ofstream myfile;
  		string filename=resultPath+"/Qiters.txt";
  		myfile.open(filename);
		result->dispQiter(myfile,net->getPIPE());
 		myfile.close();
	}

	if(flag->getFlagvalue("SolverFlag")!=2){
		if(flag->getFlagvalue("HitersFlag")==1||flag->getFlagvalue("HitersFlag")==3){
			result->dispHiter(cout,net->getNODE());
		}
		if(flag->getFlagvalue("HitersFlag")==2||flag->getFlagvalue("HitersFlag")==3){
			ofstream myfile;
	  		string filename=resultPath+"/Hiters.txt";
	  		myfile.open(filename);
			result->dispHiter(myfile,net->getNODE());
	 		myfile.close();
		}
	}
	if(flag->getFlagvalue("timeFlag")==1||flag->getFlagvalue("timeFlag")==3){
		result->DispCPUtime(cout);
	}
	if(flag->getFlagvalue("timeFlag")==2||flag->getFlagvalue("timeFlag")==3){
		ofstream myfile;
  		string filename=resultPath+"/Timing.txt";
  		myfile.open(filename);
		result->DispCPUtime(myfile);
 		myfile.close();
	}
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
		double diameter=(*D)[(*p)[(*pRow)[i]]]/Dscale/1000;
		core->getPIPE()->setD(i,diameter);
	}
}
