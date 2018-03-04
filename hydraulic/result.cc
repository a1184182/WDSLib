#include "result.h"

Result::Result(){
	/*qsol=new vector<double>();
	hsol=new vector<double>();
	qinit=new vector<double>();
	hinit=new vector<double>();
	qiter=new vector<vector<double>*>();
	hiter=new vector<vector<double>*>();*/
	//cout<<"result object created!"<<endl;
	iterator=0;
}

void Result::setQsol(vector<double>* input){
	qsol.resize(input->size());
	for(unsigned i=0;i<input->size();i++)		qsol[i]=((*input)[i]);

}

void Result::setHsol(vector<double>* input){
	hsol.resize(input->size());
	for(unsigned i=0;i<input->size();i++)	hsol[i]=(*input)[i];

}

Result::~Result(){
	//printf("result object deleted\n");
}


void Result::setIteration(int input){
		iterator=input;
	}

void Result::dispQHinit(){
	for(unsigned i=0;i<qinit.size();i++)
		printf("qinit[%d]=%f\n",i,qinit[i]);
	for(unsigned i=0;i<hinit.size();i++)
		printf("hinit[%d]=%f\n",i,hinit[i]);
}

void Result::dispQiter(){
    printf("Iterative Flows:\n"); 
    printf("-------------------------------------------------------------\n");
	for(unsigned i=0;i<qiter[0].size();i++){
		for(unsigned j=0;j<qiter.size();j++){
			printf("Q[%d]=%.4e \t",i,qiter[j][i]);
		}
		cout<<endl;
	}
    printf("-------------------------------------------------------------\n");
}

void Result::dispHiter(){
    printf("Iterative Heads:\n"); 
    printf("-------------------------------------------------------------\n");
	for(unsigned i=0;i<hiter[0].size();i++){
		for(unsigned j=0;j<hiter.size();j++){
			printf("h[%d]=%.4e \t",i,hiter[j][i]);
		}
		cout<<endl;
	}
    printf("-------------------------------------------------------------\n");
}

void Result::setGFfinal(vector<double>* G,vector<double>* F,double Gscale){
	for(unsigned i=0;i<qinit.size();i++){
		Gfinal.push_back((*G)[i]*Gscale);
		Ffinal.push_back((*F)[i]*Gscale);
	}
}
        
void Result::setQHinit(vector<double>* qi,vector<double>* hi){
	for(unsigned i=0;i<qi->size();i++)
		qinit.push_back((*qi)[i]);
	for(unsigned i=0;i<hi->size();i++)
		hinit.push_back((*hi)[i]);
}

	

void Result::setPipeIterResult(int iterator,vector<double>* q,vector<double>* G,vector<double>* F,
							double qScale,double Gscale){
	qiter.push_back(vector<double>());
	cout<<"HAHA"<<endl;
	Giter.push_back(vector<double>());
	Fiter.push_back(vector<double>());
	for(unsigned i=0;i<q->size();i++){
		qiter[iterator].push_back((*q)[i]*qScale);
		Giter[iterator].push_back((*G)[i]*Gscale);
		Fiter[iterator].push_back((*F)[i]*Gscale);
	}
}

void Result::setNodeIterResult(int iterator,vector<double>* h,double hScale){
	hiter.push_back(vector<double>());
	for(unsigned i=0;i<h->size();i++)
		hiter[iterator].push_back((*h)[i]*hScale);
}
    
void Result::setIterNorm(double norm,double cRes,double eRes)
{
	normIter.push_back(norm);
	CresIter.push_back(cRes);
	EresIter.push_back(eRes);
}  
    
void Result::setFinalNorm(double norm,double cRes,double eRes)
{
	normFinal=norm;
	EresFinal=eRes;
	CresFinal=cRes;	
}
