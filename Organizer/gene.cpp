#include "gene.h"
#include <string>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

GeneEntry::GeneEntry(){
    name_ = string("");
       
    target_average_ = 0;
    control_average_ = 0;
    target_stdev_ = 0;
    control_stdev_ = 0;
    fold_change_ = "";
    pValue_ = "";
}

void GeneEntry::calcStats(){
    // Calculate target average

    double sum = 0;

    for(int i = 0; i < target_values_.size(); ++i){
        sum += target_values_[i];
    }

    target_average_ = sum / target_values_.size();
    
    // Calculate control average

    sum = 0;
    for(int i = 0; i < control_values_.size(); ++i){
        sum += control_values_[i];
    }

    control_average_ = sum / control_values_.size();
    
    // Calculate target standard deviation
    
    double var = 0;

    for(int i = 0; i < target_values_.size(); ++i){
        var += pow((target_values_[i] - getTargetAverage()),2);
    }

    var /= target_values_.size();

    target_stdev_ = sqrt(var);

    // Calculate control standard deviation

    var = 0;
    for(int i = 0; i < control_values_.size(); ++i){
        var += pow((control_values_[i] - getControlAverage()),2);
    }

    var /= control_values_.size();

    control_stdev_ = sqrt(var);
}

//Return target value at index i
//Returns -1 if index is out of bounds
double GeneEntry::getTargetValueAt(int i) const {
    if(i < 0 || i >= target_values_.size()){
        return -1;  
    }

    return target_values_[i];
}

//Return control value at index i
//Returns -1 if index is out of bounds
double GeneEntry::getControlValueAt(int i) const {
    if(i < 0 || i >= control_values_.size()){
        return -1;  
    }

    return control_values_[i];
}

void GeneEntry::printData(ostream& out){
    
    //Output the fold change and the P Value
    out << getFoldChange() << "\t" << getPValue() << "\t";
    
    // Output the control raw counts
    for(int i = 0; i < numControlValues(); ++i){
        out << control_values_[i] << "\t";
    }

    // Output the target raw counts
    for(int i = 0; i < numTargetValues(); ++i){
        out << target_values_[i] << "\t";
    }
}

void GeneEntry::addControlValue(double val){
    control_values_.push_back(val);
}

void GeneEntry::addTargetValue(double val){
    target_values_.push_back(val);   
}
