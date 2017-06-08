#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <set>
#include "gene.h"

using namespace std;

class Experiment{
    public:
        
        //Constructor
        Experiment();

        //Filters out data averages
        void filter();
            
        //Calculates the preliminary statistics for each gene
        void calcStats();
 
        void parseData();

        //Rank the data based on simple difference from 
        //target average and control average
        //set<GeneEntry> rankByAverageDifference();
        

        //Setters

        void setNumTargetReplic(int num){num_target_replic_ = num;}
        void setNumControlReplic(int num){num_control_replic_ = num;}
        void setRawTuxFile(string name){rawTuxFile_ = name;}
        void setSumTuxFile(string name){sumTuxFile_ = name;}
        void setName(string name){name_ = name;}
        void setMeanThres(int num){mean_threshold_ = num;}
        void setVarThres(int num){var_threshold_ = num;}

        //Getters
        
        //Looks up the gene by name in the map
        //Returns empty GeneEntry if not found
        GeneEntry getGeneEntry(string name);
        int getNumGenes() const ;   
        bool hasGeneEntry(string gene);
        string getLabel(){return name_;}

        //Returns a set copy of all of the genes in this experiment
        unordered_map<string, int> getGenesList();
    private:
        
        // Data files
        string name_;
        string rawTuxFile_;
        string sumTuxFile_;
        int num_target_replic_;
        int num_control_replic_;
        int mean_threshold_;
        int var_threshold_;
        unordered_map<string, GeneEntry> gene_entries_;

};


#endif
