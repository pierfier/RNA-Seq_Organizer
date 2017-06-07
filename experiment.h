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
        
        //Setters

        void setNumTargetReplic(int num){num_target_replic_ = num;}
        void setNumControlReplic(int num){num_control_replic_ = num;}
        void setRawTuxFile(string name){rawTuxFile_ = name;}
        void setSumTuxFile(string name){sumTuxFile_ = name;}
        void setName(string name){name_ = name;}
        void setMeanThres(int num){mean_threshold_ = num;}
        void setVarThres(int num){var_threshold_ = num;}

        //Getters

        GeneEntry getGeneEntryAt(int i);
        GemeEmtry getGeneEntry(string name);
        int getNumGenes() const ;   
        bool hasGeneEntry(string gene) const;

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
