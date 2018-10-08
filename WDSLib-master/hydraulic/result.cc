#include "result.h"
#include <cmath>


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

void Result::dispQiter(ostream& stream,PIPE *pipe){
	int Left,Right;
	int MaxPipeIDLength;
	  pipe->getMaxPipeIDLength()>7?MaxPipeIDLength=pipe->getMaxPipeIDLength():MaxPipeIDLength=7;
	double NumCol=(15.0*iterator-10.0)/2.0;
	if(NumCol==ceil(NumCol)){
		Left=ceil(NumCol);
		Right=ceil(NumCol);
	}else{
		Left=ceil(NumCol)-1;
		Right=ceil(NumCol);
	}

	stream<<("=================\n");
    stream<<("|Iterative Flows|\n"); 
	stream<<("=================\n");
    for(int i=0;i<15*iterator+MaxPipeIDLength;i++) stream<<"-";
    stream<<endl;
	stream<<setw(MaxPipeIDLength)<<" "<<"|"<<setw(Left)<<""<<"Flow Rates"<<setw(Right)<<"|"<<endl;
	stream<<setw(MaxPipeIDLength)<<"Pipe ID"<<"|";
		for(unsigned j=0;j<iterator;j++)
			stream<<left<<" "<<setw(11)<<"Iterations "<<setw(2)<<j+1<<"|";
		stream<<endl;
    for(int i=0;i<15*iterator+MaxPipeIDLength;i++) stream<<"-";
    stream<<endl;
	for(unsigned i=0;i<qiter[0].size();i++){
	stream<<right<<setw(MaxPipeIDLength)<<pipe->getPipeID(i)<<"|";
		for(unsigned j=0;j<iterator;j++)  stream<<right<< scientific<< setprecision(3) <<"  "<<setw(10)<<qiter[j][i]<<"  |";
		stream<<endl;
	}
    for(int i=0;i<15*iterator+MaxPipeIDLength;i++) stream<<"-";
    stream<<endl;
	stream<<"\n\n\n";
}

void Result::dispHiter(ostream& stream,NODE* node){
	int Left,Right;
	int MaxNodeIDLength;
	  node->getMaxNodeIDLength()>7?MaxNodeIDLength=node->getMaxNodeIDLength():MaxNodeIDLength=7;
    
	 
	double NumCol=(15.0*iterator-10.0)/2.0;
	if(NumCol==ceil(NumCol)){
		Left=ceil(NumCol);
		Right=ceil(NumCol);
	}else{
		Left=ceil(NumCol)-1;
		Right=ceil(NumCol);
	}
	stream<<("=================\n");
    stream<<("|Iterative Heads|\n"); 
	stream<<("=================\n");
    for(int i=0;i<15*iterator+MaxNodeIDLength;i++) stream<<"-";
    stream<<endl;
	stream<<setw(MaxNodeIDLength)<<" "<<"|"<<setw(Left)<<""<<"Node Heads"<<setw(Right)<<"|"<<endl;
	stream<<setw(MaxNodeIDLength)<<"Node ID"<<"|";
		for(unsigned j=0;j<iterator;j++)
			stream<<left<<" "<<setw(11)<<"Iterations "<<setw(2)<<j+1<<"|";
    stream<<endl;

    for(int i=0;i<15*iterator+MaxNodeIDLength;i++) stream<<"-";
    stream<<endl;


	for(unsigned i=0;i<hiter[0].size();i++){
	stream<<right<<setw(MaxNodeIDLength)<<node->getNodeID(i)<<"|";
		for(unsigned j=0;j<iterator;j++)
			stream<<right<< scientific<< setprecision(3) <<"  "<<setw(10)<<hiter[j][i]<<"  |";
		stream<<endl;
	}

    for(int i=0;i<15*iterator+MaxNodeIDLength;i++) stream<<"-";
    stream<<endl;

	stream<<"\n\n\n";
}

void Result::setGFfinal(vector<double>* G,vector<double>* F){
	for(unsigned i=0;i<G->size();i++){
		Gfinal.push_back((*G)[i]);
		Ffinal.push_back((*F)[i]);
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
    
void Result::setIterNorm(double norm)
{
	normIter.push_back(norm);
}  

void Result::setIterResidual(double cRes, double eRes){
	CresIter.push_back(cRes);
	EresIter.push_back(eRes);
}
    
void Result::setFinalNorm(double cRes,double eRes)
{
	normFinal=normIter[normIter.size()-1];
	EresFinal=eRes;
	CresFinal=cRes;	
}
