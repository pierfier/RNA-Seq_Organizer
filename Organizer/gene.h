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
        
        // Setters

        void addTargetValue(double val);
        void addControlValue(double val);
        void setName(const string& name){name_ = name;}
        void setFoldChange(const string& val){fold_change_ = val;}
        void setPValue(const string& val){pValue_ = val;}

        //Prints all of the data to the output stream
        void printData(ostream& out);

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
        int numTargetValues() const {return target_values_.size();}
        int numControlValues() const {return control_values_.size();}
        string getPValue() const {return pValue_;}
        string getFoldChange() const {return fold_change_;}
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
        string fold_change_;
        string pValue_;

        //Store values
        vector<double> target_values_;
        vector<double> control_values_;
};

#endif
