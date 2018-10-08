#include "solver.h"
#include <iomanip> 
#include <cstring>
#include <fstream>


vector<double>* Solver::getRF(vector<double>* length,vector<double>* roughness,vector<double>* diameter,string hdlss,string unit){
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
	vector<double>* output = new vector<double>();		
	if(hdlss.compare("HW")==0){	
		const double B2=4.87037037037037037037037037037;
		const double n =1.85185185185185185185185185185;
    	for(unsigned int i=0;i<length->size();i++)		
    		output->push_back(10.67*(*length)[i]/pow((*roughness)[i],n)/pow((*diameter)[i],B2));
	}else if(hdlss.compare("DW")==0){
		const double C2=0.81056946913870220328135474119335;
		double g;
		if(unit.compare("US")==0)		g=32.2;  //EPANET value
		else if(unit.compare("SI")==0)	g=32.2/3.28;  //EPANET value
    	for(unsigned int i=0;i<length->size();i++)
			output->push_back(C2/g*(*length)[i]/pow((*diameter)[i],5));
	}
	return output;
}



void Solver::getDWGF(vector<double>* rf,vector<double>* diameter,vector<double>* roughness,vector<double> *q,double nu,string unit,vector<double>* G,vector<double>* F){
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
	int 	np=diameter->size();
	double 	a=PI16*nu; 
	double 	bb=PI4*nu; 
	double 	c=5.74*pow((PI4*nu),(0.90)); 
	double 	*Re = (double*) malloc(np*sizeof(double));
	double 	*alfa=(double*)malloc(ALFCOLS*sizeof(double));
	double 	*beta=(double*)malloc(ALFCOLS*sizeof(double));
 	double 	cc=9*c/5;
	double 	th;
	double 	th1;
	double 	ddq;
	double 	th_hat;
	double 	lnt;
	double 	lnt2;
	double 	lnt3;
	double 	rq;
	double 	rdq;
	double 	mu;

	for(int i=0;i<np;i++){
	//4/PI can be replaced
		Re[i]=abs((*q)[i])/(*diameter)[i]/bb;
		if(Re[i]<=2000){
			(*G)[i]=a*(*rf)[i]*(*diameter)[i];
			(*F)[i]=(*G)[i];
			continue;
		}
    	ddq=pow((*diameter)[i]/abs((double)(*q)[i]),0.9);
    	//roughness/diameter can be replaced
		th1=((b*(*roughness)[i])/(*diameter)[i]);
		th=th1+c*ddq;
		// turbulent flow
		if(Re[i]>=4000){
			double lth=log(th);
			rq=(*rf)[i]*abs((*q)[i])/(pow(lth,2))*opttf;
			rdq=(cc/lth)*ddq/th;
			(*G)[i]=rq;
			(*F)[i]=rq*(2+rdq);
		}else{
			// transitional flow
			mu=Re[i]/2000.0;
			th_hat=th1+Re2;
			lnt=log(th_hat); 
			lnt2=lnt*lnt; 
			lnt3=lnt2*lnt; 
			alfa[0] =          0.6627356825720859e+1/(lnt2);
			beta[0] =         -0.7846938809192028e-2/(lnt3);

			alfa[1] = 0.128   -0.1590565638173006e+2/(lnt2);
			beta[1] =          0.1961734702298007e-1/(lnt3);

			alfa[2] =-0.128   +0.1192924228629755e+2/(lnt2);
			beta[2] =         -0.1569387761838406e-1/(lnt3);

			alfa[3] = 0.032   -0.2650942730288344e+1/(lnt2);
			beta[3] =          0.3923469404596014e-2/(lnt3);

			rq=(*rf)[i]*abs((*q)[i])*((alfa[0]+beta[0]/th)+
					(alfa[1]+beta[1]/th)*mu+
                    (alfa[2]+beta[2]/th)*pow(mu,2.0)+
                    (alfa[3]+beta[3]/th)*pow(mu,3.0));
			//diagonal of G is RQ
			 (*G)[i]=rq;

			//now calculate F out of rq1
			// calculate the sum term.
			double fsum=0.0;
			 for (int k=0;k<ALFCOLS;k++)
				fsum += ((9*c/10.0)*(beta[k]/pow(th,2.0))*pow(abs((*diameter)[i]/(*q)[i]),0.9)+
						(2+k)*(alfa[k]+beta[k]/th))*pow(mu,k);
       
			(*F)[i]=(*rf)[i]*abs((*q)[i])*fsum;
	 	}     
  	}

  	free(Re);
  	free(alfa);
  	free(beta);
}
  

