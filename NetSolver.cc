#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <map>
#include <iostream>
#include <string>
#include <sys/time.h>
#include <unistd.h>
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
	Result *result=new Result();
 	Simulation *simulation1=new Simulation();
 	simulation1->L1a(result,config);
 	//Net* core=simulation1->getNet();
 	//for(int i=0;i<core->getNp();i++) core->getPIPE()->setD(i,0.7);
 	simulation1->solve(result);
 	simulation1->L1b(result);
 	simulation1->dispResult(result);
	delete simulation1;
	delete result;

 	return 0;
 }
