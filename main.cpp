#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <set>
#include "gene.h"
#include "parsers.h"

using namespace std;


//Remove all data that is above the given stdev threshold
//or below the given mean threshold
void filterGeneEntries(unordered_map<string, GeneEntry>& entries, 
        int mean_threshold, int var_threshold){
    unordered_map<string, GeneEntry>::iterator it, it2;
    for(it = entries.begin(); it != entries.end();){
        
        //DEBUG
        if(it->second.getName() == "Atp5e"){
            cout << "Stdev control of Atp5e is " << it->second.getControlStDev() 
                << " and stdev target is " << it->second.getTargetStDev() << endl;
        }

        //Check if either standard deviations are above the threshold
        if(it->second.getTargetStDev() > var_threshold ||
           it->second.getControlStDev() > var_threshold ||
           it->second.getTargetAverage() < mean_threshold  ||
           it->second.getControlAverage() < mean_threshold ||
           it->second.getControlAverage() > it->second.getTargetAverage() ){
            
            it2 = it;
            ++it;
            
            entries.erase(it2);
            
        }else{
            ++it;
        }
    }
}

// Rank gene entries based on fold change
// copy all of the values from the unordered_map to the set
// Ranking is done by GeneEntry class function comparisons
void rankGeneEntries(unordered_map<string, GeneEntry>& entries, set<GeneEntry>& sorted_entries){
    unordered_map<string, GeneEntry>::iterator it;

    for(it = entries.begin(); it != entries.end(); ++it){
        sorted_entries.insert(it->second);
    }
}

void outputData(set<GeneEntry> entries, int target_replic,
                    int control_replic){
    ofstream out("output.txt");
 
    //Check if file works
    if(!out.is_open()){
        cerr << "Unable to open output file" << endl;
        exit(1);
    }   
    

    // Output file headings

    out << "Gene ID\t";

    //Output the target replicates heading
    for(int i = 0; i < target_replic; ++i){
        out << "T_rep " << i+1 << "\t";
    }

    //Output the control replicates heading
    for(int i = 0; i < control_replic; ++i){
        out << "C_rep " << i+1 << "\t";
    }

    out << "log2\tp_value"<< endl;

    // Output gene entries

    set<GeneEntry>::const_reverse_iterator it;
    for(it = entries.rbegin(); it != entries.rend(); ++it){
        
        //Ouput name
        out << it->getName() << "\t";
      
        //Output the replicate values
        
        for(int i = 0; i < it->numTargetValues(); ++i){
            out << it->getTargetValueAt(i) << "\t";
        }

        for(int i = 0; i < it->numControlValues(); ++i){
            out << it->getControlValueAt(i) << "\t";
        }

        // Output fold change and p value
        out << it->getFoldChange() << "\t";
        out << it->getPValue() << "\t";

        out << endl;
    }

    out.close();
}

int main(int argc, char *argv[]){
    //Local Variables
    string rawTuxFile, sumTuxFile;
    unordered_map<string, GeneEntry> entries;
    int num_target_replic;
    int num_control_replic;
    int var_threshold;
    int mean_threshold;
    
    //------ Prompt user for necessary data --------
    
    //Get number of target replicates
    cout << "Enter the number of target replicates: ";
    cin >> num_target_replic;

    //Get the number of control replicates
    cout << "Enter the number of  control replicates: ";
    cin >> num_control_replic;
    
    //Get the file name of the raw Tuxedo data
    cout << "Enter the file name of the raw Tuxedo data: " << endl;
    cin >> rawTuxFile;
    
    //Get the file name of the summary Tuxedo data
    cout << "Enter the file name of the summary Tuxedo data: " << endl;
    cin >> sumTuxFile;

    //Get the standard deviation threshold
    cout << "Enter the standard deviation threshold: ";
    cin >> var_threshold;

    //Get the average threshold
    cout << "Enter the average threshold: ";
    cin >> mean_threshold;

    //------- Parse all of the gene entries ---------
    parseRawTuxedoData(rawTuxFile, entries, num_control_replic, num_target_replic);
    parseSumaryTuxedoData(sumTuxFile, entries);

    //------- Rank the data -------------------
    // First filter out genes that have a standard deviation that
    // as past the threshold standard deviation
    // then rank based on the fold change
    filterGeneEntries(entries, mean_threshold, var_threshold);
    set<GeneEntry> sorted_entries;
    rankGeneEntries(entries, sorted_entries);

    //------- write all of the sorted genes to a file --------------
    outputData(sorted_entries, num_target_replic, num_control_replic);

    //Parse command-line arguments
    for(int i = 0; i < argc; ++i){
        if(string(argv[i]) == "-"){
            
            //Option to 
        

        }
    }
}
