#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <stdlib.h>
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

void outputData(set<GeneEntry> entries, const string& outputFile, int target_replic,
                    int control_replic){
    ofstream out(outputFile);
 
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

//Prints all of the commands and how to use them
void printHelp(){
    //TODO implement this method whenever
    //Indicate that the order of execution is what happens in the program
}

int main(int argc, char *argv[]){
    //Local Variables
    string rawTuxFile, sumTuxFile, rawTreatFile, outputFile;
    unordered_map<string, GeneEntry> entries;
    set<GeneEntry> sorted_entries;
    
    int num_target_replic;
    int num_control_replic;
    int var_threshold;
    int mean_threshold;
       
    //Check arguments for configuration options
    for(int i = 0; i < argc; ++i){
        
        //Option to parse raw Tuxedo data
        if(string(argv[i]) == "-rt"){
            rawTuxFile = string(argv[i + 1]);

        //Op#include <stdlib.h>tion to parse summary Tuxedo data
        }else if(string(argv[i]) == "-st"){
            sumTuxFile = string(argv[i + 1]);

        //Option to parse raw two treatment counts data
        }else if(string(argv[i]) == "-r2"){
            rawTreatFile = string(argv[i + 1]);
            
        //Option for mean threshold
        }else if(string(argv[i]) == "-mt"){
            mean_threshold = atoi(argv[i + 1]); //TODO check if this works
        
        //Option for standard deviation threshold
        }else if(string(argv[i]) == "-vt"){
            var_threshold = atoi(argv[i + 1]);

        //Option for number of target replicates
        }else if(string(argv[i]) == "-ntr"){
            num_target_replic = atoi(argv[i + 1]);

        //Option for number of control replicates
        }else if(string(argv[i]) == "-ncr"){
            num_control_replic = atoi(argv[i + 1]);

        }else if(string(argv[i]) == "-o"){
            outputFile = string(argv[i + 1]);
        }
    }
        //Parse the data
        parseRawTuxedoData(rawTuxFile, entries, num_control_replic, num_target_replic);
        parseSumaryTuxedoData(sumTuxFile, entries);
        
        //Filter the genes
        filterGeneEntries(entries, mean_threshold, var_threshold);        
        
        //Rank genes based on difference between the target average and control average
        rankGeneEntries(entries, sorted_entries);
        
        //Ouput data to given file
        outputData(sorted_entries, outputFile, num_target_replic, num_control_replic);
}
