#ifndef GENEENTRY_H
#define GENEENTRY_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class GeneEntry{

    public:
        
        //Constructor
        GeneEntry();
        
        //Add the value to next array element if available
        //return false if array is filled
        void addTargetValue(double val);
        void addControlValue(double val);
        void setName(const string& name){name_ = name;}

        //Calculate all of the averages and standard deviations
        void calcStats();

        // Getters
        
        string getName() const {return name_;}
        double getTargetAverage() const {return target_average_;}
        double getControlAverage() const {return control_average_;}
        double getTargetStDev() const {return target_stdev_;}
        double getControlStDev() const {return control_stdev_;}
        double getTargetValueAt(int i) const;
        double getControlValueAt(int i) const;
        double getFoldChange() const {return fold_change_;}
        int numTargetValues() const {return target_values_.size();}
        int numControlValues() const {return control_values_.size();}

        //Used for inserting into the set
        bool operator<(const GeneEntry& ge) const {
            return (getTargetAverage() - getControlAverage()) < (ge.getTargetAverage() - ge.getControlAverage());}

    private:
        //Name of the gene or the gene id
        string name_;
        
        //Store the standard deviation and mean
        double target_average_;
        double control_average_;
        double target_stdev_;
        double control_stdev_;
        
        //Store the fold change
        double fold_change_;

        //Store values
        vector<double> target_values_;
        vector<double> control_values_;
};

#endif
