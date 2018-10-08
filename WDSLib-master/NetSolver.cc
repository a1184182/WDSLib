#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <map>
#include <iostream>
#include <string>
#include "Simulation/Simulation.h"

using namespace std;



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
 	if(argc==2){
		Result *result=new Result();
	 	Simulation *simulation1=new Simulation();
	 	if(simulation1->L1a(result,config)){
		 	simulation1->solve(result);
		 	simulation1->L1b(result);
		 	simulation1->dispResult(result);
		}
		delete simulation1;
		delete result;
	}else{
		cout<<"Error, incorrect number of input arguments given!"<<endl;
		cout<<"Please run WDSLib by inputing the following command:"<<endl;
		#if defined(__linux__) || defined(__CYGWIN__) ||defined(__MACH__)
		cout<<"./Netsolver config.txt"<<endl;
		#elif defined(_WIN)
		cout<<"Netsolver config.txt"<<endl;
		#endif

		return 1;
	}

 	return 0;
 }
