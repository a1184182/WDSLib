#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <map>
#include <iostream>
#include <string>
#include "../Simulation/Simulation.h"

using namespace std;


vector<double> *readLogfile(char* filename){
	string line;
	vector<double> *output=new vector<double> ();
	ifstream myfile(filename);
	if(myfile.is_open()){
		while(getline(myfile,line)){
			output->push_back(stod(line));
		}
	myfile.close();
	return output;
	}else{ 
		cout<<"unable to open file"<<endl;
		return NULL;
	}
} 

int   main(int argc, char *argv[]){
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
 	char *config=argv[1];
 	char *QLogFile=argv[2];
 	char *HLogFile=argv[3];
 	vector<double> *qLog=readLogfile(QLogFile);
 	vector<double> *hLog=readLogfile(HLogFile);
 	if(qLog==NULL) return 5;
 	if(hLog==NULL) return 6;
	Result *result=new Result();
 	Simulation *simulation1=new Simulation();
 	if(simulation1->L1a(result,config)){
	 	simulation1->solve(result);
	 	simulation1->L1b(result);
	 	string solver,FCPA;
	 	if(simulation1->getFlags()->getFlagvalue("SolverFlag")==1) solver="GGA";
	 	else if (simulation1->getFlags()->getFlagvalue("SolverFlag")==2) solver="RCTM";
	 	else return 2;
	 	if(simulation1->getFlags()->getFlagvalue("FCPAFlag")==1) FCPA=" and FCPA";
	 	else FCPA="";	 	
	 	simulation1->dispResult(result);
	 	vector<double> qResult=result->getQsol();
	 	vector<double> hResult=result->getHsol();
	 	cout<<"The continuity residual for the solution of the NYTP system using the "<<solver<<FCPA<<" implementation in WDSLib: "<<result->getFinalCres()<<endl;
	 	cout<<"The energy residual for the solution of the NYTP system using the "<<solver<<FCPA<<" implementation in WDSLib: "<<result->getFinalEres()<<endl;
	 	cout<<"The infinity-norm for the solution of the NYTP system using the "<<solver<<FCPA<<" implementation in WDSLib: "<<result->getFinalNorm()<<endl;
	 	for(int i=0;i<qResult.size();i++)
	 	 	if(abs((*qLog)[i]-qResult[i])>1e-6) 
	 	 		return 7;
	 	
	 	if(result->getFinalCres()>=1e-6) return 1;
	 	if(result->getFinalEres()>=1e-6) return 2;
	 	if(result->getFinalNorm()>=1e-6) return 3;
	}else{
		delete simulation1;
		delete result;
		delete qLog;
		delete hLog;
		return 4;
	}
	delete simulation1;
	delete result;
	delete qLog;
	delete hLog;

 	return 0;
 }
