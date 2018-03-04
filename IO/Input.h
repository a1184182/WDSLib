#ifndef Input_H
#define Input_H
#include <iostream>
#include <string>
#include <limits>
#include <stdio.h>
#include <math.h> 
#include <algorithm>	
#include <unistd.h>
#include "../Network/Net.h"
#include "epanet2.h"
#include "../Simulation/Parameter.h"
#include "../hydraulic/result.h"


using namespace std;

class Input{
	public:
	  	// -----------------------------------------------------------------------
	    //  Constructors and Destructor
	    // -----------------------------------------------------------------------
	    /** @name Constructors and Destructor */
	    //@{
	    /**
	      *Default constructor
	      **/
		Input();

		/**
         *Overload constructor
         *
	     *This method sets the names of the EPANET input and the report files
	     *
	     *@param inpFIle EPANET input file
	     *@param reportFile EPANET report file
	     */
		int setInput(char *,char *);
        /**
          *Destructor
          */
		~Input();
		//@}

	  	// -----------------------------------------------------------------------
	    //  Input functions
	    // -----------------------------------------------------------------------
	    /** @name  Input functions */
	    //@{

	    /** Parse the node parameters
	   	  *
	   	  * This method parse the node parameters using the EPANET parser
	   	  * 
	      * @param Net class
	      *
	      */
		void getNodeData(Net* );

	    /** Parse the pipe parameters
	   	  *
	   	  * This method parse the pipe parameters using the EPANET parser
	   	  * 
	      * @param Net class
	      *
	      */
		void getPipeData(Net* );


	    /** Parse the network information
	   	  *
	   	  * This method parse the network information using the EPANET parser
	   	  * 
	      * @return Net class
	      * @see getNodeData
	      * @see getPipeData
	      */
		Net* getNetInfo();
		//@}



	  	// -----------------------------------------------------------------------
	    //  Output functions
	    // -----------------------------------------------------------------------
	    /** @name  Output functions */
	    //@{


  		/** This method displays the basic machine information
	      *
	      */
		void basicInfo();

  		/** This method displays the the EPANET input file name and the network
	      * input data
	      *
	      * @param net a Net class
	      * @see dispNet in Net
	      */
		void NetInfo(Net*);

  		/** This method displays the scaling factors 
	      *
	      * @param net a Net class
	      * @see dispScale in Net
	      */
		void ScalingInfo(Net*);

  		/** This method displays the convergence information
	      *
	      * The convergence information include the user selected norm, 
	      * energy residual, and continuity residual.
	      *
	      * @param parameter a Parameter class
	      * @param result a Result class
	      */
		void ConverInfo(Parameter*,Result*);

  		/** This method displays the pipe results
	      *
	      * @param net a Net class
	      * @param result a Result class
	      * @param qsol a vector of flows
	      */
		void LinkResult(Net*,Parameter*,vector<double>);

  		/** This method displays the nodal results
	      *
	      * @param net a Net class
	      * @param result a Result class
	      * @param hsol a vector of nodal heads
	      */
		void NodeResult(Net*,Parameter*,vector<double>);

  		/** This method displays the statistical information of the results
	      *
	      * @param net a Net class
	      * @param qsol a vector of flows
	      * @param hsol a vector of nodal heads
	      */
		void StatInfo(Net*,vector<double>,vector<double>);
		//@}

	private:
		char *inputFile;
		char *RptFile;
		FILE *InFile;
};

#endif
