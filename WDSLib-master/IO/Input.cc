#include "Input.h"

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

int Input::setInput(string inputDirectory,string inputFilename){
//-------------------------------------------------------------------------
//  Date:    10/09/2014
//  Author:  Mengning Qiu
//  Input:   
//  Output:  
//  Purpose: 
//  calls:   
//  called from: 
//-------------------------------------------------------------------------
	char* filename;
	string file=inputDirectory+inputFilename;
    filename = (char *)malloc(file.size() + 1);
    memcpy(filename, file.c_str(), file.size() + 1);
	inputFile=file;
	RptFile="Rpt";
	int err=ENopen(filename, "Rpt","");
	free(filename);
	return err;
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


void Input::getPipeData(Net* net){
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


void Input::basicInfo(ostream& stream){
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
	stream << "===================\n";
	stream << "|Basic Information|\n";
	stream << "===================\n";
	#if defined(__linux__) || defined(__CYGWIN__)
	char hostname[HOST_NAME_MAX];
	char username[LOGIN_NAME_MAX];
	gethostname(hostname, HOST_NAME_MAX);
	getlogin_r(username, LOGIN_NAME_MAX);
	stream << "Name=" << hostname << "," << username << endl;
	#elif defined(__MACH__)
	char hostname[20];
	char username[20];
	gethostname(hostname, 20);
	getlogin_r(username, 20);
	stream << "Name=" << hostname << "," << username << endl;
	#elif defined(_WIN)
	char* hostname=getenv("COMPUTERNAME");
	char* username=getenv("USERNAME");
	stream << "Name=" << hostname << "," << username << endl;
	#endif
 	time_t t=time(0);
 	struct tm* now=localtime(&t);
 	stream<<"Time: "<<asctime(now);
 	stream<<"Machine epsilon: "<<numeric_limits<double>::epsilon()<<endl;
 	stream<<"\n\n\n";

}


void Input::NetInfo(ostream& stream,Net* net){
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
 	stream<<("\n");
 	stream<<"=====================\n";
 	stream<<("|Network Information|\n");
 	stream<<"=====================\n";
 	stream<<("-------------------------------\n");
 	stream<<"Input filename: "<<inputFile<<endl;
 	net->dispNet(stream);
 	stream<<("\n");
}


void Input::ScalingInfo(ostream& stream,Net* net){
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
   	stream<<("=====================\n");
	stream<<("|Scaling Information|\n");
   	stream<<("=====================\n");
 	net->dispScale(stream);
   	stream<<("\n\n\n");
}


void Input::ConverInfo(ostream& stream,Parameter* parameter,Flag* flag,Result* result){
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
 	stream<<"=========================\n";
    stream<<"|Convergence Information|"<<endl; 
 	stream<<"=========================\n";
    stream<<"Stopping tolerance: "<<parameter->getParametervalue("StopTol")<<endl; 
    if(parameter->getParametervalue("StopTest")==1)
        stream<<"Stopping Test: inf-norm of Relative difference of flows"<<endl;
    else if(parameter->getParametervalue("StopTest")==2)
        stream<<"Stopping Test: inf-norm of Relative difference of heads"<<endl;
    else if(parameter->getParametervalue("StopTest")==3)
        stream<<"Stopping Test: Stopping Test used in Matlab"<<endl;
    
    for(int i=0;i<33;i++) stream<<"-";
    if(flag->getFlagvalue("SolverFlag")==1)	for(int i=0;i<44;i++) stream<<"-";
    stream<<endl;
    stream<<"|  "<<"Iteration"<<"  |      "<<"Norm"<<"     ";
	if(flag->getFlagvalue("SolverFlag")==1){ 		
		stream<<"  |  "<<"Energy Residual"<<"  |  "<<"Continuity Residual";
  	}
  	stream<<"  |"<<endl;
    for(int i=0;i<33;i++) stream<<"-";
    if(flag->getFlagvalue("SolverFlag")==1)	for(int i=0;i<44;i++) stream<<"-";
    stream<<endl;
    for(unsigned int i=0;i<EresIter.size();i++){
    	stream<<"|     "<< scientific<< setprecision(3)<<setw(2)<<i+1<<"      |    "<<NormIter[i]<<"  ";
		if(flag->getFlagvalue("SolverFlag")==1) 		stream<<"  |     "<<EresIter[i]<<"     |       "<<CresIter[i]<<"     ";
		stream<<"  |"<<endl;
	}
    for(int i=0;i<33;i++) stream<<"-";
    if(flag->getFlagvalue("SolverFlag")==1)	for(int i=0;i<44;i++) stream<<"-";
    stream<<endl;
    stream<<endl;


//------------------------------END OF ConvergeRpt------------------------%

}


//--------------------------START OF LinkResult----------------------------
void Input::LinkResult(ostream& stream,Net* net,Flag* flag,Parameter* Parameter,Result* result){
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
	vector<double> qsol=result->getQsol();
	vector<double> G=result->getGfinal();
	vector<double> F=result->getFfinal();
  	const double PI = atan(1.0)*4;
  	double qcf=net->getQCF();
  	int np = net->getNp();
  	bool GFflag=flag->getFlagvalue("GFflag");
    vector<int>* SN=net->getTopology()->getSN();
    vector<int>* EN=net->getTopology()->getEN();
    vector<double> *D=pipe->getD();
    double qScale=pipe->Diascale()*pipe->Diascale();
    double GScale=pipe->GFscale();
	int MaxPipeIDLength;
	  pipe->getMaxPipeIDLength()>2?MaxPipeIDLength=pipe->getMaxPipeIDLength():MaxPipeIDLength=2;
	int MaxNodeIDLength;
	  node->getMaxNodeIDLength()>2?MaxNodeIDLength=node->getMaxNodeIDLength():MaxNodeIDLength=2;
    int MaxNpIterResult = Parameter->getParametervalue("MaxNpIterResult");

	
    stream<<"Link Result:"<<endl; 
    for(int i=0;i<65+MaxPipeIDLength+2*MaxNodeIDLength;i++) stream<<"-";
    if(GFflag)	for(int i=0;i<32;i++) stream<<"-";
    stream<<endl;
    stream <<right<<"| " << setw(MaxPipeIDLength) <<"ID"<<" |  " << setw(MaxNodeIDLength) <<"SN"<<"  |  "<< setw(MaxNodeIDLength) <<"EN"<<"  |  "<< setw(16) <<"Scaled Flow Rate"<<"  |  " << setw(10) <<"Flow Rate" <<"  |  "<< setw(10) <<"  Velocity  |";
    if(GFflag)	stream<<"       "<< setw(1) <<"G"<<"       |       " << setw(1) <<"F"<<"       |";
    stream<<endl;
    stream <<internal<<"| " << setw(MaxPipeIDLength) <<"-"<<" |  " << setw(MaxNodeIDLength) <<"-"<<"  |  "<< setw(MaxNodeIDLength) <<"-"<<"  |  "<< setw(16) <<"-"<<"  |  " << setw(10) <<"(CMS)" <<"  |  "<< setw(10) <<"(m/s)" <<"  |";
    if(GFflag)	stream<<"       -       |       -       |  ";
    stream<<endl;
     
    for(int i=0;i<65+MaxPipeIDLength+2*MaxNodeIDLength;i++) stream<<"-";
    if(GFflag)	for(int i=0;i<32;i++) stream<<"-";
    stream<<endl;
    for(int i = 0; i < np; i++){
    	stream<<"| " <<right<< scientific<< setprecision(3) << setw(MaxPipeIDLength)<<(pipe->getPipeID(i))<<" |  " << setw(MaxNodeIDLength)<<(node->getNodeID((*SN)[i]))<<"  |  " << setw(MaxNodeIDLength)<<(node->getNodeID((*EN)[i]))
    	<<"  |     "<< setw(10) <<qsol[i]/qScale<<"     |  " << setw(10) <<qsol[i]<<"  |  " << setw(10) <<qsol[i]/(PI/4*qScale*(*D)[i]*(*D)[i])<<"  |  ";
    	if(GFflag)	stream<< scientific<< setprecision(3)<< setw(11)<<G[i] <<"  |  "<< setw(11)<<F[i] <<"  |"; 
    	stream<<endl;
    } 
    for(int i=0;i<65+MaxPipeIDLength+2*MaxNodeIDLength;i++) stream<<"-";
    if(GFflag)	for(int i=0;i<32;i++) stream<<"-";
    stream<<endl;
    stream<<"\n\n";



}
//----------------------------END OF LinkResult----------------------------


//--------------------------START OF NodalResult---------------------------//
void Input::NodeResult(ostream& stream,Net* net,Parameter* Parameter,vector<double> hsol){
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
    int MaxNodeIDLength;
	  node->getMaxNodeIDLength()>2?MaxNodeIDLength=node->getMaxNodeIDLength():MaxNodeIDLength=2;
    int MaxNpIterResult = Parameter->getParametervalue("MaxNpIterResult");
    stream<<"Final Nodal Head"<<endl;
    for(int i=0;i<41+MaxNodeIDLength;i++) stream<<"-";
    stream<<endl;
    stream <<right<<"| " << setw(MaxNodeIDLength) <<"ID"  <<" |  " << "Scaled Nodal Head"<<"  |  "<< "Nodal Head"<<"  |"<<endl;
    for(int i=0;i<41+MaxNodeIDLength;i++) stream<<"-";
    stream<<endl;
    for(int i = 0 ; i < nj ; i++)
  		stream <<"| " <<right<< scientific<< setprecision(3) << setw(MaxNodeIDLength) <<(node->getNodeID(i)) <<" |      "<< setw(10) <<hsol[i]/hScale<<"     |  "<< setw(10) <<hsol[i]<<"  |"<<endl;
   	for(int i=0;i<41+MaxNodeIDLength;i++) stream<<"-";
    stream<<endl;
   	stream<<"\n\n";





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
//  calls:   0
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
void Input::StatInfo(ostream& stream,Net* net,vector<double> qsol,vector<double> hsol){
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
    
    stream<<"Statistical Information:"<<endl; 
    stream<<"--------------------------------------------------------------------------"<<endl;
    stream<<left<<"| "<<setw(7)<<""<<" |   "<<setw(11)<<"Scaled Flow"<<"  |     "<<"Flow"<<"     |  "<<"Scaled Head"<<"  |  "<<setw(10)<<"Head"<<"  |"<<endl;
    stream<<"|------------------------------------------------------------------------|"<<endl;
    stream<<left<<scientific<<setprecision(3)<<"| " <<setw(7)<<"Max"<<" |   "<<setw(11)<<qmax/qScale<<"  |  "<<setw(10)<<qmax<<"  |  "<<setw(11)<<hmax/hScale<<"  |  "<<setw(10)<<hmax<<"  |"<<endl;
    stream<<left<<scientific<<setprecision(3)<<"| " <<setw(7)<<"Min"<<" |   "<<setw(11)<<qmin/qScale<<"  |  "<<setw(10)<<qmin<<"  |  "<<setw(11)<<hmin/hScale<<"  |  "<<setw(10)<<hmin<<"  |"<<endl;
    stream<<left<<scientific<<setprecision(3)<<"| " <<setw(7)<<"Median"<<" |   "<<setw(11)<<qmedian/qScale<<"  |  "<<setw(10)<<qmedian<<"  |  "<<setw(11)<<hmedian/hScale<<"  |  "<<setw(10)<<hmedian<<"  |"<<endl;
    stream<<left<<scientific<<setprecision(3)<<"| " <<setw(7)<<"Average"<<" |   "<<setw(11)<<qAve/qScale<<"  |  "<<setw(10)<<qAve<<"  |  "<<setw(11)<<hAve/hScale<<"  |  "<<setw(10)<<hAve<<"  |"<<endl;
    stream<<"--------------------------------------------------------------------------"<<endl;
    stream<<"\n\n";  




//---------------------------END OF StatReport-----------------------------%


}

