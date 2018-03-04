#include "GGAsolver.h"
GGAsolver::GGAsolver(Net* p_net,Parameter *p_parameter,Flag* p_flag)
{
	
	qsol =	new vector<double>();
	hsol =	new vector<double>();
    net=p_net;
    parameter=p_parameter;
    flag=p_flag;

}

GGAsolver::~GGAsolver()
{	
	delete  qsol;
	delete  hsol;
    cs_sfree (pamd) ;
	delete A2el;
	delete Core;    
}


vector<double>* GGAsolver::GGAgetH(vector<double>* G,vector<double>* F,vector<double>* A2el,
								vector<double>* q,vector<int> *SN,vector<int> *EN,vector<double>* dm,string hdlss){
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
	int nj=dm->size();
	int np=q->size();
	vector<double> diag(nj);
	vector<double>* LHS=new vector<double>(nj);
	vector<map<int,double > >p(nj);
	vector<int> v;
	vector<double> value;

	vector<double> bb(nj);
	Matrix* RHS=new Matrix(nj,nj);
  	for(int i=0;i<np;i++){
  		int pSN=(*SN)[i];
  		int pEN=(*EN)[i];
  		if(pSN<nj&&pEN<nj){  
  			p[pSN][pEN]-=1.0/(*F)[i];
  			p[pEN][pSN]-=1.0/(*F)[i];
  		}
  		if(pSN<nj){
			bb[pSN]+=(((*G)[i]*(*q)[i]-modifier2*(*A2el)[i])/(*F)[i])-(*q)[i];		
  			diag[pSN]+=1.0/(*F)[i];
  		}
  		if(pEN<nj){
			bb[pEN]-=(((*G)[i]*(*q)[i]-modifier2*(*A2el)[i])/(*F)[i])-(*q)[i];
  			diag[pEN]+=1.0/(*F)[i];
  		}
   	}

   	for(int i=0;i<nj;i++)	RHS->triple(i, i, diag[i]);
   	
   	for(unsigned int i=0;i<p.size();i++)
   		for (std::map<int,double>::iterator it=p[i].begin(); it!=p[i].end(); ++it)
   	  		RHS->triple(i,it->first,it->second);
	RHS->CCS();
	for(int i=0;i<nj;i++)	(*LHS)[i]=((-modifier3*(*dm)[i]+bb[i])/modifier1);
		

	vector<double>* result=RHS->linsolve(pamd,LHS);
	delete LHS;
	delete RHS;
	return result;
}

void GGAsolver::amd(Result* result){
	PIPE* pipe=net->getPIPE();
	NODE* node=net->getNODE();
	unsigned int np=net->getNp();
	unsigned int nj=net->getNj();
	for(unsigned int i=0;i<np;i++) qsol->push_back(0.0);
	for(unsigned int i=0;i<nj;i++) hsol->push_back(0.0);
	unsigned int nf=net->getNf();
	vector<double>* dm=node->getDM();
	topology=net->getTopology();
	pRow=topology->getcorePipes(); 
	pCol=topology->getcoreNodes(); 
	result->SampleCPUCycles("AMD","start");
	Core=net->permute(pRow,pCol);
	PIPE* pipe1=Core->getPIPE();
	int NCoreNodes=pCol->size();
	int NCorepipes=pRow->size();
	cs *T,*ST;		
  	vector<int>* SN=Core->getTopology()->getSN();
  	vector<int>* EN=Core->getTopology()->getEN();
  	int x;
	T = cs_spalloc (NCoreNodes, NCoreNodes, 1, 1, 1) ; 
  	for (int i = 0 ; i < NCoreNodes ; i++) x=cs_entry (T, i, i, 2) ;
  	for(int j=0;j<NCorepipes;j++){
  		if((*SN)[j]<NCoreNodes&&(*EN)[j]<NCoreNodes){
  			x=cs_entry (T, (*SN)[j], (*EN)[j], 1);
  			x=cs_entry (T, (*EN)[j], (*SN)[j], 1);
  		}
    }
    ST = cs_compress (T) ; 
    pamd=cs_schol(1,ST) ;
    cs_spfree(T);
    cs_spfree(ST);
    
	result->SampleCPUCycles("AMD","end");

	NODE* node1=Core->getNODE();
	A2el=new vector<double>(NCorepipes);
	vector<double>* zs=node1->getZS();
	for(int i=0;i<NCorepipes;i++){
		if((*SN)[i]>=NCoreNodes)			(*A2el)[i]+=(*zs)[(*SN)[i]-NCoreNodes];
		if((*EN)[i]>=NCoreNodes)			(*A2el)[i]-=(*zs)[(*EN)[i]-NCoreNodes];
		
	}
}


