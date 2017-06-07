#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Experiment{
    public:

        //Filters out data averages
        void filter();

        //Rank the data based on simple difference from 
        //target average and control average
        void rankByAverageDifference();
        
        //Getters
        GeneEntry getGeneEntryAt(int i);
        GemeEmtry getGeneEntry(string name);
        int getNumGenes() const ;   
        bool hasGeneEntry(string gene) const;
    private:
        // Data files
        string rawTuxFile_;
        string sumTuxFile_;
        unordered_map<string, GeneEntry> gene_entries_;

};


#endif
