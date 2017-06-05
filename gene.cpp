#include "gene.h"

GeneEntry::GeneEntry(string name, bool c, int replicates, int control_replicates){
    name_ = name;
    control_ = c;
       
    target_average_ = 0;
    control_average_ = 0;
    target_stdev_ = 0;
    control_stdev_ = 0;
    fold_change_ = 0;
}

//Return the target average
//Calculates the average if value is not yet stored
double GeneEntry::getTargetAverage(){
    if(target_average_ != 0){
        return target_average_;
    }

    // Calculate target average
    
    double sum = 0;

    for(int i = 0; i < target_values_.size(); ++i){
        sum += target_values_[i];
    }

    target_average_ = sum / target_values_.size();
    
    return target_average_;
}

//Return the control average
//Calculates the average if value is not yet stored
double GeneEntry::getControlAverage(){
    if(control_average_ != 0){
        return control_average_;
    }

    // Calculate target average
    
    double sum = 0;

    for(int i = 0; i < control_values_.size(); ++i){
        sum += control_values_[i];
    }

    control_average_ = sum / control_values_.size();
    
    return control_average_;
}

//Return the target standard deviation
//Calculates if value not yet stored
double GeneEntry::getTargetStDev(){
    if(target_stdev_ != 0){
        return target_stdev_;
    }

    // Calculate the target standard deviation
       
    double var = 0;

    for(int i = 0; i < target_values_; ++i){
        var += pow((target_values_[i] - getTargetAverage()),2);
    }

    var /= target_values_.size();

    target_stdev_ = sqrt(var);

    return target_stdev_;
}

//Return the control standard deviation
//Calculates if value not yet stored
double GeneEntry::getControlStDev(){
    if(control_stdev_ != 0){
        return control_stdev_;
    }

    // Calculate the target standard deviation
       
    double var = 0;

    for(int i = 0; i < control_values_; ++i){
        var += pow((control_values_[i] - getControlAverage()),2);
    }

    var /= control_values_.size();

    control_stdev_ = sqrt(var);

    return control_stdev_;
}

//Return target value at index i
//Returns -1 if index is out of bounds
double GeneEntry::getTargetValueAt(int i){
    if(i < 0 || i >= target_values_.size()){
        return -1;  
    }

    return target_values_[i];
}

//Return control value at index i
//Returns -1 if index is out of bounds
double GeneEntry::getControlValueAt(int i){
    if(i < 0 || i >= control_values_.size()){
        return -1;  
    }

    return control_values_[i];
}

void GeneEntry::addControlValue(double val){
    control_values_.push_back(val);
}

void GeneEntry::addTargetValue(double val){
    target_values_.push_back(val);   
}
