#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <iostream>
#include <string>

using namespace std;

class Experiment{
    public:

        //Filters out data averages
        void filter();

        //Rank the data based on simple difference from 
        //target average and control average
        void rankByAverageDifference();

    
    private:
        // Data files
        string rawTuxFile_;
        string sumTuxFile_;
        

};


#endif
