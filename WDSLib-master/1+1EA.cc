#include "Simulation/Simulation.h"
#include "hydraulic/result.h"
#include <time.h>
vector<double> ADiameter ={ 36,48,60,72,84,96,108,120,132,144,156,168,180,192,204};
vector<double> unitCost ={ 93.6,133.7,176.3,221,267.6,315.8,165.4,416.5,468.7,522.1,576.6,632.1,688.5,745.1,804.1};
double penaltyCost;
/*int AVA=6;
*/
int GTN=100000;
double minP=0.0;
using namespace std;

vector<int>  generateinitialpopulation(int np)
{
	vector<int> Diameter = vector<int>(np);
	for (int i = 0; i<np; i++)
		Diameter[i]= rand() % ADiameter.size();
	return Diameter;
}

vector<int>  mutate(vector<int>* string)
{
	vector<int> string1;
	string1=*string;
	int aa = rand() % (string->size());
	int a = rand() %ADiameter.size();
	(string1)[aa]=a;
	return string1;
}


double evaluate(Result* result,Net* net,vector<int> *p1) {
	PIPE* pipe =net->getPIPE();
	double np=net->getNp();
	double nj=net->getNj();
	double cost1=0;
	penaltyCost=0;
	vector<double> hsol = result->getHsol();
	vector<double>* L = pipe->getL();
	vector<double>* zu = net->getNODE()->getZU();
	double Lscale=pipe->Lenscale();
	for (int i = 0; i<np; i++) cost1 += (*L)[i]*Lscale * unitCost[(*p1)[i]];
	for (int i = 0; i<nj; i++)
		if ((hsol)[i]-(*zu)[i]<minP)	penaltyCost += (minP - (hsol)[i]+(*zu)[i])*10000000;
	return cost1+penaltyCost;
}
int   main(int argc, char *argv[])
{ 
  srand (1);
	char *config=argv[1];
	double cost,currentbest=1e10;
	Result *result=new Result();
 	Simulation *simulation1=new Simulation();
 	Net *net=simulation1->L1a(result,config);
	vector<int> p1=generateinitialpopulation(net->getNp());
	vector<int> p2;
	cout<<p1.size()<<endl;
	for(int i=0;i<GTN;i++){ 
		simulation1->setD(&p1,&ADiameter,net->getPIPE()->Diascale());
	 	simulation1->solve(result);
	 	simulation1->L1b(result);
	 	cost=evaluate(result,net,&p1);
	 	if(cost<currentbest||i==0){
	 		currentbest=cost;
	 		p2=p1;
	 		cout<<i<<"\t"<<currentbest<<"\t"<<penaltyCost<<endl;
	 	}
	 	p1=mutate(&p2);
	 	if(i==10000) cout<<"."<<endl;
	 	if(i==20000)	 cout<<"."<<endl;
	 	if(i==30000)	 cout<<"."<<endl;
	 	if(i==40000)	 cout<<"."<<endl;
	 	if(i==50000)	 cout<<"."<<endl;
	 	if(i==60000)	 cout<<"."<<endl;
	 	if(i==70000)	 cout<<"."<<endl;
	 	if(i==80000)	 cout<<"."<<endl;
	 	if(i==90000)	 cout<<"."<<endl;
	}

 	simulation1->dispResult(result);

	delete simulation1;
	delete result;

 	return 0;

}
