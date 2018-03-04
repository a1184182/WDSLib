#include "Input.h"
#include <fstream>
#include <string.h>
#include <iomanip> 
#include <stdio.h>

#define   GPMperCMS   15850.3187
#define   AFDperCMS   70.0537111
#define   MGDperCMS   22.82457759
#define   IMGDperCMS  19.00635545
#define   CFSperCMS   35.31467011
#define   LPSperCMS   1000.0
#define   LPMperCMS   60000.0
#define   CMHperCMS   3600.0
#define   CMDperCMS   86400.0
#define   MLDperCMS   86.4

Input::Input()
{
	inputFile="example.inp";
	RptFile="report.txt";
}

int Input::setInput(char* InpFile,char* reportFile){
//-------------------------------------------------------------------------
//  Date:    10/09/2014
//  Author:  Mengning Qiu
//  Input:   
//  Output:  
//  Purpose: 
//  calls:   
//  called from: 
//-------------------------------------------------------------------------
	inputFile=InpFile;
	RptFile=reportFile;
	return ENopen(InpFile,reportFile," ");
}
Input::~Input(){
	int err=ENclose();
}
Net* Input::getNetInfo(){
//-------------------------------------------------------------------------
//  Date:    10/09/2014
//  Author:  Mengning Qiu
//  Input:   
//  Output:  
//  Purpose: 
//  calls:   
//  called from: 
//-------------------------------------------------------------------------	
	string hd,u,uf,up;
    int flowunit;
    int Formflag;
	int np,nj,nf,nn;
	double qcf=0;
	ENgetcount(EN_NODECOUNT,&nn);
    ENgetcount(EN_LINKCOUNT,&np);
    ENgetcount(EN_TANKCOUNT,&nf);
    ENgethdlss(&Formflag);
    ENgetflowunits(&flowunit);
    switch (flowunit)
    {
	    case EN_CFS:  
		    u="US";
		    uf="CFS";
		    up="ft";
		    qcf=CFSperCMS;
	    	break;
	    case EN_GPM:
		    u="US";
		    uf="GPM";
		    up="ft";
		    qcf=GPMperCMS;
	    	break;
	    case EN_MGD:
	    	u="US";
	    	uf="MGD";
	    	up="ft";
		    qcf=MGDperCMS;
	    	break;
	    case EN_IMGD:
	    	u="US";
	    	uf="IMGD";
	    	up="ft";
		    qcf=IMGDperCMS;
	    	break;
	    case EN_AFD:
	    	u="US";
	    	uf="AFD";
	    	up="ft";
		    qcf=AFDperCMS;
	    	break;
	    case EN_LPS:
	    	u="SI";
	    	uf="LPS";
	    	up="m";
		    qcf=LPSperCMS;
	    	break;
	    case EN_LPM:
	    	u="SI";
	    	uf="LPM";
	    	up="m";
		    qcf=LPMperCMS;
	    	break;
	    case EN_MLD: 
	    	u="SI";
	    	uf="MLD";
	    	up="m";  
		    qcf=MLDperCMS;
	    	break; 
	    case EN_CMH:   
	    	u="SI";
	    	uf="CHM";
	    	up="m"; 
		    qcf=CMHperCMS;
	    	break;
	    case EN_CMD:
	    	u="SI";
	    	uf="CMD";
	    	up="m";
		    qcf=CMDperCMS;
	    	break;
	}
	switch (Formflag){
	case 1:
		hd="DW";
		break;
	case 2:
		hd="HW";
		break;
	}   
    nj=nn-nf;
    Net* net =new Net(np, nj, nf, hd, u, uf, up,qcf);
    getPipeData(net);
    getNodeData(net);
    return net;
}


