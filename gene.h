#define _GENEENTRY_

class GeneEntry{
    public:
        //Constructor
        GeneEntry(string name);
        
        //Add the value to next array element if available
        //return false if array is filled
        void addTargetValue(double val);
        void addControlValue(double val);

        // Getters
        
        string getName(){return name_;}
        double getTargetAverage();
        double getControlAverage();
        double getTargetStDev();
        double getControlStDev();
        double getTargetValueAt(int i);
        double getControlValueAt(int i);
        double getFoldChange(){return fold_change_;}
        int numTargetValues(){return target_values_.size();}
        int numControlValues(){return control_values_.size();}
    
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
