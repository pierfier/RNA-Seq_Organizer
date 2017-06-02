#include "gene.h"

GeneEntry::GeneEntry(bool c, int replicates){
    control_ = c;
    num_replicates_ = replicates;
    
    values_ = new double[num_replicates_];

    //Initialize elements to zero
    for(int i = 0; i < num_replicates_; ++i){
        values_[i] = 0;
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

bool GeneEntry::addValue(double val){
    // Return if value is zero
    if(val == 0){
        return true;
    }

    // Find a zero element 
    for(int i = 0; i < num_replicates_; ++i){
        if(values_[i] == 0){
            values_[i] = val;
            return true;
        }   
    }

    return false;
}

GeneEntry::~GeneEntry(){
    delete [] values_;
}
