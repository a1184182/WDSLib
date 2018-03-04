#ifndef solver_H
#define solver_H
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "../math/Matrix.h"
#include "../Network/Geometry/topology.h"
#include "../Network/Net.h"
#include "../Simulation/Parameter.h"
#include "../Simulation/Flag.h"
#include "result.h"
#include <math.h>
#define ALFCOLS 4

#include <limits>
#define _USE_MATH_DEFINES
using namespace std;


class Solver{
	public:

   		/** 
   		 *Virtual function for approximate minimum degree permutation
   		 *
   		 */
		virtual void amd(Result*){return;};

   		/** 
   		 *Virtual function for performing hydrauic simulation  
   		 *
   		 */
		virtual void runH(Result*){return;};

	    /** Calculate the user selected norm of a vector 
	   	  *
	      * @param Input a input vector
	      * @param NormTyp 1 for 1-norm 2 for 2-norm and 3 for inf-norm
	      *
	      */
		double NORM(vector<double>* ,int );

	    /** Check whether or not there is improvement of the existing iteration
	   	  *
	   	  * Check the improvement of the current iteration by fitting the last five norms
	   	  * to a curve using singular value decomposition. If the slope is less than the 
	   	  * user selected value, terminate the iterations 
	   	  *
	      * @param parameter a Parameter class
	      * @param norm a vector of the iterative norms 
	      *
	      */
		bool MinInprov(Parameter* ,vector<double> );

	    /** Post-processing of the forest-core partitioning algorithm
	   	  *
	   	  * Calculate the heads in the forest nodes
	   	  *
	      * @param result a Result class
	      * @param topology a Topology class
	      *
	      */
		void	reverseFCPA(Result*,Topology*); 

	    /** Perform scaling
	   	  *
	   	  *
	      * @param Algorithm The type of the solution method 1 for GGA and 2 for RCTM
	      *
	      */
		void	getscale(int);

		 /** Initialize the flows and heads
	   	  *
	   	  *
	      * @param diameter a vectot of pipe diameters
	      * @param V user selected initial velocity
	      * @param unit length unit
	      * @param Algorithm The type of the solution method 1 for GGA and 2 for RCTM
	      * @param nj number of junctions 
	      * @param q output initial flows
	      * @param h output heads
	      */
		void 	initQH(vector<double> *,double ,string,int,
						int ,vector<double>* ,vector<double>*);

		 /** Calculate the resistance invariant 
	   	  *
	   	  *
	      * @param length a vectot of pipe length
	      * @param rougness a vectot of pipe roughness
	      * @param diameter a vectot of pipe diameters
	      * @param hdlss The type of the head loss model 1 for DW and 0 for HW
	      * @param unit length unit 
	      *
	      * @return a vector of resistance invariants
	      */
		vector<double>*	getRF(vector<double>* ,vector<double>* ,vector<double>* ,string ,string );
		
		 /** Calculate the Darcy-Weisbach G and F matrices 
	   	  *
	   	  * @param rf vector of resistance invariants
	      * @param rougness a vectot of pipe roughness
	      * @param diameter a vectot of pipe diameters
	      * @param q a vector of pipe flows of the current iteration
	      * @param nu kinetic viscosity of water
	      * @param unit length unit 
	      * @param G the diagonal element of matrix G
	      * @param F the diagonal element of matrix F
	      *
	      */
		void getDWGF(vector<double>* ,vector<double>* ,vector<double>* ,vector<double> *,double,string 
			,vector<double>* ,vector<double>* );

		 /** Calculate the Darcy-Weisbach G and F matrices 
	   	  *
	   	  * @param rf vector of resistance invariants
	      * @param q a vector of pipe flows of the current iteration
	      * @param G the diagonal element of matrix G
	      * @param F the diagonal element of matrix F
	      *
	      */
		void getHWGF(vector<double>* ,vector<double>* ,vector<double>* ,vector<double>* );
		

	    /** Calculate the user selected norm of the relative difference of two vectors 
	   	  *
	      * @param qnew a vector of flows of the current iteration
	      * @param q a vector of flows of the last iteration
	      * @param hnew a vector of heads of the current iteration
	      * @param h a vector of flows of the last iteration
	      * @param StopTest the type of the stopping test
	      * 					1 for q-norm, 2 for h-norm 3 for q&h-norm
	      * @param NormTyp the type of the norm 
	      *					1 for 1-norm 2 for 2-norm and 3 for inf-norm
	      *
	      */
		double getnorm(vector<double>* ,vector<double>* ,vector<double>* ,
			vector<double>* ,int,int); 

	    /** Post-processing
	   	  *
	   	  *
	      * @param result a Result class
	      *
	      */
		void reverseH(Result*);

		Net* getNet(){return Core;};

	protected:
		Topology 		*topology;
		
		double			Lscale,
						Dscale,
						Rscale,	
						Zscale,
						DMscale,
						qScale,
						hScale,
						Gscale;

		vector<int>		*pRow,
			 			*pCol,
			 			*pFRow,
			 			*pFCol;

		double 			visco;	

		double			modifier1,
						modifier2,
						modifier3,
						modifier4,
						modifier5,
						modifier6;

			 			
		vector<double>	*q,
						*h,
						*qinit,
						*hinit,
						*qsol,
						*hsol;
		css* pamd;
		Net* net;
		Net* Core;
		Flag* flag;		
		Parameter		*parameter	;

		const double  opttf 	= 1.32547452761959950264041659714;
		const double  PI    	= 3.14159265358979323846264338328;
		const double  PI16  	= 50.2654824574366918154022941325;
		const double  PI4   	= 0.785398163397448309615660845820;
		const double  b     	= 0.27027027027027027027027027027;
		const double  Re2	= 3.288954763453990e-03;
};

#endif
