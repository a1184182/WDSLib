#ifndef Matrix_H
#define Matrix_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include "cs.h"

using namespace std;

class Matrix//: public Net
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
		Matrix();

		/**
         *Overload constructor
         *
       	 *This method sets the matrix number of rows and number columns 
       	 *
         *@param a Number of matrix rows
         *@param b Number of matrix columns
       */
		Matrix(int,int);

    	/**
      	 *Destructor
      	 */
		~Matrix();
        //@}


		/** 
	     * This method sets each entry of a Matrix by the row index, column index,
	     * and the valye 
	     *
	     * @param col the column index of each entry
	     * @param row the row index of each entry
	     * @param value the value of each entry
	     */
		void triple(int,int,double);

		/** 
	     * Get the density of the current matrix 
	     *  
	     * This method calculates and outputs the density of the current matrix
	     *
	     * @return density of the current matrix 
	     */
		int density();

		/** 
	     * Convert the matrix from triplet form the compressed column format
	     */
		void CCS();

		/** 
	     * Applied the approximate minimum degree permutation 
	     */
		css* amd();
		// -----------------------------------------------------------------------
    	//  Getter methods
    	// -----------------------------------------------------------------------
    	/** @name Getter methods */
    	//@{

   		/** 
   		 *Get the maximum number of entries of the current matrix
   		 *
   		 * @return maximum number of entries
   		 */

		int nzmax(){
			return A->nzmax;
		}
   		/** 
   		 *Get the number of rows of the current matrix
   		 *
   		 * @return number of rows
   		 */
		int nr(){
			return A->m;
		}


   		/** 
   		 *Get the number of columns of the current matrix
   		 *
   		 * @return number of columns
   		 */
		int nc(){
			return A->n;
		}

   		/** 
   		 *Get the vector of column pointers
   		 *
   		 * @return column pointers
   		 */
		int* colp(){
			return A->p;
		}
		

   		/** 
   		 *Get the vector of row indices
   		 *
   		 * @return the row indices
   		 */
		int* rowi(){
			return A->i;
		}

   		/** 
   		 *Get the vector of numerical values
   		 *
   		 * @return numerical values
   		 */
		double* val(){
			return A->x;
		}

		// -----------------------------------------------------------------------
    	//  Getter methods
    	// -----------------------------------------------------------------------
    	/** @name Matrix operations */
    	//@{

	 
	    /** Matrix addition
	      *
	      * This method adds the current matrix A and another matrix b
	      * and result is stored in the Matrix "result"
	      * 
	      * @param b a matrix that added to the current matrix A
	      *
	      * @return the result of the addition
	      */

		Matrix* operator+(const Matrix* b){
			Matrix* result=new Matrix();
			result->A=cs_add(this->A,b->A,1,1);
			return result;
		}

 		/** Matrix subtraction
	      *
	      * This method subtracts the matrix b from the current matrix A 
	      * and result is stored in the Matrix "result"
	      * 
	      * @param b a matrix that subtracted from the current matrix A
	      *
	      * @return the result of the subtraction
	      */
		Matrix* operator-(const Matrix* b){
			Matrix* result=new Matrix();
			result->A=cs_add(this->A,b->A,1,-1);
			return result;
		}

 		/** Matrix multiplication
	      *
	      * This method multiplies the current matrix A and the matrix b
	      * and result is stored in the Matrix "result"
	      * 
	      * @param b a matrix that multiplied by the current matrix A
	      *
	      * @return the result of the multiplication
	      */
		Matrix* operator*(const Matrix* b){
			Matrix* result=new Matrix();
			result->A=cs_multiply(this->A,b->A);
			return result;
		}

 		/** Matrix transpose
	      *
	      * This method transpose the current matrix A
	      * and result is stored in the Matrix "result"
	      * 
	      * @return the result of the transpos
	      */
		Matrix* transpose(){
			Matrix* result=new Matrix();
			result->A=cs_transpose(this->A,1);
			return result;
		}


 		/** Solve a saddle point problem using Cholesky factorization 
	      *
	      * This method factorizes the current matrix using Cholesky factorization 
	      * and solve the saddle point problem using forward and backward substitutions
	      * 
	      * Modification of the original cholsol function from the SUITESPARSE package has been made.
	      *	 The approximate minimum degree permutation has been factored out of the cholsol function.
	      * This is because the AMD permutation is the same for the same topology.
	      * @param S the AMD permutation vector 
	      * @param b the RHS of the equation
	      */
		CS_INT cholsol(css  *S,const cs *A,CS_ENTRY *b){
		    CS_ENTRY *x ;
		    csn *N ;
		    CS_INT n, ok ;
		    if (!CS_CSC (A) || !b) return (0) ;     /* check inputs */
		    n = A->n ;
		    N = cs_chol (A, S) ;                    /* numeric Cholesky factorization */
		     x = (CS_ENTRY *) calloc(n,sizeof(CS_ENTRY));
  			ok = (S && N && x) ;
		    if (ok)
		    {
		        cs_ipvec (S->pinv, b, x, n) ;   /* x = P*b */
		        cs_lsolve (N->L, x) ;           /* x = L\x */
		        cs_ltsolve (N->L, x) ;          /* x = L'\x */
		        cs_pvec (S->pinv, x, b, n) ;    /* b = P'*x */
		    }
		    cs_free (x) ;
		    cs_nfree (N) ;
		    return (ok) ;
		}


 		/** Solves sparse symmetric system of linear equations using Cholesky factorization
	      *
	      * This method solves the sparse symmetric system of linear equations \f$Ax=b\f$.
	      * It starts with factorizing the current matrix \f$A$\f using Cholesky factorization
	      * 
	      * Modification of the original cholsol function from the SUITESPARSE package has been made.
	      *	 The approximate minimum degree permutation has been factored out of the cholsol function.
	      * This is because the AMD permutation is the same for the same topology.
	      * @param pamd the AMD permutation vector 
	      * @param input the RHS of the equation
	      * @return the result vector x
	      */
	      vector<double>* linsolve(css* S,CS_ENTRY *b){
	      	vector<double> *output;
			CS_ENTRY *x ;
		    csn *N ;
		    CS_INT n, ok ;
		    if (!CS_CSC (A) || !b) return (0) ;     /* check inputs */
		    n = A->n ;
		    output=new vector<double>(n);
		    N = cs_chol (A, S) ;                    /* numeric Cholesky factorization */
		  //  cout<<*(S->parent)<<","<<*(S->cp)<<endl;
		    x = (CS_ENTRY *) calloc(n,sizeof(CS_ENTRY));
  			ok = (S && N && x) ;
		    if (ok)
		    {
		        cs_ipvec (S->pinv, b, x, n) ;   /* x = P*b */
		        cs_lsolve (N->L, x) ;           /* x = L\x */
		        cs_ltsolve (N->L, x) ;          /* x = L'\x */
		        cs_pvec (S->pinv, x, b, n) ;    /* b = P'*x */
		    }
		    cs_free (x) ;
		    cs_nfree (N) ;
			for(int i=0;i<output->size();i++)	(*output)[i]=b[i];
				return output;
		}
		/*vector<double>* linsolve(css* pamd,vector<double>* input){
			double *LHS;
			vector<double>* output=new vector<double>(input->size());
  			LHS=(double *) calloc(input->size(),sizeof(double));
  			for(unsigned int i =0;i<input->size();i++) LHS[i]=(*input)[i];
			cholsol(pamd,this->A,LHS);
			int size = nr();
			for(int i=0;i<size;i++)	(*output)[i]=LHS[i];
			free(LHS);
			return output;
		}*/


	    /** Get the norm of the current matrix
	      * @return norm
	      *
	      */
		double norm(){
			return cs_norm(A);
		}

		vector<double>* operator*(const vector<double>* b){
			CS_INT p, j, n,m, *Ap, *Ai ;
    		CS_ENTRY *Ax ;
    		vector<double> *result=new vector<double>();
    		n = A->n ; m=A->m ;Ap = A->p ; Ai = A->i ; Ax = A->x ;
    		for(int i=0;i<m;i++)	result->push_back((double)0.0);
		    for (j = 0 ; j < n ; j++)
		    {
		        for (p = Ap [j] ; p < Ap [j+1] ; p++)
		        {
		        	if(Ax [p]==1)	(*result) [Ai [p]] +=(double) (*b) [j] ; 
		        	else if(Ax [p]==-1)	(*result) [Ai [p]] -=(double) (*b) [j] ; 
		            else   (*result) [Ai [p]] += Ax [p] *((double) (*b) [j]) ; 
		        }
		    }
		    return result;
		}

		Matrix* bitwise(vector<double>* input,int j){
			double *LHS;
  			LHS=(double *) calloc(input->size(),sizeof(double));
  			for(unsigned int i =0;i<input->size();i++) LHS[i]=(*input)[i];
			Matrix *result = new Matrix();
			int np=this->nc();
			int nj=this->nr();
			Matrix *M1 = new Matrix(np,np);
			for(int i=0;i<np;i++){
				if(j==1) M1->triple(i,i,1.0/LHS[i]);
				else if(j==2) M1->triple(i,i,LHS[i]);
			}
			M1->CCS();
			result->A=cs_multiply(this->A,M1->A);
			free(LHS);
			delete M1;
			return result;
		}

		vector<double>* fTSub(const vector<double>* input){
			double *LHS;
  			LHS=(double *) calloc(input->size(),sizeof(double));
  			for(unsigned int i =0;i<input->size();i++) LHS[i]=(*input)[i];
			vector<double>* result=new vector<double>();
			cs_ltsolve(this->A,LHS);
			int size = nr();
			//b->clear();
			for(int i=0;i<size;i++){
				result->push_back(LHS[i]);
			}
			//this->printMatrix();
			free(LHS);
			return result;
		}
		
		vector<double>* fSub(const vector<double>* input){
			double *LHS;
  			LHS=(double *) calloc(input->size(),sizeof(double));
  			for(unsigned int i =0;i<input->size();i++) LHS[i]=(*input)[i];
			vector<double>* result=new vector<double>();
			cs_lsolve(this->A,LHS);
			int size = nr();
			//b->clear();
			for(int i=0;i<size;i++){
				result->push_back(LHS[i]);
			}
			//this->printMatrix();
			free(LHS);
			return result;
		}

        //@}

		/**
	      * This method displays the current matrix
	      */
		int printMatrix(int);

		//Access function

	private:
		cs *A;
};





#endif