void Input::getPipeData(Net*  net){
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
	char pID[15];
	int pSN,pEN;
	double plength,pdiameter,proughness;
	int np=net->getNp();
	string hdlss=net->getHd();
	string unit = net->getUnit();
	for(int i=1;i<=np;i++){
		ENgetlinkid(i,pID);
		ENgetlinknodes(i,&pSN,&pEN);
		ENgetlinkvalue(i,EN_DIAMETER,&pdiameter);
		ENgetlinkvalue(i,EN_LENGTH,&plength);
		ENgetlinkvalue(i,EN_ROUGHNESS,&proughness);
		if(hdlss.compare("DW")==0){
			proughness=proughness/1000;
		}
		string dummyID=pID;
		if(unit.compare("US")==0){
			net->setPIPE(dummyID,pSN-1,pEN-1,(plength),(pdiameter)/12,(proughness));
		}else if (unit.compare("SI")==0){
			net->setPIPE(dummyID,pSN-1,pEN-1,(plength),(pdiameter)/1000,(proughness));
		}
		
	}
}

void Input::getNodeData(Net*  net){
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
	char nID[15];
	double Pdm=0;
	double Pel=0;
	int nn=net->getNn();
	int nj=net->getNj();
	int error;

	for(int i=1;i<=nn;i++)
	{
		if(i<=nj){
			ENgetnodeid(i,nID);
			ENgetnodevalue(i,EN_ELEVATION,&Pel);
			error=ENgetnodevalue(i,EN_BASEDEMAND,&Pdm);
			string dummyID=nID;
			net->setNODE(dummyID,(Pdm),(Pel));
		}else{
			ENgetnodeid(i,nID);
			ENgetnodevalue(i,EN_ELEVATION,&Pel);
			string dummyID=nID;
			net->setSOURCE(dummyID,(Pel));
		}
	}

	//delete[] nID;

}


void Input::basicInfo(){
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
	char hostname[HOST_NAME_MAX];
	char username[LOGIN_NAME_MAX];
	gethostname(hostname, HOST_NAME_MAX);
	getlogin_r(username, LOGIN_NAME_MAX);

 	cout<<endl;
 	cout<<"Basic Information\n";
 	cout<<"-------------------------------\n";
 	cout<<"Name="<<hostname<<","<<username<<endl;
 	time_t t=time(0);
 	struct tm* now=localtime(&t);
 	cout<<"Time: "<<asctime(now);
 	cout<<"Machine epsilon: "<<numeric_limits<double>::epsilon()<<endl;
}


void Input::NetInfo(Net* net){
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
 	cout<<("\n");
 	cout<<("Network Information\n");
 	cout<<("-------------------------------\n");
 	cout<<("Input filename: %s\n",inputFile);
 	net->dispNet();
 	cout<<("\n");
}


void Input::ScalingInfo(Net* net){
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
	cout<<("Scaling Information:\n");
   	cout<<("-------------------------------------------------------------\n");
 	net->dispScale();
   	cout<<("\n");
}


void Input::ConverInfo(Parameter* parameter,Result* result){
//-------------------------------------------------------------------------
//                               ConverRpt
//
//  Date:    10/09/2014
//  Author:  Mengning Qiu
//  Input:   iterator(int):     the number of current iteration
//           result(struct):    the struct that contains all result values
//           StopTest(char):    the flag of the stopping test that is being
//                              used
//  Output:  none
//  Purpose: write the convergence information:
//           the convergence information include:
//           the stopping tolerance defined, the type of the stopping test
//           used, the iterates q norm, the iterates h norm, the iterates
//           norm of energy residue, the iterates norm of continuity
//           residue, the final q norm, the final h norm, the final norm of 
//           energy residue, and the final norm of continuity residue.
//  calls:   none
//  called from: writereport
//-------------------------------------------------------------------------
	vector<double> NormIter=result->getIterNorm();
	vector<double> EresIter=result->getIterEres();
	vector<double> CresIter=result->getIterCres();
	double NormFinal=result->getFinalNorm();
	double EresFinal=result->getFinalEres();
	double CresFinal=result->getFinalCres();
    cout<<"Convergence Information:"<<endl; 
    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<"Stopping tolerance: "<<parameter->getParametervalue("StopTol")<<endl; 
    if(parameter->getParametervalue("StopTest")==1)
        cout<<"Stopping Test: inf-norm of Relative difference of flows"<<endl;
    else if(parameter->getParametervalue("StopTest")==2)
        cout<<"Stopping Test: inf-norm of Relative difference of heads"<<endl;
    else if(parameter->getParametervalue("StopTest")==3)
        cout<<"Stopping Test: Stopping Test used in Matlab"<<endl;
    
    cout<<("iteration\t\tNorm\t\t\tEnergy Residual\t\tContinuity Residual\n");
    for(unsigned int i=0;i<EresIter.size();i++)
	    printf("%d\t\t\t%5.2e\t\t\t%5.2e\t\t\t%5.2e\n",i+1,NormIter[i],EresIter[i],CresIter[i]);
//------------------------------END OF ConvergeRpt------------------------%

}


