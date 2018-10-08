#ifndef GGAsolver_H
#define GGAsolver_H
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "../solver.h"
#include <limits>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
class GGAsolver: public Solver{
	public:	
		// -----------------------------------------------------------------------
	    //  Constructors and Destructor
	    // -----------------------------------------------------------------------
	    /** @name Constructors and Destructor */
	    //@{
    
	    /**
          *Default constructor
          */
		GGAsolver(Net*,Parameter*,Flag*);
    	/**
          *Destructor
	     */
		~GGAsolver();
    	//@}

		void	runH(Result*);
		//void	initH();
		void 	amd(Result*);


	    /** Solve the heads using the GGA
	   	  *
	      * @param G a vector of the diagonal elements of the matrix G
	      * @param F a vector of the diagonal elements of the matrix F
	      * @param A2el a vector of the A2*el 
	      * @param q a vector of the flows at the current iteration
	      * @param SN a vector of start nodes of all pipes 
	      * @param EN a vector of end nodes of all pipes 
	      *
	      * @return result a vector of heads
	      */
		vector<double>* GGAgetH(vector<double>*,vector<double>*,vector<double>*,
									vector<double>*,vector<int>*,vector<int>*,vector<double>*,string);
		
	private:
		vector<double>* A2el;
};


#endif