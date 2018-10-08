#ifndef pipe_H
#define pipe_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <unordered_map>  
#include "../../Vertex/NODE/node.h"


using namespace std;

class PIPE //: public Edge
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
		PIPE();
		
        /**
         *Overload constructor
         *
	     *This method sets the pipe parameters
	     *
	     *@param ID_input Pipe ID
	     *@param L The input pipe length
	     *@param D The input pipe diameter
	     *@param epmm The input pipe roughness (C for Hazen-William headloss model 
	     * 			  roughness height for Darcy-Weisbach model)
	     */
	     void setPIPE(string,double,double,double);
        /**
          *Destructor
          */
		~PIPE();
        //@}
		
		
		// -----------------------------------------------------------------------
	    //  Setter Methods
	    // -----------------------------------------------------------------------
	    /** @name Setter Methods */
	    //@{

		/** 
	     *This method sets the diamter of a pipe
	     *@param pipeIndex pipe index
	     *@param D Diameter of the pipe

	     */
		void setD(int pipeIndex,double D){(*diameter)[pipeIndex]=D;}

		/** 
	     *This method sets the length of a pipe
	     *@param pipeIndex pipe index
	     *@param L Length of the pipe

	     */
		void setL(int pipeIndex,double L){ (*length)[pipeIndex]=L;}

		/** 
	     *This method sets the roughness of a pipe
	     *@param pipeIndex Pipe index
	     *@param R Roughness of the pipe

	     */
		void setR(int pipeIndex,double R){ (*roughness)[pipeIndex]=R;}
        //@}


	    // -----------------------------------------------------------------------
	    //  Getter methods
	    // -----------------------------------------------------------------------
	    /** @name Getter methods */
	    //@{

		/** Get the ID of a pipe
	      *
	      * This method returns the ID of a pipe.
	      *
	      * param index the index of a pipe
	      * @return the ID of a pipe
	      *
	      */
		string getPipeID(int index){return (*ID)[index];}


		/** Get the vector of pipe diameters
	      *
	      * This method returns the vector of pipe diameters.
	      *
	      *
	      * @return vector of pipe diameters
	      */
		vector<double>* getD(){	return diameter;}

		/** Get the vector of pipe lengths
	      *
	      * This method returns the vector of pipe lengths.
	      *
	      *
	      * @return vector of pipe lengths
	      */

		vector<double>* getL(){	return length;}

		/** Get the vector of pipe roughnesses
	      *
	      * This method returns the vector of pipe roughnesses.
	      *
	      *
	      * @return vector of pipe roughnesses
	      */
		vector<double>* getR(){	return roughness;}




		/** Get the scaling factor of pipelength 
	      *
	      * This method returns the scaling factor of pipelength
	      *
	      *
	      * @return scaling factor of pipelength
	      */
		double Lenscale(){return Lscale;}


		/** Get the scaling factor of pipe diameter
	      *
	      * This method returns the scaling factor of pipe diameter.
	      *
	      *
	      * @return scaling factor of pipe diameter
	      */
		double Diascale(){return Dscale;}


		/** Get the scaling factor of pipe roughnesses
	      *
	      * This method returns the scaling factor of pipe roughnesses.
	      *
	      *
	      * @return scaling factor of pipe roughnesses
	      */
		double Roughscale(){return Rscale;}


		/** Get the scaling factor of G and F matrices 
	      *
	      * This method returns the scaling factor of G and F matrices 
	      *
	      *
	      * @return scaling factor of G and F matrices 
	      */
		double GFscale(){return Gscale;	}
		
		//@}


	     /**
	      * This method applies scalings to the Pipe parameters
	      *
	      * @param hdlss headloss model
	      * @param unit length unit
	      *
	      */
   		void pipeScale(string,string);


	     /**
	      * This method applies permutation to the current Pipe class
	      *
	      * @param output the ouput permuted Pipe class
	      * @param p permutation vector for pipes
	      *
	      */
		void permutePipe(PIPE*,vector<int>*);



		int getMaxPipeIDLength() { return MaxPipeIDLength; }

	     /**
	      * This method displays the parameters of the Pipe parameters 
	      * and start node and the end node of each pipe
	      *
	      * @param SN vector of start node
	      * @param EN vector of end node
	      *
	      */
   		void dispPipes(ostream& ,vector<int>*,vector<int>*,NODE*);

   		void setScales(double,double,double,double);
	     /**
	      * This method displays the scaling factor for each of the Pipe parameters
	      */
		void dispPipeScale(ostream& stream){
			stream<<"Pipe Length Scaling factor="<<Lscale<<endl;
			stream<<"Pipe Diameter Scaling factor="<<Dscale<<endl;
			stream<<"Pipe Roughness Scaling factor="<<Rscale<<endl;
		}
	private:
		vector<string>	*ID;
		vector<double>	*length, 		
						*diameter,
					 	*roughness;

		double			Lscale,
						Dscale,
						Rscale,
						Gscale;

		bool			scalingIndicator;


		int MaxPipeIDLength;
};



#endif


