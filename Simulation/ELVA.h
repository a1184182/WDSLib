#ifndef ELVA_H
#define ELVA_H

#include <string>
#include <map>
#include <iostream>
#include <time.h>
#include <utility>
#include <stdio.h>
#ifdef __linux__ 
    #include <sys/time.h>
#elif _WIN32
    #include <windows.h>
#endif



using namespace std;


class CPUcycle{
    public:
        // -----------------------------------------------------------------------
        //  Constructors and Destructor
        // -----------------------------------------------------------------------
        /** @name Constructors and Destructor */
        //@{
       
        /**
          *Default constructor
          */
        CPUcycle();
        /**
          *Destructor
          */
        ~CPUcycle();
        //@}

        /**
          * This method samples the current wall clock time 
          *
          * @param function the name of the function of interest
          * @param location the start or the end of the function
          */
        void SampleCPUCycle(string, string);

         /**
          * This method displays the time spend in each of the sampled functions 
          *
          */
        void DispCPUtime();


         /**
          * This method returns the time spend in each of the sampled functions 
          *
          * @return the time spend in each of the sampled functions 
          */
        map<string , long double> getTiming(){ return timespend;};


    private:
        map<string , long double> Time_start;
        map<string , long double> Time_end;
        map<string , long double> timespend;


};




#endif


