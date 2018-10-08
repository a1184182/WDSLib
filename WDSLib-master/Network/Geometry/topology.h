#ifndef topology_H
#define topology_H
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <utility> 
#include "../../math/Matrix.h"
#include "../../hydraulic/result.h"
#include <stdint.h>
#include <iterator>   

using namespace std;

class Topology
{
  public:
  // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    /** @name Constructors and Destructor */
    //@{
    /**
      *Default constructor
      *
       *This method initialize the Topology class
       *
       *@param Npipes Number of pipes 
       *@param Njuncs Number of unknown-head nodes
       *@param Nsources Number of fixed-head nodes
       */  
    Topology(int, int, int);
    
        /**
         *Overload constructor
         *
       *This method sets the Network topology
       *
       *@param SN The start node of the current pipe
       *@param EN The end node of the current pipe
       */
    void setTopology(int,int);
    /**
      *Destructor
      */
    ~Topology();
        //@}

    /**
      * A forest search algorithm
      *
      * This function searches for the forest component. A node is marked as leaf node
      * when its node degree is one, and this node and pipe pair is inserted into the 
      * forestPipe. The node degree of the parent node of the leaf node is reduced by 
      * one and the pointer is moved to the parent node. This process is repeated until all
      * nodes in the network has been searched once.
      *
      *@param dm
      */

    void searchLeafs(vector<double> *);
    /**
      * A spanning tree search algorithm
      *
      * This function searches for a spanning tree and co-tree combination. All sources are marked as visited
      * and the starting point of the search process and inserted into the vector SN. Removing the first
      * node in the vector SN and all adjacent pairs, node s and pipe t. If the node s is not visited, the pair pipe
      * and 
      *
      *@param dm
      */
    void searchSTs();
    void NetworkDecomposition(Result*,vector<double>*,int,bool);    
    void permuteTopology(Topology* ,vector<int>* ,vector<int>* );

    void createAdjList();

/*

    void CreateA1A2(vector<int>,vector<int>);
    void NetworkDecomposition(Result*,vector<double>*,int,bool);    
    void ForestCorePartitioning(vector<double> *,vector<double> *,vector<int> *,vector<int> *);
    void update(int*,int*);
    void searchLeaf(Result*,int, int,int,vector<vector<int> >* ,vector<vector<int> >*,vector<double> *,vector<double> * );
    void searchInternalTree(int, int,int,vector<vector<int> >* ,vector<vector<int> >* ,vector<double> *,vector<double> *);
    vector<unsigned int> searchForest(int,int,vector<vector<int> >* ,vector<vector<int> >*,vector<double> *,vector<double> *);    
    void searchST(Result*,int ,int ,int ,vector<vector<int> >* ,vector<vector<int> >*,vector<int>*,vector<int>* );
    
    vector<pair<int,int> > searchSeriespipe(Result*,int,int,vector<vector<int> >* ,vector<vector<int> >*,vector<double> *,vector<double> *);
*/

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    /** @name Getter methods */
    //@{

    /** Get the matrix A2
      *
      * This method returns the fixed-head node-arc incidence matrix
      *
      * @return the matrix A2
      *
      */
    Matrix* getA2()  { return A2;  }

    /** Get the vector SN
      *
      * This method returns the vector of the start node of each pipe
      *
      * @return the vector SN
      *
      */
    vector<int>* getSN(){ return pSN;}

    /** Get the vector EN
      *
      * This method returns the vector of the end node of each pipe
      *
      * @return the vector EN
      *
      */
    vector<int>* getEN(){ return pEN;}
    
    /** Get the matrix A1
      *
      * This method returns the unknown-head node-arc incidence matrix
      *
      * @return the matrix A1
      *
      */
    Matrix* getA1()  { return A1;  } 

    /** Get the vector p_corePipesvec
      *
      * This method returns the vector of the indices of the pipes in core 
      *
      * @return the vector corePipes
      *
      */    

    vector<int> *getcorePipes(){ return corePipes; }
  

    /** Get the vector coreNodes
      *
      * This method returns the vector of the indices of the nodes in core 
      *
      * @return the vector coreNodes
      *
      */   
    vector<int> *getcoreNodes(){ return coreNodes; }


    /** Get the vector s_vec
      *
      * This method returns the vector of the indices of the pipes in forest 
      *
      * @return the vector s_vec
      *
      */ 
    vector<int>* returnPIIF(){ return s_vec; }
    
