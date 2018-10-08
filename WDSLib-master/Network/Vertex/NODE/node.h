#ifndef node_H
#define node_H
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;


class NODE
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
		NODE();
		
        /**
         *Overload constructor
         *
	     *This method sets the unknown-head node parameters
	     *
	     *@param ID_input Node ID
	     *@param dm_input The input nodal demand
	     *@param zu_input The input elevation head of a unknown-head node 
	     *
	     */
	     void setNODE(string,double,double);
		
		
        /**
         *Overload constructor
         *
	     *This method sets the fixed-head node parameters
	     *
	     *@param ID_input Source ID
	     *@param zs_input the input elevation head of a source
	     */
	     
   		void setSOURCE(string,double);


        /**
          *Destructor
          */
		~NODE();
		//@}


	    // -----------------------------------------------------------------------
	    //  Getter methods
	    // -----------------------------------------------------------------------
	     /** @name Getter methods */
	    //@{



		/** Get the vector of nodal demands
	      *
	      * This method returns the vector of nodal demands.
	      *
	      * @return the vector of nodal demands
	      *
	      */
		vector<double>* getDM(){
			return dm;
		}



		/** Get the vector of nodal elevations
	      *
	      * This method returns the vector of nodal elevations.
	      *
	      * @return the vector of nodal elevations
	      *
	      */
		vector<double>* getZS(){
			return zs;
		}


		vector<double>* getZU(){
			return zu;
		}


		/** Get the ID of a node
	      *
	      * This method returns the ID of a node.
	      *
	      * param index the index of a node
	      * @return the ID of a node
	      *
	      */
	     string getNodeID(int index){
			if(index<nodeID->size())
				return (*nodeID)[index];
			else
				return (*sourceID)[index-(nodeID->size())];
		}


		 int getMaxNodeIDLength() { return MaxNodeIDLength;}

		/** Get the scaling factor of nodal demands
	      *
	      * This method returns the scaling factor of nodal demands.
	      *
	      *
	      * @return scaling factor of nodal demand
	      */
   		double DMscale(){
   			return dmScale;
   		}

		/** Get the scaling factor of fixed-head node elevations
	      *
	      * This method returns the scaling factor of fixed-head node elevations.
	      *
	      *
	      * @return scaling factor of fixed-head node elevations
	      */
   		double ELscale(){
   			return zsScale;
   		}
		//@}



	     /**
	      * This method displays the parameters of the Node parameters 
	      */
   		void dispNodes(ostream& );


	     /**
	      * This method applies scalings to the Node parameters
	      */
   		void nodeScale();
   		

	     /**
	      * This method applies permutation to the current Node class
	      *
	      * @param output the ouput permuted Node class
	      * @param v permutation vector for nodes
	      *
	      */
		void permuteNode(NODE*,vector<int>*);


	     /**
	      * This method displays the scaling factor for each of the Node parameters
	      */
		void dispNodeScale(ostream& stream){
			stream<<"Nodal demand Scaling factor: "<<dmScale<<endl;
			stream<<"Nodal head Scaling factor: "<<zsScale<<endl;
			stream<<"Fixed-head node elevation head Scaling factor "<<zsScale<<endl;
		}

		//Access function

	private:
		vector<string>	*nodeID,
						*sourceID;

		vector<double> 	*zs,
						*zu,	
						*dm;

		double			dmScale,
						zsScale;

		bool			scalingIndicator;


		int MaxNodeIDLength;
};
#endif
