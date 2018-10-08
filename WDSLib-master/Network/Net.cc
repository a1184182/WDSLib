#include <string>
#include "Net.h"

Net::Net(){
	Npipes=0;
	Njuncs=0;
	Nsources=0;
}


Net::Net(int np,int nj,int nf,string hd,string u,string uf,string up,double i_qcf){
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
	Npipes=np;
	Njuncs=nj;
	Nsources=nf;
	hdlss=hd;
	unit=u;
	flowUnit=uf;
	pressureUnit=up;	
	qcf=i_qcf;
	pipe=new PIPE();
	node=new NODE();
	topology=new Topology(np,nj,nf);
}

Net::~Net(){
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
	if(pipe!=NULL)		delete pipe;		
	if(node!=NULL)		delete node;		
	if(topology!=NULL)	delete topology;		
}


void Net::dispNet(ostream& stream){
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
	stream<<"Number of Pipes:"<<Npipes<<endl;
	stream<<"Number of Nodes:"<<Njuncs<<endl;
	stream<<"Number of Sources:"<<Nsources<<endl;
	stream<<"Unit:"<<unit<<endl;
	stream<<"Flow Unit:"<<flowUnit<<endl;
	stream<<"Pressure Unit:"<<pressureUnit<<endl;
	stream<<"Headloss Model:"<<hdlss<<endl;
	stream<<"\n\n";
	node->dispNodes(stream);
	pipe->dispPipes(stream,topology->getSN(),topology->getEN(),node);
}

int Net::getNp() const
{
	return Npipes;
}

int Net::getNn() const
{
	return Njuncs+Nsources;
}

int Net::getNj() const
{
	return Njuncs;
}

int Net::getNf() const
{
	return Nsources;
}	

string 	Net::getHd() const
{
	return hdlss;
}

string 	Net::getUnit() const
{
	return unit;
}

string 	Net::getQUnit() const
{
	return flowUnit;
}

string 	Net::getHUnit() const
{
	return pressureUnit;
}

Net *Net::permute(vector<int>* p,vector<int>* v){
	vector<int>* p_pointer=new vector<int>();
  	for(int i=0;i<Njuncs;i++)   p_pointer->push_back(0);
  	for(int i=0;i<Nsources;i++) p_pointer->push_back(0);
	for(unsigned int i=0;i<v->size();i++)  (*p_pointer)[(*v)[i]]=i;
	for(int i=0;i<Nsources;i++)  (*p_pointer)[Njuncs+i]=v->size()+i;
	Net* output=new Net(p->size(),v->size(),Nsources,hdlss,unit,flowUnit,pressureUnit,qcf);
	PIPE* outputPipe=output->getPIPE();
	NODE* outputNode=output->getNODE();
	Topology* outputTopology=output->getTopology();
	pipe->permutePipe(outputPipe,p);
	node->permuteNode(outputNode,v);
	topology->permuteTopology(outputTopology,p,p_pointer);
	delete p_pointer;
	return output;
}