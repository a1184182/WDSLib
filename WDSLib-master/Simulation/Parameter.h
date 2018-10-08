#ifndef Parameter_h
#define Parameter_h

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <stdio.h>


using namespace std;

class Parameter{
	public:
		// -----------------------------------------------------------------------
		//  Constructors and Destructor
	    // -----------------------------------------------------------------------
	    /** @name Constructors and Destructor */
	    //@{
	   
	    /**
          *Default constructor
          *
          *This method set each parameter to its default value
          */
		Parameter();
    	/**
          *Destructor
          */
		~Parameter();

    	//@}



		// -----------------------------------------------------------------------
	    //  Setter Methods
	    // -----------------------------------------------------------------------
	    /** @name Setter Methods */
	    //@{
    
	    /**
          *Set a parameter value 
          */
		/**
	     * This method sets the parameter value of name
	     *
	     *@param name the name of a parameter
	     *@param value the value of the parameter of name
	     */
		void setParameter(string ,double);


    	//@}

		// -----------------------------------------------------------------------
	    //  Getter methods
	    // -----------------------------------------------------------------------
	     /** @name Getter methods */
	    //@{

	    /** Get a parameter value 
	      *
	      * This method returns the parameter value of name
	      *	
	      * @param name the name of a parameter
	      *
	      * @return the value of a parameter
	      */
	     double getParametervalue(string);

    	//@}

	     /**
	      * This method returns the reference to the current Parameter class
	      *
	      * @return A pointer to the current Parameter class.
	      */
		Parameter* returnParameter(){
			return this;
		}

	     /**
	      * This method displays the values of all parameters 
	      *
	      */
	   	void dispParameters();
	private:
	      map<string , double> parameter;
};


#endif

