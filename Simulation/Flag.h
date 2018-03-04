#ifndef Flag_h
#define Flag_h

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <stdio.h>

using namespace std;

class Flag{

	public:
		// -----------------------------------------------------------------------
		//  Constructors and Destructor
	    // -----------------------------------------------------------------------
	    /** @name Constructors and Destructor */
	    //@{
	   
	    /**
          *Default constructor
          *
          *This method set each flag to its default value
          */
		Flag();
	
    	/**
          *Destructor
          */
		~Flag();

    	//@}



		// -----------------------------------------------------------------------
	    //  Setter Methods
	    // -----------------------------------------------------------------------
	    /** @name Setter Methods */
	    //@{
    
	    /**
          *Set a flag value 
          */
		/**
	     * This method sets the flag value of name
	     *
	     *@param name the name of a flag
	     *@param value the value of the flag of name
	     */
		void setFlag(string ,int);


    	//@}

		// -----------------------------------------------------------------------
	    //  Getter methods
	    // -----------------------------------------------------------------------
	     /** @name Getter methods */
	    //@{

	    /** Get a flag value 
	      *
	      * This method returns the flag value of name
	      *	
	      * @param name the name of a flag
	      *
	      * @return the value of a flag
	      */
	    int getFlagvalue(string);

    	//@}

	     /**
	      * This method returns the reference to the current Flag class
	      *
	      * @return A pointer to the current Flag class.
	      */
		Flag* returnFlag(){		return this;   }

	     /**
	      * This method displays the values of all flags 
	      *
	      */
	     void dispFlags();
	private:
	      map<string , int> flag;
};


#endif

