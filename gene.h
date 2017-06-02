#define _GENEENTRY_

class GeneEntry{
    public:
        //Constructor
        GeneEntry(bool c, int replicates, int control_replicates);
        
        //Deconstructor
        ~GeneEntry();
        
        //Add the value to next array element if available
        //return false if array is filled
        bool addValue(double val);
        

        //Calculates the significance among the values
        double calcSignificance(int threshold);

        //Reports the average value of all the data
        double averageValue();
    private:
        int num_target_replicates_;
        int num_control_replicates_;
        bool control_;
        double * values_;
        double * control_values_;
};

#endif
