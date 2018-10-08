#ifndef result_H
#define result_H
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <iomanip>
#include "../Simulation/ELVA.h"
#include "../Network/Edge/PIPES/pipe.h"
#include "../Network/Vertex/NODE/node.h"

using namespace std;

class Result{
	public:
		// -----------------------------------------------------------------------
	    //  Constructors and Destructor
	    // -----------------------------------------------------------------------
	    /** @name Constructors and Destructor */
	    //@{
    
	    /**
          *Default constructor
          */
		Result();
    	/**
          *Destructor
          */
		~Result();

    	//@}


		// -----------------------------------------------------------------------
	    //  Setter Methods
	    // -----------------------------------------------------------------------
	    /** @name Setter Methods */
	    //@{

	    /** Set the flow solutions
	   	  *
	   	  * This method parses the flow solutions and stores in the current Result class
	   	  * 
	      * @param input flow solutions
	      *
	      */
		void setQsol(vector<double>*);

	    /** Set the head solutions
	   	  *
	   	  * This method parses the head solutions and stores in the current Result class
	   	  * 
	      * @param input head solutions
	      *
	      */
		void setHsol(vector<double>*);

	    /** Set the required number of iterations  
	   	  *
	   	  * This method parses the number of iterations required and stores in the current Result class
	   	  * 
	      * @param input the required number of iterations 
	      *
	      */
		void setIteration(int);

	    /** Set the final G and F matrices
	   	  *
	   	  * This method parses the diagonal entries of the G and F matrices 
	   	  * and stores in the current Result class
	   	  * 
	      * @param G the scaled diagonal entries of the matrix G
	      * @param F the scaled diagonal entries of the matrix F
	      * @param Gscale scaling factor for matrices G and F
	      *
	      */
		void setGFfinal(vector<double>* ,vector<double>*  );
	
	    /** Set the initial guesses of flows and heads
	   	  *
	   	  * This method parses the initial guesses of flows and heads
	   	  * and stores in the current Result class
	   	  * 
	      * @param qi a vector of the initial flow guesses 
	      * @param hi a vector of the initial head guesses 
	      *
	      */        
		void setQHinit(vector<double>* ,vector<double>* );

	
	    /** Set the iterative pipe results
	   	  *
	   	  * This method parses the iterative pipe results
	   	  * and stores in the current Result class
	   	  * 
	      * @param iterator the current iteration number 
	      * @param q a vector of the scaled flows for current iteration
	      * @param G a vector of the scaled diagonal entries of the matrix G 
	      * 			of the current iteration
	      * @param F a vector of the scaled diagonal entries of the matrix G 
	      * 			of the current iteration
	      * @param qScale scaling factor for flows
	      * @param Gscale scaling factor for matrices G and F
	      *
	      */ 
		void setPipeIterResult(int,vector<double>* ,vector<double>* ,vector<double>* ,double ,double);
		void setNodeIterResult(int,vector<double>* ,double);

	    /** Set the iterative node results
	   	  *
	   	  * This method parses the iterative node results
	   	  * and stores in the current Result class
	   	  * 
	      * @param iterator the current iteration number 
	      * @param h a vector of the scaled heads for current iteration
	      * @param hScale scaling factor for heads
	      *
	      */ 
		void setNodeResult(int,vector<double>* ,double);

		/** Set the iterative norms
	   	  *
	   	  * This method parses the iterative norm
	   	  * and stores in the current Result class
	   	  * 
	      * @param norm the current iteration number 
	      * @param cRes the current continuity residual
	      * @param eRes the current energy residual
	      *
	      */ 
	    void setIterNorm(double );



	    void setIterResidual(double , double );
	    /** Set the final norm
	   	  *
	   	  * This method parses the final norm
	   	  * and stores in the current Result class
	   	  * 
	      * @param cRes the final continuity residual
	      * @param eRes the final energy residual
	      *
	      */ 
	    void setFinalNorm(double ,double  );

	    

    	//@}

	    // -----------------------------------------------------------------------
	    //  Getter methods
	    // -----------------------------------------------------------------------
	     /** @name Getter methods */
	    //@{


   		/** 
   		 *Get the vector of Iterative user selected norms 
   		 *
   		 * @return iterative norms 
   		 */
	    vector<double> getIterNorm(){
			return normIter;
		}  
	    
   		/** 
   		 *Get the number of iterations
   		 *
   		 * @return  required number of iteration
   		 */
		int getIteration(){
			return iterator;
		}


   		/** 
   		 *Get the vector of Iterative energy residuals
   		 *
   		 * @return Iterative energy residuals
   		 */
	    vector<double> getIterEres(){
			return EresIter;
		}  
	    
	    
   		/** 
   		 *Get the vector of Iterative continuity residuals
   		 *
   		 * @return Iterative continuity residuals
   		 */
	    vector<double> getIterCres(){
			return CresIter;
		}  
	    
