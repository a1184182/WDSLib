#ifndef Simulation_h
#define Simulation_h

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string.h>
#include "../hydraulic/result.h"
#include "Flag.h"
#include "Parameter.h"
#include "../IO/Input.h"
#include "../hydraulic/RCTM/RCTMsolver.h"
#include "../hydraulic/GGA/GGAsolver.h"

using namespace std;

/** 
 *  @file    Simulation.h
 *  @author  Mengning Qiu
 *  @date    23/02/2018
 *  @version 1.0 
 *  
 *  @brief Manage hydraulic simulation
 *
 *  @section DESCRIPTION
 *  
 *  This is a class that 
 *
 */

class Simulation{
	public:
		// -----------------------------------------------------------------------
	    //  Constructors and Destructor
	    // -----------------------------------------------------------------------
	    /** @name Constructors and Destructor */
	    //@{
    
	    /**
          *Default constructor
          */
		Simulation();
    	/**
          *Destructor
          */
		~Simulation();

    	//@}

	    // -----------------------------------------------------------------------
	    //  Getter methods
	    // -----------------------------------------------------------------------
	     /** @name Getter methods */
	    //@{

	    /** Get the Flag class
	      *
	      * This method returns the Flag object that contains all the
	      * flags that are used in the WDSLib
	      *
	      * The returned Flag object is owned by the Simulation class.
	      *
	      * @return A reference to the current Flag class
	      */
		Flag* getFlags(){
			return flag;
		}

		 /** Get the Parameter class
	      *
	      * This method returns the Parameter class that contains all the
	      * parameters that are used in the WDSLib
	      *
	      * The returned Parameter object is owned by the Simulation class.
	      *
	      * @return a refernce to the current Parameter class
	      */
		Parameter* getParameters(){
			return parameter;
		}

		void setD(vector<int>*,vector<double>*,double);
    	//@}



		// -----------------------------------------------------------------------
	    //  Setter Methods
	    // -----------------------------------------------------------------------
	    /** @name Setter Methods */
	    //@{
    
	    /**
          *Set the input directory
          */
		/**
	     * Set the directory of the EPANET input file 
	     *
	     *@param value the user specified input file directory
	     */
		void setInputDirectory(string);

		 /**
          *Set the input filename
          */
		/**
	     * Set the name of the EPANET input file 
	     *
	     *@param value the user specified input file name
	     */
		void setInputFile(string);
    	//@}



  		/** Runs the user selected L1a functions
	      *
	      * This method runs the user selected once before every 
	      * multiple simulation functions. This method parse the config file, which include
	      * flags, parametes, and the EPANET input directory and file name. Followed
	      * by parsing the user specified EPANET input file. Finally, the topology dependent
	      * functions and approximated minimum degree permutationare carried out 
	      * using the adjacency list.
	      *
	      * @param result a Result class
	      * @param config a config file name
	      *
	      * @return A reference to the current Net class
	      */
		Net* L1a(Result *,char *);


  		/** Runs the user selected L2a, L3, and L2b functions
	      *
	      * This method runs the user selected L2a, L3, and L2b functions.
	      *
	      * @param result a Result class
	      */
		void solve(Result *);

  		/** This function reverses the permutations in the L1a functions
	      *
	      * This method reverses the permutations of the user selected L1a function,
	      * which include forest core partitioning, spanning tree and co-tree partioning
	      *	and approximated minimum degree permuatation
	      *
	      * @param result a Result class
	      */
		void L1b(Result *);


  		/** This method displays the results
	      *
	      *
	      * @param net a Net class
	      * @param result a Result class
	      */
		void dispResult(Result*);

		/** This method parses the config file
	      *
	      *
	      * @param configFile the config file name
	      */
		int readConfig(char *);


		/** This method parses the EPANET input file
	      *
	      *
	      * @return a reference to the current Net class
	      */
		Net*  getInputData();

		

	private:
		Flag* flag;					/*!< a Flag class*/
		Net* net;
		Parameter* parameter;		/*!< a Parameter class*/
		Input* input;				/*!< a Input class*/
		Result* result;				/*!< a Result class*/
		string inputDirectory;		/*!< a string that contains the directory of the input*/
		string inputFilename;		/*!< a string that contains the name of the input*/
		GGAsolver *gga;				/*!< a GGAsolver class*/
		RCTMsolver *rctm;			/*!< a RCTMsolver class*/

};



#endif
