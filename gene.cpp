#include "gene.h"

GeneEntry::GeneEntry(bool c, int replicates, int control_replicates){
    control_ = c;
    num_target_replicates_ = replicates;
    num_control_replicates_ = control_replicates;

    values_ = new double[num_replicates_];

    //Initialize elements to zero
    for(int i = 0; i < num_control_replicates_; ++i){
        control_values_[i] = 0;
    }
    for(int i = 0; i < num_target_replicates_; ++i){
        target_values_[i] = 0;
    }
}

double GeneEntry::calcSignificance(int threshold){
  
}

double GeneEntry::averageValue(){
    double sum = 0;

    for(int i = 0; i < num_replicates_; ++i){
        sum += values_[i];
    }

    return sum/num_replicates_;
}

bool GeneEntry::addControlValue(double val){
    // Return if value is zero
    if(val == 0){
        return true;
    }

    // Find a zero element 
    for(int i = 0; i < num_control_replicates_; ++i){
        if(control_values_[i] == 0){
            control_values_[i] = val;
            return true;
        }   
    }

    return false;
}

bool GeneEntry::addTargetValue(double val){
    // Return if value is zero
    if(val == 0){
        return true;
    }

    // Find a zero element 
    for(int i = 0; i < num_target_replicates_; ++i){
        if(target_values_[i] == 0){
            target_values_[i] = val;
            return true;
        }   
    }

    return false;
}

GeneEntry::~GeneEntry(){

    //Free up arrays
    delete [] target_values_;
    delete [] control_values_;
}
