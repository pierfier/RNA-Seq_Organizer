#include <iostream>
#include <fstream>
#include <stringstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stdlib.h>
#include <set>
#include "gene.h"
#include "parsers.h"
#include "experiment.h"
#include <math.h>

using namespace std;

#define MAX_FILES 2

//Global variables
enum dataFiles{
    rawTuxedo,
    sumTuxedo,
};

//Currently gets the genes that are found in all of the experiments
//These genes are then stored in the set entries
void findOverlap(vector<Experiment>& experiments, set<string>& entries){
    //Map indexed by gene ID and then
    //stores the number of experiments it is referenced (NOTE: Not needed now, but could be used later)
    unordered_map<string, int> gene_reference;
    int max_gene_occurrence = 1;


    //Add genes from the first experiment into the map
    for(int i = 0; i < experiments[0].getNumGenes(); ++i){
        gene_reference(make_pair(experiments[0].getGeneEntryAt(i).getName(), 1));
    }

    //Check all of the other experiments to see if they have the same gene
    //If so update individual gene counter
    for(int i = 0; i < experiments.size(); ++i){
        
        //Iterate through each gene in the common gene reference map
        //and test if they occur in the current experiment
        unordered_map<string, int>::iterator it, it2;

        for(it = gene_reference.begin(); it != gene_reference.end();){
            if(experiments[i].hasGeneEntry(it->first)){
                it->second += 1;
                
                //Update max gene occurrence count
                if(it->second > max_gene_occurrence){
                    max_gene_occurrence = it->second;
                }

                ++it;
            }else{
                it2 = it;
                ++it;

                gene_reference.erase(it2);
            }
        }
    }

    //Find all of the genes that have the same occurrence as the max gene
    //then place them in the set
    for(it = gene_reference.begin(); it != gene_reference.end(); ++it){
        if(it->second == max_gene_occurrence){
            entries.insert(it->first);
        }
    }
}

void parseConfigFile(const string& configFile, vector<Experiment>& experiments){
    ifstream in(configFile.c_str());
    stringstream ss;
    string line, str;
    Experiment temp;

    if(!in.is_open()){
        cerr << "Invalid config file " << configFile << endl;
        exit(1);
    }
    
    while(getline(in, line)){
        //Reset variables
        ss = stringstream(line);
        temp = Experiment();
        
        ss >> str;
        //Set the experiment label
        temp.setName(str);

        ss >> str;        
        //Set the raw Tuxedo file
        temp.setRawTuxFile(str);

        ss >> str;
        //Set the sum Tuxedo file
        temp.setSumTuxFile(str);

        ss >> str;
        //Set number target replicates
        temp.setNumTargetReplic(atoi(str));
        
        ss >> str;
        //Set number control replicates
        temp.setNumControlReplic(atoi(str));
        
        ss >> str;
        //Set number mean threshold
        temp.setMeanThres(atoi(str));
        
        ss >> str;
        //Set number of stdev threshold
        temp.setVarThres(atoi(str));
    }
}

void printOverlap(const string& fileName, set<string>& entries, const vector<Experiment>& experiments){  
    //Open the output file
    ofstream out(fileName.c_str());
    
    if(!out.is_open()){
        cerr << "Could not open file " << fileName << endl;
        exit(1);
    }

    set<string>::iterator it;
    
    GeneEntry entry;

    for(it = entries.begin(); it != entries.end(); ++it){
        for(int i = 0; i < experiments.size(); ++i){
            experiments[i].getGeneEntry(*it).printData(out);
            out << endl;
        }
    }

    out.close();
}

void rankAndFilterExperiments(vector<Experiment>& experiments){
    for(int i = 0; i < experiments.size(); ++i){
        experiments[i].filter();
        experiments[i].rankByAverageDifference();
    }
}

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
    string dataFiles[MAX_FILES];
    string configFile;


    //TODO Use this as a vector, possibly make this a class
    //to keep everything organized
    vector<Experiment> experiments;

    //Set that stores the common genes across all of the experiments
    //In order of basic ranking system
    set<string> common_genes;
    
    int num_target_replic;
    int num_control_replic;
    int var_threshold;
    int mean_threshold;
       
    //Check arguments for configuration options
    for(int i = 0; i < argc; ++i){
        
        // Parse arguments based on experiments
        
        //Parse for configuration data
        if(string(argv[i]) == "-c"){
            configFile = string(argv[i + 1]);
        }
 


        //TODO might have to delete all of this
        //Option to parse raw Tuxedo data
        if(string(argv[i]) == "-rt"){
            dataFiles[rawTuxedo] = string(argv[i + 1]);

        //Op#include <stdlib.h>tion to parse summary Tuxedo data
        }else if(string(argv[i]) == "-st"){
            dataFiles[sumTuxedo] = string(argv[i + 1]);

        //Option to parse raw two treatment counts data
        }else if(string(argv[i]) == "-r2"){
            dataFiles[rawTreat] = string(argv[i + 1]);
            
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
    
    //Parse the config file
    parseConfigFile(configFile, experiments);
    rankAndFilterExperiments(experiments);


    // Check commandline arguments for what process is going to be done
    for(int i = 0; i < argc; ++i){
        
        //Option find overlap between all of the experiments
        if(string(argv{i}) == "-ol"){
            findOverlap(experiments, common_genes);
        }else 
        
        //Option to print the common genes across all of the experiments
        if(string(argv[i]) = "-pol"){
            printOverlap(string(argv[i + 1]), common_genes);
        }
    }
}
