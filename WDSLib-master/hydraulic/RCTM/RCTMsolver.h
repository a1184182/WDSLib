#ifndef RCTMsolver_H
#define RCTMsolver_H
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "../solver.h"
#include <limits>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
class RCTMsolver: public Solver{
	public:
		// -----------------------------------------------------------------------
	    //  Constructors and Destructor
	    // -----------------------------------------------------------------------
	    /** @name Constructors and Destructor */
	    //@{
    
	    /**
          *Default constructor
          */
		RCTMsolver(Net*,Parameter*,Flag*);
    	/**
          *Destructor
	     */
		~RCTMsolver();

    	//@}
		void 	amd(Result*);
		void	runH(Result*);

		/** Solve the flows in the cotree pipes using the RCTM
	   	  *
	      * @param L21 a part of a basis for the null space of the permutated node-arc 
	      * 			incidence matrix for RCTM
	      * @param F a vector of the diagonal elements of the matrix F
	      * @param G a vector of the diagonal elements of the matrix G
	      * @param nj number of junctions
	      * @param q a vector of the flows at the current iteration
	      * @param dm a vector of demands
	      *
	      * @return output flows in the cotree pipes
	      */
		vector<double>* CotreeFlow(Matrix*,vector<double> *,vector<double> *,int ,
					vector<double> *,vector<double> *);


		/** Solve the flows in the cotree pipes using the RCTM
	   	  *
	      * @param L21 a part of a basis for the null space of the permutated node-arc 
	      * 			incidence matrix for RCTM
	      * @param qct flows in the cotree pipes
	      *
	      * @return qST flows in the spanning tree pipes
	      */
		vector<double>* SpanningtreeFlow(Matrix* ,const vector<double>* );

	private:

		vector<double>* T1Tdm;	
		vector<double>* a1;
		vector<double>* a2;
};


#endif