void Solver::getHWGF(vector<double>* rf,vector<double>* q,vector<double>* G,vector<double>* F){
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
	const double n =1.85185185185185185185185185185;
  	for(unsigned int i=0;i<q->size();i++){
        (*G)[i]=(*rf)[i]*pow(fabs((*q)[i]),n-1.0);
	    (*F)[i]=(*G)[i]*n;
  	}
}



void Solver::reverseFCPA(Result* result,Topology* topology){
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
	double qcf=net->getQCF();
	result->SampleCPUCycles("reverseFCPA","start");	
	vector< vector<pair<int,int> > > *forestpipes=topology->getforestPipes();
	if(forestpipes->empty()){
		result->SampleCPUCycles("reverseFCPA","end");
		return;
	}	
	vector<int> *rootNodes=topology->getrootNodes();
	vector<int> 	*SN=topology->getSN(),
					*EN=topology->getEN();
	int Nforest=topology->getNforest();
	PIPE* pipe=net->getPIPE();
	NODE* node=net->getNODE();
	int nj=net->getNj();
	vector<double>* zs=node->getZS();
	int counter=0;
	vector<double>* length=pipe->getL();
	vector<double>* diameter=pipe->getD();
	vector<double>* roughness=pipe->getR();
	vector<double>* dm=node->getDM();
	vector<double> *pipeL=new vector<double>(Nforest);
	vector<double> *pipeD=new vector<double>(Nforest);
	vector<double> *pipeR=new vector<double>(Nforest);
	vector<double> *q=new vector<double>(Nforest);
	vector<double>  *G=new vector<double>(Nforest),
					*F=new vector<double>(Nforest);
	string hdlss=net->getHd();
	string unit =net->getUnit();

	for(int i=forestpipes->size()-1;i>=0;i--){
		for(int j=(*forestpipes)[i].size()-1; j>=0;j--){
			int currentPipe=(*forestpipes)[i][j].first;
			int currentNode=(*forestpipes)[i][j].second;
			(*pipeL)[counter]=(*length)[currentPipe]*Lscale;
			(*pipeD)[counter]=(*diameter)[currentPipe]*Dscale;
			(*pipeR)[counter]=(*roughness)[currentPipe]*Rscale;
			if((*SN)[currentPipe]==currentNode)	(*qsol)[currentPipe]=-(*dm)[currentNode]*DMscale/qcf;
			else if((*EN)[currentPipe]==currentNode)	(*qsol)[currentPipe]=(*dm)[currentNode]*DMscale/qcf;
			(*q)[counter]=(*qsol)[currentPipe];
			counter++;
		}
	}
	vector<double>* rf=getRF(pipeL,pipeR,pipeD,hdlss,unit);
	if(hdlss.compare("DW")==0)		getDWGF(rf,pipeD,pipeR,q,visco,unit,G,F);
  	else if(hdlss.compare("HW")==0)	getHWGF(rf,q,G,F);
	counter=0;
	for(int i=forestpipes->size()-1;i>=0;i--){
		for(int j=(*forestpipes)[i].size()-1; j>=0;j--){
			int currentPipe=(*forestpipes)[i][j].first;
			(*Gfinal)[currentPipe]=(*G)[counter];
			(*Ffinal)[currentPipe]=(*F)[counter];
			counter++;
		}
	}
	counter=0;
	for(int i=forestpipes->size()-1;i>=0;i--){
		int rootNode=(*rootNodes)[i]; 
		for(int j=(*forestpipes)[i].size()-1; j>=0;j--){
			int currentPipe=(*forestpipes)[i][j].first;
			int currentNode=(*forestpipes)[i][j].second;
			if(j==(*forestpipes)[i].size()-1){
				if(rootNode>nj)	(*hsol)[currentNode]=(*zs)[rootNode-nj]*Zscale-(*G)[counter]*abs((*q)[counter]);
				else			(*hsol)[currentNode]=(*hsol)[rootNode]-(*G)[counter]*abs((*q)[counter]);
			}else{
				int previousNode=(*forestpipes)[i][j+1].second;
				(*hsol)[currentNode]=(*hsol)[previousNode]-(*G)[counter]*abs((*q)[counter]);
			}
			counter++;
		}
	}
	result->SampleCPUCycles("reverseFCPA","end");
	delete pipeL;
	delete pipeD;
	delete pipeR;
	delete q;
	delete rf;
	delete G;
	delete F;
 }

