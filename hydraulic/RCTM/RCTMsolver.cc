#include "RCTMsolver.h"


RCTMsolver::RCTMsolver(Net *p_net,Parameter *p_parameter,Flag* p_flag)
{
	qsol =	new vector<double>();
	hsol =	new vector<double>();
	net=p_net;
	parameter=p_parameter;
	flag=p_flag;
}

RCTMsolver::~RCTMsolver()
{
	delete  qsol;
	delete  hsol;
	delete Core;
	delete T1Tdm;
	delete a2;
	delete a1;
	cs_sfree(pamd);    
}

vector<double>* RCTMsolver::CotreeFlow(Matrix* L21,vector<double> *F,vector<double> *G,int nj,
				vector<double> *q,vector<double> *dm){
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

	int size = F->size() - nj;
	vector<double> 	*F1=new vector<double>(nj),
					*F2=new vector<double>(size),
					*FG1=new vector<double>(nj),
					*FG2=new vector<double>(size);
	vector<double> *RHS=new vector<double>(size);
	vector<double> *F1T1Tdm=new vector<double>(nj);
	Matrix* LHS;
	Matrix* L21T=L21->transpose();
	for(int i=0;i<nj;i++){
		(*F1)[i]=((*F)[i]);
		(*F1T1Tdm)[i]=((*F)[i]*(*T1Tdm)[i]);
		(*FG1)[i]=(((*F)[i]-(*G)[i])*(*q)[i]);
	}
	for(unsigned int i=nj;i<F->size();i++){
		(*F2)[i-nj]=((*F)[i]);
		(*FG2)[i-nj]=(((*F)[i]-(*G)[i])*(*q)[i]);
	}	vector<double>* RHS1=(*L21)*FG1;
	vector<double>* RHS2=(*L21)*F1T1Tdm;
	for(unsigned int i=0;i<RHS1->size();i++) (*RHS)[i]=((*RHS1)[i]+(*FG2)[i]+(*a2)[i]*modifier1+modifier4*(*RHS2)[i]);
	Matrix* L21F=L21->bitwise(F1,2);
	Matrix* LHS1=(*L21F)*L21T; 
	Matrix* LHS2=new Matrix(size,size);
	for(unsigned int i=0;i<F2->size();i++) LHS2->triple(i,i,(*F2)[i]);
	LHS2->CCS();
	LHS=*LHS1+LHS2;
	vector<double>* output=LHS->linsolve(pamd,RHS);
	delete F1;
	delete F2;
	delete FG1;
	delete FG2;
	delete RHS;
	delete F1T1Tdm;
	delete L21T;

	delete RHS1;
	delete RHS2;
	delete L21F;
	delete LHS;
	delete LHS1;
	delete LHS2;
	return output;
}

vector<double>* RCTMsolver::SpanningtreeFlow(Matrix* L21,const vector<double>* qCt){
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
	Matrix* L21T = L21->transpose();
	vector<double>* qST=new vector<double>();
	vector<double>* L21Tqc=(*L21T)*qCt;
	for(unsigned int i=0;i<T1Tdm->size();i++) qST->push_back((*L21Tqc)[i]-modifier3*(*T1Tdm)[i]);
	delete L21T;
	delete L21Tqc;
	return qST;
}


void RCTMsolver::amd(Result* result){
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
	PIPE* pipe=net->getPIPE();
	NODE* node=net->getNODE();
	unsigned int np=net->getNp();
	unsigned int nj=net->getNj();
	for(unsigned int i=0;i<np;i++) qsol->push_back(0.0);
	for(unsigned int i=0;i<nj;i++) hsol->push_back(0.0);
	unsigned int nf=net->getNf();
	int SolverFlag=flag->getFlagvalue("SolverFlag");
	bool FCPAFlag=flag->getFlagvalue("FCPAFlag");
	//double qcf=net->getQCF();
	vector<double>* dm=node->getDM();
	//for(int i=0;i<dm->size();i++) (*dm)[i]=(*dm)[i]/qcf;
  	topology=net->getTopology();
	result->SampleCPUCycles("AMD","start");	
	pCol=topology->returnNIIC();
	pRow=topology->returnPIIC();
	Matrix *KeyMatrix = topology->getL21();	
	Matrix *KeyMatrixT=KeyMatrix->transpose();
	Core=net->permute(pRow,pCol);
	Matrix *KeyMatrixTKeyMatrix=*KeyMatrix*KeyMatrixT;
    pamd=KeyMatrixTKeyMatrix->amd() ;
	delete KeyMatrixT;
    delete KeyMatrixTKeyMatrix;
    result->SampleCPUCycles("AMD","end");
	NODE* node1=Core->getNODE();
	PIPE* pipe1=Core->getPIPE();
	vector<double>* zs=node1->getZS();
	dm=node1->getDM();
	Matrix *T1  = topology->getT1();
	Matrix* A2=topology->getA2();
	a1=new vector<double>(Core->getNj());
	T1Tdm=T1->fTSub(dm);
	vector<double>*  A2el=*A2 * zs;
	for(int i=0;i<Core->getNj();i++) (*a1)[i]=((*A2el)[i]);
	a2=*KeyMatrix*a1;
	for(int i=0;i<np-nj;i++) (*a2)[i]=(*a2)[i]+(*A2el)[i+Core->getNj()];	
	delete  A2el;

}