//--------------------------START OF LinkResult----------------------------
void Input::LinkResult(Net* net,Parameter* Parameter,vector<double> qsol){
//------------------------------------------------------------------------- 
//                               LinkResult                                  
//                                                                          
//  Date:    10/09/2014                                                     
//  Author:  Mengning Qiu                                                   
//  Input:   net(struct):       the struct that contains all network 
//                              information         
//           result(struct):    the struct that contains all results
//           flag(struct):      the struct that contains all flags
//  Output:  none
//  Purpose: write the link result to the output file:
//           for each pipe:
//           start node, end node, Scaled final flow rate, unscaled final
//           flow rate, flow velocity, final diagonal elements of G matrix,
//           and final diagonal elements of F matrix.
//  calls:   none
//  called from: writereport
//-------------------------------------------------------------------------
	PIPE* pipe=net->getPIPE();
	NODE* node=net->getNODE();
  	const double PI = atan(1.0)*4;
  	double qcf=net->getQCF();
  	int np = net->getNp();
    vector<int>* SN=net->getTopology()->getSN();
    vector<int>* EN=net->getTopology()->getEN();
    vector<double> *D=pipe->getD();
    double qScale=pipe->Diascale()*pipe->Diascale();
    int MaxNpIterResult = Parameter->getParametervalue("MaxNpIterResult");
    cout<<endl;
    cout<<"Link Result:"<<endl; 
    cout<<"-----------------------------------------------------------------------------------------------"<<endl;
    /*if (np>=MaxNpIterResult){
        cout<<("The number of pipes is greater than %d\n",MaxNpIterResult);
        cout<<("No link Result will be displayed.\n");
        cout<<("\n\n");
        return;
    }*/
    cout<<"ID\tStart\tEnd\t\tScaled Flow Rate\tFlow Rate\tVelocity\t\tG\t\t\tF"<<endl;
    cout<<"-----------------------------------------------------------------------------------------------"<<endl;
    for(int i = 0; i < np; i++){
    	cout<<(pipe->getPipeID(i))<<"\t"<<(node->getNodeID((*SN)[i]))<<"\t\t"<<(node->getNodeID((*EN)[i]))
    	<<"\t\t\t"<<qsol[i]/qScale<<"\t\t\t"<<qsol[i]<<"\t\t"<<qsol[i]/(PI/4*qScale*(*D)[i]*(*D)[i])<<endl;
    }
    cout<<"\n\n";
}
//----------------------------END OF LinkResult----------------------------