   		/** 
   		 *Get the final user selected norms 
   		 *
   		 * @return final norms 
   		 */
	    double getFinalNorm(){
			return normFinal;
		}
	
   		/** 
   		 *Get the final user selected energy residual 
   		 *
   		 * @return final energy residual 
   		 */    
	    double getFinalEres(){
			return EresFinal;
		}
	
   		/** 
   		 *Get the final user selected continuity residual 
   		 *
   		 * @return final continuity residual 
   		 */    
	    double getFinalCres(){
			return CresFinal;
		}
	
   		/** 
   		 *Get the initial guesses of flows
   		 *
   		 * @return the initial guesses of flows
   		 */    	    
	    vector<double> getQinit(){
	        return qinit;
	    }
	    	
   		/** 
   		 *Get the initial guesses of heads
   		 *
   		 * @return the initial guesses of heads
   		 */    	    
	    vector<double> getHinit(){
	        return hinit;
	    }
	    	
   		/** 
   		 *Get the final flows
   		 *
   		 * @return a vector of final flows
   		 */    	    
	    vector<double> getQsol(){
	        return qsol;
	    }
	    
   		/** 
   		 *Get the final heads
   		 *
   		 * @return a vector of final heads
   		 */    	    
	    vector<double> getHsol(){
	        return hsol;
	    }
	       
   		/** 
   		 *Get the flows for every iterations 
   		 *
   		 * @return the flows for every iterations
   		 */    	    
	    vector<vector<double> > getQiter(){
	        return qiter;
	    }
	       
   		/** 
   		 *Get the heads for every iterations 
   		 *
   		 * @return the heads for every iterations
   		 */    	    
	    vector<vector<double> > getHiter(){
	        return hiter;
	    }
	          
	       
   		/** 
   		 *Get the diagonal elements of the matrix G for every iterations 
   		 *
   		 * @return the diagonal elements of the matrix G for every iterations 
   		 */    
	    vector<vector<double> > getGiter(){
	        return Giter;
	    }	      
	       
   		/** 
   		 *Get the diagonal elements of the matrix F for every iterations 
   		 *
   		 * @return the diagonal elements of the matrix F for every iterations 
   		 */    
	    vector<vector<double> > getFiter(){
	        return Fiter;
	    }
	    
	    /** 
   		 *Get the diagonal elements of the matrix G for final iterations 
   		 *
   		 * @return the diagonal elements of the matrix G for final iterations 
   		 */    	    
	    vector<double> getGfinal(){
	        return Gfinal;
	    }
	    
	    /** 
   		 *Get the diagonal elements of the matrix F for final iterations 
   		 *
   		 * @return the diagonal elements of the matrix F for final iterations 
   		 */    	 
	    vector<double> getFfinal(){
	        return Ffinal;
	    }    

	    /** 
   		 *Get the timing results 
   		 *
   		 * @return the timing results 
   		 */    	      

	     map<string , long double> getTiming(){ return CPUsample1.getTiming();}

    	//@}


	    /** 
   		 *Sample the current wall clock time at either the beginning or the end of a function
   		 *
   		 * @param function the function of the interest
   		 * @param position either the beginning or the end of "function"
   		 */    	 
	    void SampleCPUCycles(string function, string position){
	    	CPUsample1.SampleCPUCycle(function, position);
	    }   
	            
  		/** This method displays the timing of the functions sampled
	      *
	      */
	    void DispCPUtime(ostream& stream){
	    	CPUsample1.DispCPUtime(stream);
	    }          
       
  		/** This method resets the timing of the functions sampled
	      *
	      */
	    void resetTiming(){
	    	map<string , long double> Time=getTiming();
	    	Time.clear();
	    }

       
  		/** This method displays the initial flows and heads 
	      *
	      */
		void dispQHinit();

  		/** This method displays the iterative flows 
	      *
	      */
		void dispQiter(ostream&,PIPE *);
		void dispHiter(ostream&,NODE *);

	private:
		int	   iterator;	 
	    double normFinal;
	    double EresFinal;
	    double CresFinal;
		vector<double> qsol;
		vector<double> hsol;
		vector<double> qinit;
		vector<double> hinit;
		vector<double> normIter;
		vector<double> CresIter;
		vector<double> EresIter;
		vector<double> Gfinal;
		vector<double> Ffinal;
		vector<vector<double> > qiter;
		vector<vector<double> > Giter;
		vector<vector<double> > Fiter;
		vector<vector<double> > hiter;
		CPUcycle CPUsample1;
};

#endif