void Solver::reverseH(Result *result){
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
   int SolverFlag=flag->getFlagvalue("SolverFlag");
	bool FCPAFlag=flag->getFlagvalue("FCPAFlag");
  	if(FCPAFlag){	
		reverseFCPA(result,topology);
	}
  	result->setQsol(qsol);
	result->setHsol(hsol);
	result->setGFfinal(Gfinal,Ffinal);
	double qcf=net->getQCF();
	vector<int> 	*SN = net->getTopology()->getSN(),
					*EN = net->getTopology()->getEN();
	vector<double>* dm=net->getNODE()->getDM();
	vector<double>* zs=net->getNODE()->getZS();
	int nj=net->getNj();
	int np=net->getNp();
	vector<double> A1h(np);

	for(int i=0;i<np;i++){
		if((*SN)[i]>=nj)			A1h[i]+=(*zs)[(*SN)[i]-nj]*Zscale;
		if((*EN)[i]>=nj)			A1h[i]-=(*zs)[(*EN)[i]-nj]*Zscale;
	}

	for(int i=0;i<np;i++){
 		if((*SN)[i]<nj)	A1h[i]+=(*hsol)[(*SN)[i]];
 		if((*EN)[i]<nj)	A1h[i]-=(*hsol)[(*EN)[i]];
	}
   		vector<double> *EresI=new vector<double>(np);
		vector<double> *CresI=new vector<double>(nj);
		for(int i = 0;i<np; i++){
			(*EresI)[i]=(*Gfinal)[i]*(*qsol)[i]-A1h[i];
			if(abs((*EresI)[i])>1) cout<<i<<"\t"<<(*Gfinal)[i]*(*qsol)[i]<<"\t"<<-A1h[i]<<endl;
		}		
		for(int i=0;i<pRow->size();i++){
			if((*SN)[(*pRow)[i]]<nj) (*CresI)[(*SN)[(*pRow)[i]]]+=(*qsol)[(*pRow)[i]];
			if((*EN)[(*pRow)[i]]<nj) (*CresI)[(*EN)[(*pRow)[i]]]-=(*qsol)[(*pRow)[i]];	
		}
		for(int i=0;i<pCol->size();i++)
			(*CresI)[(*pCol)[i]]+=(*dm)[(*pCol)[i]]*DMscale/qcf;
		result->setFinalNorm(NORM(CresI,3),NORM(EresI,3));
		delete EresI;
		delete CresI;
}


void Solver::initQH(vector<double> *diameter,double V,string unit,int Algorithm,
					int nj,vector<double>* q,vector<double>* h){
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
	int size;
	if(unit.compare("US")==0)	V=V/0.3048;
	if(Algorithm==2)			for(unsigned int i=0;i<q->size();i++)	(*q)[i]=V*PI/4*pow((*diameter)[nj+i],2);
	else if (Algorithm==1) 	for(unsigned int i=0;i<q->size();i++)	(*q)[i]=V*PI/4*pow((*diameter)[i],2);
 	for(unsigned int i=0;i<nj;i++)	(*h)[i]=0.0;
} 

