#include "topology.h"

Topology::Topology(int Npipes,int Njuncs,int Nsources){
  A2=NULL;
  T1=NULL;
  L21=NULL;
  np=Npipes;
  nj=Njuncs;
  nf=Nsources;

  corePipes=new vector<int>();
  coreNodes=new vector<int>();
  p_set=NULL;
  p_vec=new vector<int>();
  v_vec=new vector<int>();
  s_vec=new vector<int>();
  t_vec=new vector<int>();
  forestNodes=NULL;
  rootNodes=new vector<int>();
  coTree=new vector<int>();
  forestPipes   =NULL; 
 // spanningTree   = new vector<pair<int,int> >(); 
  superGraph   = new vector< vector<int> >(); 
  InternalTrees   = new vector< vector<unsigned int> >(); 
  pSN=new vector<int>();
  pEN=new vector<int>();
  adjList=new vector<vector<pair<int,int> > >(nj+nf);
  GI=NULL;
}




Topology::~Topology(){
//-------------------------------------------------------------------------
//  Date:    10/09/2014
//  Author:  Mengning Qiu
//  Input:   
//  Output:  
//  Purpose: 
//  calls:   
//  called from: 
//-------------------------------------------------------------------------
  if(T1!=NULL)    delete T1;
  if(L21!=NULL)   delete L21;

  if(A2!=NULL)    delete A2;

  if(corePipes!=NULL) delete corePipes;
  if(coreNodes!=NULL)    delete coreNodes;
  
  if(p_set!=NULL) delete p_set;
  if(p_vec!=NULL)  delete p_vec;
  if(v_vec!=NULL)  delete v_vec;
  if(s_vec!=NULL)  delete s_vec;
  if(t_vec!=NULL)  delete t_vec;
  if(forestNodes!=NULL) delete forestNodes;
  if(rootNodes!=NULL) delete rootNodes;

  //if(spanningTree!=NULL)  delete spanningTree;
  if(coTree!=NULL)  delete coTree;
  if(forestPipes!=NULL) delete forestPipes;
  if(superGraph!=NULL) delete superGraph;
  if(InternalTrees!=NULL) delete InternalTrees;
  if(pSN!=NULL)   delete pSN;
  if(pEN!=NULL)   delete pEN;
  if(adjList!=NULL)   delete adjList;
  if(GI!=NULL)   delete GI;
}
  
void Topology::setTopology(int SN,int EN){
//-------------------------------------------------------------------------
//  Date:    10/09/2014
//  Author:  Mengning Qiu
//  Input:   
//  Output:  
//  Purpose: 
//  calls:   
//  called from: 
//-------------------------------------------------------------------------
  pSN->push_back(SN);
  pEN->push_back(EN);
}

void Topology::searchLeafs(vector<double> *dm){
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
    int nextPipe;
    int nextNode;
    forestNodes=new set<int> ();
    forestPipes=new vector<vector<pair<int,int> > >();
    vector<pair<int,int> > forestPipe;
    for(int i=0;i<nj;i++){
      int currentNode=i;
        while((*GI)[currentNode]==1&&currentNode<nj){
          for(int j=0;j<(*adjList)[currentNode].size();j++){
            if((*GI)[(*adjList)[currentNode][j].second]!=0){
              nextNode=(*adjList)[currentNode][j].second;
              nextPipe=(*adjList)[currentNode][j].first;
              continue;
            }
          }
          p_set->erase(nextPipe);
          forestNodes->insert(currentNode);
          forestPipe.push_back(make_pair<int,int>(nextPipe,currentNode));
          (*dm)[nextNode]=(*dm)[nextNode]+(*dm)[currentNode];
          (*GI)[currentNode]--;
          (*GI)[nextNode]--;
          currentNode=nextNode;
        } 
        if(!forestPipe.empty()){
          rootNodes->push_back(currentNode);
          forestPipes->push_back(forestPipe);
          forestPipe.clear();
        }
      }
}

void Topology::searchSTs(){
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
  set<pair<int,int> > *singleton
  =new set<pair<int,int> >();
  set<pair<int,int> >::iterator it;
  vector<bool> *vistNode=new vector<bool>(np+nj);
  for(int i=0;i<coreNodes->size();i++) (*vistNode)[(*coreNodes)[i]]=true;
  
   for(int i=nj;i<adjList->size();i++){
    for(int j=0;j<(*adjList)[i].size();j++){
      singleton->insert((*adjList)[i][j]);
      (*vistNode)[i]=false;  
    }
  }
  while(!singleton->empty()){
      it=singleton->begin();
      int currentPipe=it->first;
      int currentNode=it->second; 
      if((*vistNode)[currentNode]){
        p_vec->push_back(currentPipe);
        p_set->erase(currentPipe);
        (*vistNode)[currentNode]=false;  
        v_vec->push_back(currentNode);
        for(int j=0;j<(*adjList)[currentNode].size();j++)
          if((*vistNode)[(*adjList)[currentNode][j].second])
            singleton->insert((*adjList)[currentNode][j]); 
      }
      singleton->erase(it);
    }
  for(set<int>::iterator it=p_set->begin();it!=p_set->end();++it){
    p_vec->push_back(*it);
    coTree->push_back(*it);
  }
  delete vistNode;
  delete singleton;
}