void RCTMsolver::runH(Result* result){
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
	double norm;
	string TerMsg;
	unsigned iterator;
	unsigned maxIter=parameter->getParametervalue("maxIter");
	string hdlss=Core->getHd();
	string unit=Core->getUnit();

	PIPE* pipe=Core->getPIPE();
	NODE* node=Core->getNODE();
	int nj = Core->getNj();
	int np = Core->getNp();

	vector<double>* length=pipe->getL();
	vector<double>* diameter=pipe->getD();
	vector<double>* roughness=pipe->getR();

	vector<double> *qinit_ctree = new vector<double>(np-nj);
	vector<double> *qinit_tree;
	qinit = new vector<double>();
	hinit = new vector<double>(nj);
	vector<double>* dm = node->getDM();
	vector<double>* zs = node->getZS();
	Matrix *L21 = topology->getL21();
	Matrix *T1  = topology->getT1();
	Matrix* L21T = L21->transpose();
	
	vector<double>  *G=new vector<double>(np),
					*F=new vector<double>(np);	
	for(int i=0;i<np;i++){
		(*G)[i]=0;
		(*F)[i]=0;
	}
	vector<double>* qnow=new vector<double>(np);
	vector<double>* qnext=new vector<double>(np);
	vector<double> *qCt,
				   *qSt;
	result->SampleCPUCycles("Pre-other","end");
	result->SampleCPUCycles("init","start");

	double initV=parameter->getParametervalue("initV");
	initQH(diameter,initV,unit,2,nj,qinit_ctree,hinit);
	qinit_tree=SpanningtreeFlow(L21,qinit_ctree);	
	for(unsigned int i=0;i<qinit_tree->size();i++) qinit->push_back((*qinit_tree)[i]);
	for(unsigned int i=0;i<qinit_ctree->size();i++) qinit->push_back((*qinit_ctree)[i]);
	for(int i=0;i<np;i++) (*qnow)[i]=(*qinit)[i];

	//result->setQHinit(qinit,hinit);  
	result->SampleCPUCycles("init","end");
	
	result->SampleCPUCycles("GetGF-1","start");
	vector<double>* rf=getRF(length,roughness,diameter,hdlss,unit);
	result->SampleCPUCycles("GetGF-1","end");
	result->SampleCPUCycles("iter","start");
	delete qinit_ctree;
	delete qinit_tree;
	delete qinit;
	delete hinit;

	for(iterator=0;iterator<maxIter;iterator++){

		result->SampleCPUCycles("getGF","start");
		if(hdlss.compare("DW")==0)		getDWGF(rf,diameter,roughness,qnow,visco,Core->getUnit(),G,F);
  		else if(hdlss.compare("HW")==0)	getHWGF(rf,qnow,G,F);
		result->SampleCPUCycles("getGF","end");

		result->SampleCPUCycles("linear solver","start");
		qCt=CotreeFlow(L21,F,G,nj,qnow,dm);
		result->SampleCPUCycles("linear solver","end");


		result->SampleCPUCycles("second phase","start");
		qSt=SpanningtreeFlow(L21,qCt);
		result->SampleCPUCycles("second phase","end");
		
		for(unsigned int i=0;i<qSt->size();i++) (*qnext)[i]=(*qSt)[i];
		for(unsigned int i=0;i<qCt->size();i++) (*qnext)[qSt->size()+i]=(*qCt)[i];

		result->SampleCPUCycles("normTest","start");
		norm=getnorm(qnext,qnow,qnext,qnow,parameter->getParametervalue("StopTest"),1);
		result->SampleCPUCycles("normTest","end");
		for(unsigned int i=0;i<qnext->size();i++) (*qnow)[i]=(*qnext)[i];
		delete qCt;
		delete qSt;	
		if(flag->getFlagvalue("QitersFlag"))  result->setPipeIterResult(iterator,qnow,G,F,qScale,Gscale);
		result->setIterNorm(norm,NULL,NULL);
//		cout<<".";
		if (norm<=parameter->getParametervalue("StopTol")) {
			TerMsg="The Hydraulic Sover (RCTM) satisfied the convergence test after ";
			break;
		}
		else if (MinInprov(parameter,result->getIterNorm())){
			TerMsg="The Hydraulic Sover (RCTM) converged without satisfying the stopping test after ";		
			break;
		}
	}

		result->SampleCPUCycles("iter","end");
//	printf("\n%s%d iterators\n",TerMsg.c_str(),iterator+1);
	vector<double> *aaa=new vector<double>();
	result->SampleCPUCycles("reverseRCTM","start");	
	for(int i=0;i<nj;i++) aaa->push_back((*G)[i]*(*qnow)[i]*Gscale*qScale-Zscale*(*a1)[i]);
	vector<double>* hfinal=T1->fSub(aaa);
	result->SampleCPUCycles("reverseRCTM","end");	


	result->setIteration(iterator+1);
	result->SampleCPUCycles("undoPermutation","start");	
	for(unsigned i=0;i<pRow->size();i++) (*qsol)[(*pRow)[i]]=((*qnow)[i]*qScale);
	for(unsigned i=0;i<pCol->size();i++) (*hsol)[(*pCol)[i]]=(*hfinal)[i];
	result->SampleCPUCycles("undoPermutation","end");	

	result->setGFfinal(G,F,Gscale);
//	result->setFinalNorm(norm,NaN,NaN);
	delete hfinal;
	delete qnext;
	delete qnow;
	delete aaa;
	delete L21T;
	delete G;
	delete F;
  	delete rf;

}