void Solver::getscale(int Algorithm){
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
	net->scale();
	PIPE* pipe=net->getPIPE();
	NODE* node=net->getNODE();
	double qcf=net->getQCF();
	Lscale=pipe->Lenscale();
	string unit=net->getUnit();
	Dscale=pipe->Diascale();
	Rscale=pipe->Roughscale();
	Zscale=node->ELscale();
	DMscale=node->DMscale();
	Gscale=pipe->GFscale();
	qScale=Dscale*Dscale;
	hScale=Zscale;
	if(unit.compare("US")==0) visco=1.1E-5*Dscale/qScale;
	else if(unit.compare("SI")==0)	visco=1.1E-5/pow(3.28,2)*Dscale/qScale;
	if (Algorithm==1){
		modifier1=hScale/Gscale/qScale;
		modifier2=Zscale/Gscale/qScale;
		modifier3=DMscale/qScale/qcf;
	}else if (Algorithm==2){
		modifier1=hScale/Gscale/qScale;
		modifier2=1;//qScale;
		modifier3=DMscale/qScale/qcf;	
		modifier4=DMscale/qScale/qcf;		
	}
}

double Solver::NORM(vector<double>* Input,int NormTyp){
	double _norm=0;
	switch(NormTyp){
				case 1:
					for(unsigned i=0;i<Input->size();i++)	_norm += abs((*Input)[i]);
					break;
				case 2:
					for(unsigned i=0;i<Input->size();i++)  _norm = _norm+pow((*Input)[i],2);
						_norm=sqrt(_norm);
					break;					
				case 3:
					double max=0;
					for(unsigned i=0;i<Input->size();i++)
						if(abs((*Input)[i])>max)
							max=abs((*Input)[i]);
					_norm=max;
					break;
	}
	return _norm;
}

double Solver::getnorm(vector<double>* qnew,vector<double>* q,vector<double>* hnew,
	vector<double>* h,int StopTest,const int NormTyp){
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
	double normDiff=0;
	vector<double>* diff=new vector<double>();
	vector<double>* denominator=new vector<double>(); 
	switch(StopTest){
		case 1:
			for(unsigned i=0;i<qnew->size();i++){
				diff->push_back(((*qnew)[i]-(*q)[i]));
				denominator->push_back((*qnew)[i]);
			}
			normDiff=NORM(diff,NormTyp)/NORM(denominator,NormTyp);
			break;
		case 2:
			for(unsigned i=0;i<hnew->size();i++){
				diff->push_back((*hnew)[i]-(*h)[i]);
				denominator->push_back((*hnew)[i]);
			}
			normDiff=NORM(diff,NormTyp)/NORM(denominator,NormTyp);
			break;
		case 3:
			for(unsigned i=0;i<qnew->size();i++){
				diff->push_back((*qnew)[i]-(*q)[i]);
				denominator->push_back((*qnew)[i]);
			}
			for(unsigned i=0;i<hnew->size();i++){
				diff->push_back((*hnew)[i]-(*h)[i]);
				denominator->push_back((*hnew)[i]);
			}
			normDiff=NORM(diff,NormTyp)/NORM(denominator,NormTyp);
			break;
	}
	delete diff;
	delete denominator;
	return normDiff;
}

bool Solver::MinInprov(Parameter* parameter,vector<double> norm){
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
	double acc[5]={-0.2,-0.1,-6.93889390390723e-018,0.1,0.2};
	if(norm.size()<5)
		return false;
	else if(norm.size()>=5){
		double sum=0;
		for(int i=0;i<5;i++)	sum=sum+norm[norm.size()-5+i]*acc[i];
		if(abs(sum)<=parameter->getParametervalue("MinImproTol")) return true;
	}
	return false;
}




/*
void Solver::GMPAsolver(Net* net,Parameter* parameter,Flag* flag){
	cout<<"GMPAsolver not developed!"<<endl;
}


void Solver::PDMsolver(Net* net,Parameter* parameter,Flag* flag){
	
}*/