void Topology::NetworkDecomposition(Result* result,vector<double>* dm,int SolverFlag,bool FCPAFlag){
  if(SolverFlag==1&&!FCPAFlag){
    for(int i=0;i<nj;i++) coreNodes->push_back(i);
    for(int i=0;i<np;i++) corePipes->push_back(i);
    return;
  }
  p_set=new set<int>();
  GI=new vector<int>(nf+nj);
  for(int i=0;i<np;i++){
    p_set->insert(i);
    int SN=(*pSN)[i];
    int EN=(*pEN)[i];
    (*adjList)[(*pSN)[i]].push_back(pair<int,int>(i,(*pEN)[i]));
    (*adjList)[(*pEN)[i]].push_back(pair<int,int>(i,(*pSN)[i]));
    (*GI)[SN]++;
    (*GI)[EN]++;
  }
  if(FCPAFlag){ 
    result->SampleCPUCycles("FCPA","start"); 
    searchLeafs(dm);
    Nforest=forestNodes->size();
    if(!forestPipes->empty()){
      set<int>::iterator it;
      it=forestNodes->begin();
      for(int i=0;i<nj;i++){
        if(*it!=i)         coreNodes->push_back(i);
        else ++it;
      }
    }else for(int i=0;i<nj;i++) coreNodes->push_back(i);
    result->SampleCPUCycles("FCPA","end"); 
  }else   for(int i=0;i<nj;i++) coreNodes->push_back(i);


  for(set<int>::iterator it=p_set->begin();it!=p_set->end();++it)   
    corePipes->push_back(*it);

  if(SolverFlag==2){
    result->SampleCPUCycles("RCTM","start");   
    searchSTs(); 
    unsigned int NNC=v_vec->size();
    vector<int> CTSN(np-nj);
    vector<int> CTEN(np-nj);


    vector<int>* vprime=new vector<int>(np);
    vector<int>* vvprime=new vector<int>(nj);
  
    for(unsigned int i=0;i<p_vec->size();i++) 
      (*vprime)[(*p_vec)[i]]=i;
    for(unsigned int i=0;i<v_vec->size();i++) 
      (*vvprime)[(*v_vec)[i]]=i;
  
    A2=new Matrix(p_vec->size(),nf);
  
    vector<int> pp(np-nj);
    for(int i=0;i<coTree->size();i++){
      CTSN[i]=(*pSN)[(*coTree)[i]];
      CTEN[i]=(*pEN)[(*coTree)[i]];
      pp[i]=i;
    }


   T1=new Matrix(NNC,NNC);

    for(unsigned int i=0;i<p_vec->size();i++){  
        int SN=(*pSN)[(*p_vec)[i]];
        int EN=(*pEN)[(*p_vec)[i]];     
      if(i<NNC){
        if(SN<nj)   T1->triple(i,(*vvprime)[SN],1);
        if(EN<nj)   T1->triple(i,(*vvprime)[EN],-1); 
      } 
      if(SN>=nj) A2->triple(i,SN-nj,1);
      if(EN>=nj) A2->triple(i,EN-nj,-1);
    }
//T1->printMatrix(0);
    L21=new Matrix(np-nj,NNC);
    int size=np-nj-1;
    int j,SN,EN,STP,STN,pSTP,SSN,EEN;
    for(int i=NNC-1;i>=0;i--){
       STP=(*p_vec)[i];   
       STN=(*v_vec)[i];
       pSTP=(*vprime)[STP];
       SSN=(*pSN)[STP];
       EEN=(*pEN)[STP];
      for(int k=0;k<=size;k++){
        bool test=false;
        j=pp[k];
        if(STN==CTEN[j]){
          if(SSN==STN){
            CTEN[j]=EEN;
            L21->triple(j,pSTP,1);
          }else if(EEN==STN){  
            CTEN[j]=SSN;
            L21->triple(j,pSTP,-1);
          }
         if(CTSN[j]==CTEN[j]){  
            iter_swap(pp.begin() + k, pp.begin() + size);
            size--;
            k--;
          }
        }else if(STN==CTSN[j]){
          if(SSN==STN){ 
            CTSN[j]=EEN;
            L21->triple(j,pSTP,-1);
          }
          else if(EEN==STN){
            CTSN[j]=SSN;
            L21->triple(j,pSTP,1);
          }   
           if(CTSN[j]==CTEN[j]){  
            iter_swap(pp.begin() + k, pp.begin() + size);
            size--;
            k--; 
          }
        }
          
      }
    }
    int NPT=np-nj;
    T1->CCS();
    L21->CCS();
    A2->CCS();
    delete vvprime; 
    delete vprime;
    result->SampleCPUCycles("RCTM","end"); 
  }

}

void Topology::permuteTopology(Topology* output,vector<int>* p,vector<int>* p_pointer){
  for(unsigned int i=0;i<p->size();i++){
    int pipeIndex=(*p)[i];
    output->setTopology((*p_pointer)[(*pSN)[pipeIndex]],(*p_pointer)[(*pEN)[pipeIndex]]);
  }
}