    /** Get the vector t_vec
      *
      * This method returns the vector of the indices of the nodes in forest 
      *
      * @return the vector t_vec
      *
      */ 
    vector<int>* returnNIIF(){ return t_vec; }
 
    /** Get the matrix L21
      *
      * This method returns a part of the null space of the permuted unknown-head noce-arc
      * incidence matrix for the RCTM
      *
      * @return the Matrix L21
      *
      */
    Matrix* getL21(){ return L21; }

 
    /** Get the matrix T1
      *
      * This method returns the unknown-head noce-arc incidence matrix for the spanning tree
      * of the RCTM
      * @return the Matrix T1
      *
      */
    Matrix* getT1(){ return T1; }
    
 
    /** Get the forest component
      *
      * This method returns the forest component in pairs of pipe and node
      * from end node to the root node
      *
      * @return forestPipes
      *
      */
    vector<vector<pair<int,int> > >*getforestPipes(){ return forestPipes; }


 
    /** Get the vector of the root nodes
      *
      * This method returns a vector of the root nodes 
      * @return rootNodes
      */
    vector<int> *getrootNodes(){ return rootNodes; }

    int getNforest(){return Nforest;}

    vector<int>* returnPIIC(){ return p_vec; }

    vector<int>* returnNIIC(){ return v_vec; }
        //@}


  private:
    int np,nj,nf;
    Matrix* A1;
    Matrix* A2;
    Matrix* L21;
    vector<vector<pair<int,int> > >*forestPipes;  // The collection of the forest pipes
    set<int>  *forestNodes;  // The collection of the forest pipes
    vector<int>  *rootNodes;    // The collection of the forest pipes
    vector<int>  *corePipes;
    vector<int>  *coreNodes;
    vector<vector<pair<int,int> > > *adjList;
    vector<int>  *pSN;
    vector<int>  *pEN;
    vector<int>* GI;
    vector<pair<int,int> >*spanningTree;  // The collection of the spanning tree pipes and nodes
    vector<int>  *coTree;  // The collection of the cotree pipes
    vector<int>   *p_vec,     /* pipe indeces in core         */
            *v_vec,     /* node indeces in core         */
            *s_vec,     /* pipe indeces in forest         */
            *t_vec;   /* Graph index of nodes         */

    Matrix  *T1; 
    bool      flag;
    int Nforest;
    int NsuperNode;      
      int NsuperLink;
    vector< vector<int> > *superGraph;  // The collection of the forest pipes
    vector<vector<unsigned int> > *InternalTrees;
      vector<vector<unsigned int> > *superPipes;
      int Ncorepipes;
      set<int> *p_set;
      vector<double> *A2el;
      
      
//template <class InputIterator1, class InputIterator2, class OutputIterator>
  bool loop_diff (set<set<int> >::iterator it1,set<set<int> >::iterator it2,vector<set<int> >* output)
{
  set<int> result;
  set<int> loop1=*it1;
  set<int> loop2=*it2;
  set<int>::iterator first1=loop1.begin();
  set<int>::iterator last1=loop1.end();
  set<int>::iterator first2=loop2.begin();
  set<int>::iterator last2=loop2.end();
  set<int>::reverse_iterator rfirst1=loop2.rbegin();
  set<int>::reverse_iterator rfirst2=loop2.rbegin();
  /*cout<<"------------------input1------------------"<<endl;
  for (set<int>::iterator it=loop1.begin(); it!=loop1.end(); ++it)
        cout<<*it<<",";
     cout<<endl;
  cout<<"------------------input2------------------"<<endl;
  for (set<int>::iterator it=loop2.begin(); it!=loop2.end(); ++it)
        cout<<*it<<",";
     cout<<endl;*/
    if (*rfirst1<=*first2){  return false;}
    if (*rfirst2<=*first1){ return false;}
  while (true)
  {    

    if (first2==last2){
      result.insert(first1,last1); 
      if(result.size()<loop1.size()){ output->push_back(result); return true;}
    else{  return false;}
  } 
    if (first1==last1){
      result.insert(first2,last2);
      if(result.size()<loop1.size()){ output->push_back(result);  return true;}
    else{  return false;}
    } 
  if (*first1<*first2) {result.insert(*first1); ++first1;}
    else if (*first2<*first1) { result.insert(*first2); ++first2;}
    else { ++first1; ++first2; }
  }


};




};



#endif


