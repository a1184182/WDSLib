#ifndef Net_H
#define Net_H

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "./Vertex/NODE/node.h"
#include "./Edge/PIPES/pipe.h"
#include "./Geometry/topology.h"

using namespace std;

class Net 
{
	public:
        // -----------------------------------------------------------------------
        //  Constructors and Destructor
        // -----------------------------------------------------------------------
        /** @name Constructors and Destructor */
        //@{
       
        /**
          *Default constructor
          */
		Net();
		
        /**
         *Overload constructor
         *
	     *This method sets the Net parameters and initialized 
	     * Pipe class, Node class, and Topology class.
	     *
	     *@param np Number of pipes
	     *@param nj Number of unknown-head nodes
	     *@param nf Number of fixed-head nodes
	     *@param hd headloss model
	     *@param u length unit
	     *@param uf flow unit
	     *@param up pressure unit
	     *@param qcf flow conversion unit		
	     */
	     Net(int,int,int,string,string,string,string,double);
        /**
          *Destructor
          */
		~Net();
        //@}


		// -----------------------------------------------------------------------
	    //  Setter Methods
	    // -----------------------------------------------------------------------
	    /** @name Setter Methods */
	    //@{
    
	    /**
          *Set the flow conversion factor
          */
		/** 
	     *the flow conversion factor that converts the flow to m^3/s
	     *@param input the flow conversion factor 
	     */
		
		void setQCF(double input){
			qcf=input;
		}

		/**
          *Set the pipe parameters
          */
		/** 
	     *This method sets the pipe parameters and Topology class 
	     *
	     *@param pipeID Pipe ID
	     *@param SN The start node of the current pipe
	     *@param EN The end node of the current pipe
	     *@param L The length of the current pipe
	     *@param D The diameter of the current pipe
	     *@param epmm The roughness height node of the current pipe if Darcy-Weisbach 
	     * 			  headloss model is used and Hazen-William C if Hazen-William 
	     * 			  headloss model is used.	
	     */
		
		void setPIPE(string pipeID,int SN,int EN,double L,double D,double epmm){
			pipe->setPIPE(pipeID,L,D,epmm);
			topology->setTopology(SN,EN);
		}

		/**
          *Set the node parameters
          */
		/** 
	     *This method sets the node parameters
	     *@param nodeID Node ID
	     *@param dm The demand of the current node
	     *@param el the elevation head of the current node

	     */
		void setNODE(string nodeID,double dm,double el){
			node->setNODE(nodeID,dm,el);
		}

		/**
          *Set the source parameters
          */
		/** 
	     *This method sets the node parameters
	     *@param sourceID source ID
	     *@param el the elevation head of the current source

	     */
		void setSOURCE(string sourceID,double el){
			node->setSOURCE(sourceID,el);
		}
		//@}

	    // -----------------------------------------------------------------------
	    //  Getter methods
	    // -----------------------------------------------------------------------
	     /** @name Getter methods */
	    //@{

	    /** Get the flow converstion factor
	      *
	      * This method returns the flow conversion factor that 
	      * converts the flow unit to m^3/s
	      *
	      *
	      * @return flow conversion factor
	      */
		double getQCF(){
			return qcf;
		}

	    /** Get the PIPE class
	      *
	      * This method returns the PIPE class that contains all the pipe
	      * parameters
	      *
	      * The returned PIPE class is owned by the Net class.
	      *
	      * @return a refernce to the current PIPE class
	      */
		PIPE* getPIPE(){return pipe;}

	    /** Get the NODE class
	      *
	      * This method returns the NODE class that contains all the node
	      * parameters
	      *
	      * The returned NODE class is owned by the Net class.
	      *
	      * @return a refernce to the current NODE class
	      */
		NODE* getNODE(){return node;}

	    /** Get the Topology class
	      *
	      * This method returns the Topology class that contains all the Topology
	      * parameters
	      *
	      * The returned Topology class is owned by the Net class.
	      *
	      * @return a refernce to the current Topology class
	      */
		Topology* getTopology(){return topology;}

	    /** Get the "Npipes" variable
	      *
	      * This method gets the number of pipes from the Net class
	      * @return number of pipes
	      */
		int 	getNp() const;			//get the number of pipes