void GGAsolver::runH(Result* result){
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
	result->SampleCPUCycles("Pre-other","start");
	PIPE* pipe=Core->getPIPE();
	NODE* node=Core->getNODE();
	Topology* topology=Core->getTopology();
	vector<double>* length=pipe->getL();
	vector<double>* diameter=pipe->getD();
	vector<double>* roughness=pipe->getR();
	vector<int> 	*SN=topology->getSN(),
					*EN=topology->getEN();
    string unit=net->getUnit();
	int nj=Core->getNj();
	int np=Core->getNp();
	double Eres,Cres;
	unsigned iterator;

	vector<double>* dm=node->getDM();
	string hdlss=Core->getHd();
	unsigned maxIter=parameter->getParametervalue("maxIter");
	string TerMsg;
	vector<double>  *G=new vector<double>(np),
					*F=new vector<double>(np);	
	result->SampleCPUCycles("Pre-other","end");
	q 	 =	new vector<double>(np);
	h 	 =	new vector<double>(nj);
		
	result->SampleCPUCycles("init","start");	
	double initV=parameter->getParametervalue("initV");
	initQH(diameter,initV,unit,1,nj,q,h);
    //result->setQHinit(q,h);  
	result->SampleCPUCycles("init","end");
    double norm;
    result->SampleCPUCycles("GetGF-1","start");
	vector<double>* rf=getRF(length,roughness,diameter,hdlss,unit);
	result->SampleCPUCycles("GetGF-1","end");
	result->SampleCPUCycles("iter","start");
	vector<double>* qnew=new vector<double>(np);
	for(iterator=0;iterator<maxIter;iterator++)
	{  
		vector<double>* hnew;
		result->SampleCPUCycles("getGF-2","start");
		if(hdlss.compare("DW")==0)		getDWGF(rf,diameter,roughness,q,visco,unit,G,F);
  		else if(hdlss.compare("HW")==0)	getHWGF(rf,q,G,F);
		result->SampleCPUCycles("getGF-2","end");
		result->SampleCPUCycles("linear solver","start");
		hnew=GGAgetH(G,F,A2el,q,SN,EN,dm,hdlss);
		result->SampleCPUCycles("linear solver","end");
		result->SampleCPUCycles("second phase","start");
		vector<double> A1h(np);
		for(int i=0;i<np;i++){
			A1h[i]=(*A2el)[i];
  			if((*SN)[i]<nj)
				A1h[i]+=(*hnew)[(*SN)[i]];
  			if((*EN)[i]<nj)
				A1h[i]-=(*hnew)[(*EN)[i]];
   		}
   		for(int i=0;i<np;i++)				
   			(*qnew)[i]=(*q)[i]+(modifier1*A1h[i]-(*G)[i]*(*q)[i])/(*F)[i];
		result->SampleCPUCycles("second phase","end");
		result->SampleCPUCycles("normTest","start");
			norm=getnorm(qnew,q,hnew,h,parameter->getParametervalue("StopTest"),parameter->getParametervalue("NormTyp"));
		result->SampleCPUCycles("normTest","end");
		if(flag->getFlagvalue("ConvergenceFlag")){
			vector<double> *EresI=new vector<double>(np);
			vector<double> *CresI=new vector<double>(nj);
			for(int i = 0;i<np; i++){
				(*EresI)[i]=(*G)[i]*(*q)[i]-modifier1*A1h[i];
				if((*SN)[i]<nj) (*CresI)[(*SN)[i]]+=(*q)[i];
				if((*EN)[i]<nj) (*CresI)[(*EN)[i]]-=(*q)[i];
			}			
			for(int i=0;i<nj;i++)
				(*CresI)[i]+=(*dm)[i]*modifier3;
			Eres=NORM(EresI,3);
			Cres=NORM(CresI,3);
			delete EresI;
			delete CresI;
		}
		for(int i=0;i<np;i++) (*q)[i]=(*qnew)[i];
		for(int i=0;i<nj;i++) (*h)[i]=(*hnew)[i];
		if(flag->getFlagvalue("QitersFlag"))  result->setPipeIterResult(iterator,q,G,F,qScale,Gscale);
		if(flag->getFlagvalue("HitersFlag"))  result->setNodeIterResult(iterator,h,hScale);
		//printf(".");
		
		result->setIterNorm(norm,Cres,Eres);
		
		delete hnew;
		if (norm<=parameter->getParametervalue("StopTol")) {
			TerMsg="The Hydraulic Sover (GGA) satisfied the convergence test after ";
			break;
		}
		if(iterator>=5){
			if (MinInprov(parameter,result->getIterNorm())){
				TerMsg="The Hydraulic Sover (GGA) converged without satisfying the stopping test after ";		
				break;
			}
		}
	} 
	result->SampleCPUCycles("iter","end");
	//printf("\n%s%d iterators\n",TerMsg.c_str(),iterator+1);
	result->SampleCPUCycles("undoPermutation","start");	  
	for(unsigned i=0;i<pCol->size();i++) (*hsol)[(*pCol)[i]]=(*h)[i]*hScale;
	for(unsigned i=0;i<pRow->size();i++) (*qsol)[(*pRow)[i]]=(*q)[i]*qScale;
	result->SampleCPUCycles("undoPermutation","end");	
  	delete rf;
  	delete qnew;
  	delete q;
  	delete h;
 	delete G;
	delete F;
}