//--------------------------START OF NodalResult---------------------------//
void Input::NodeResult(Net* net,Parameter* Parameter,vector<double> hsol){
//----------------------------------------------------------------------- 
//                               NodalResult
//
//  Date:    10/09/2014
//  Author:  Mengning Qiu
//  Input:   h(vector):         the column vector of the final nodal heads
//           hscale(double):    the scale factor for head
//  Output:  none
//  Purpose: write the nodal result to the output file:
//           for each node:
//           the scaled final nodal heads and the unscaled nodal heads
//  calls:   none
//  called from: writereport
//-------------------------------------------------------------------------//

  	int np = net->getNp();
  	int nj = net->getNj();
	PIPE* pipe=net->getPIPE();
	NODE* node=net->getNODE();
    double hScale=node->ELscale();
    int MaxNpIterResult = Parameter->getParametervalue("MaxNpIterResult");
    cout<<"Final Nodal Head"<<endl;
    cout<<"----------------------------------------------------------"<<endl;   
    cout<<"Node ID\t\tScaled Nodal Head\t\tUnscaled Nodal Head\n";
    cout<<"----------------------------------------------------------\n";
    for(int i = 0 ; i < nj ; i++)
  		cout<<(node->getNodeID(i))<<"\t\t\t\t"<<hsol[i]/hScale<<"\t\t\t\t"<<hsol[i]<<endl;
   	cout<<"\n\n";
}

double median(vector<double> &v){
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
	if(v.size()%2==0)
	{
		size_t n = v.size() / 2;
    	nth_element(v.begin(), v.begin()+n, v.end());
    	return (v[n-1]+v[n])/2;
	}else{
    	size_t n = v.size() / 2;
    	nth_element(v.begin(), v.begin()+n, v.end());
    	return v[n];
	}
}

double average(vector<double> &v){
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
	double sum=0;
	for(unsigned int i = 0; i<v.size();i++)
		sum=sum+v[i];
	return sum/v.size();
}

//----------------------------END OF NodalResult---------------------------


//-------------------------START OF StatReport-----------------------------
void Input::StatInfo(Net* net,vector<double> qsol,vector<double> hsol){
//------------------------------------------------------------------------- 
//                                 StatReport
//                                                                          
//  Date:    10/09/2014
//  Author:  Mengning Qiu
//  Input:   result(class):    the class that contains all result values
//  Output:  none
//  Purpose: write the statistical report of the result
//           the statistical information include:
//               maximum, minimum, median, mean, and interquartile ranges
//           the reporting variables: final unscaled flow, final unscaled
//           head, final scaled flow, final scaled head
//  calls:   none
//  called from:   writereport
//-------------------------------------------------------------------------
	PIPE* pipe=net->getPIPE();
	NODE* node=net->getNODE();
	double qmax=*max_element(qsol.begin(),qsol.end());
	double hmax=*max_element(hsol.begin(),hsol.end());
	double qmin=*min_element(qsol.begin(),qsol.end());
	double hmin=*min_element(hsol.begin(),hsol.end());
	double qmedian=median(qsol);
	double hmedian=median(hsol);
	double qAve=average(qsol);
	double hAve=average(hsol);
    double hScale=node->ELscale();
    double qScale=pipe->Diascale()*pipe->Diascale();
    
    printf("Statistical Information:\n"); 
    printf("-------------------------------------------------------------\n");
    printf("\t\t\t\t\tScaled Flow\t\tFlow\t\tScaled Head\t\tHead\n");
    printf("Max\t\t\t\t\t%6.3f\t\t\t%6.3f\t\t%6.3f\t\t%6.3f\n",qmax/qScale,qmax,hmax/hScale,hmax);
    printf("Min\t\t\t\t\t%6.3f\t\t\t%6.3f\t\t%6.3f\t\t%6.3f\n",qmin/qScale,qmin,hmin/hScale,hmin);
    printf("Median\t\t\t\t\t%6.3f\t\t\t%6.3f\t\t%6.3f\t\t%6.3f\n",qmedian/qScale,qmedian,hmedian/hScale,hmedian);
    printf("Average\t\t\t\t\t%6.3f\t\t\t%6.3f\t\t%6.3f\t\t%6.3f\n",qAve/qScale,qAve,hAve/hScale,hAve);
    printf("\n\n");  
//---------------------------END OF StatReport-----------------------------%


}