		/** Get the number of nodes
	      *
	      * This method gets the number of nodes from the Net class
	      * @return Njuncs+Nsources
	      */
		int 	getNn() const;			//get the number of junctions


		/** Get the number of unknown-head nodes
	      *
	      * This method gets the number of unknown-head nodes from the Net class
	      * @return Njuncs
	      */
		int 	getNj() const;			//get the number of junctions


		/** Get the number of fixed-head nodes
	      *
	      * This method gets the number of fixed-head nodes from the Net class
	      * @return Nsources
	      */
		int 	getNf() const;			//get the number of sources


		/** Get the type of headloss model
	      *
	      * This method gets the type of headloss model from the Net class
	      * @return hdlss
	      */
		string 	getHd() const;			//get the type of the head loss function


		/** Get the type of length unit
	      *
	      * This method gets the type of length unit from the Net class
	      * @return unit
	      */
		string 	getUnit() const;		//get the type of unit


		/** Get the type of flow unit
	      *
	      * This method gets the type of flow unit from the Net class
	      * @return flowUnit
	      */
		string 	getQUnit() const;		//get the type of flow unit


		/** Get the type of pressure unit
	      *
	      * This method gets the type of pressure unit from the Net class
	      * @return HUnit
	      */
		string 	getHUnit() const;		//get the type of head unit

		//@}



	     /**
	      * This method displays the parameters of Net class, which include 
	      * the Pipe parameters, Node parameters, and Topology class
	      *@see dispPipes
	      *@see dispNodes
	      */
		void 	dispNet(ostream& );

		/**
	      * This method displays the scale factors used in the current Pipe class 
	      *  and current Node class
	      *
	      *@see dispNodeScale
	      *@see dispPipeScale
	      */
		void dispScale(ostream& stream){
			node->dispNodeScale(stream);
			pipe->dispPipeScale(stream);
		}

		/**
	      * This method permutes the network based on the pipe 
	      * permutation vector and the node permutation vector
	      *
	      *@param p pipe permutation vector
	      *@param v node permutation vector
	      *
	      *@see permutePipe
	      *@see permuteNode
	      *@see permuteTopology
	      *
	      *@return permuted Net class
	      */
		Net* permute(vector<int>* ,vector<int>* );



        /**
          * This method applies the variable scaling to Pipe class
          * and the Node class in Net
          *
          * @see nodeScale
          * @see pipeScale
          */
		void scale(){
			node->nodeScale();
			pipe->pipeScale(hdlss,unit);
		}

		/*permute(vector<int>* p,vector<int>* v){
			vector<int>* p_pointer=new vector<int>();
		  	for(int i=0;i<Njuncs;i++)   p_pointer->push_back(0);
		  	for(int i=0;i<Nsources;i++) p_pointer->push_back(0);
	  		for(unsigned int i=0;i<v->size();i++)  (*p_pointer)[(*v)[i]]=i;
	  		for(int i=0;i<Nsources;i++)  (*p_pointer)[Njuncs+i]=v->size()+i;
			Net* output=new Net(p->size(),v->size(),Nsources,hdlss,unit,flowUnit,pressureUnit,qcf);

			PIPE* outputPipe=output->getPIPE();
			NODE* outputNode=output->getNODE();
			Topology* outputTopology=output->getTopology();
			pipe->permutePipe(outputPipe,p,p_pointer);
			node->permuteNode(outputNode,v);
			topology->permuteTopology(outputTopology,p,p_pointer);
			delete p_pointer;
			return output;
		}*/

	private:
		PIPE *pipe;				/*!< a Pipe class*/
		NODE *node;				/*!< a Node class*/
		Topology *topology;		/*!< a Topology class*/
		int Npipes;				/*!< Number of pipes*/
		int Njuncs;				/*!< Number of junctions*/
		int Nsources;			/*!< Number of sources*/
		string hdlss;			/*!< Headloss model*/
		string unit;			/*!< length unit*/
		string flowUnit;		/*!< flow unit*/
		string pressureUnit;	/*!< /pressure unit*/
		double qcf;				/*!< flow conversion factor*/
};

#endif