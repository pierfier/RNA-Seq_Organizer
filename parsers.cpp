#include "parsers.h"
#include "gene.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

void parseConfigFile(const string& configFile, vector<Experiment>& experiments){
    ifstream in(configFile.c_str());
    string line = "", str;
    Experiment temp;

    if(!in.is_open()){
        cerr << "Invalid config file " << configFile << endl;
        exit(1);
    }
    
    while(getline(in, line)){
        //Reset variables
        stringstream ss(line);
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
        temp.setNumTargetReplic(atoi(str.c_str()));
        
        ss >> str;
        //Set number control replicates
        temp.setNumControlReplic(atoi(str.c_str()));
        
        ss >> str;
        //Set number mean threshold
        temp.setMeanThres(atoi(str.c_str()));
        
        ss >> str;
        //Set number of stdev threshold
        temp.setVarThres(atoi(str.c_str()));
        
        
        //Parse the individual data for each experiment
        temp.parseData();
        //Add the experiment to the vector of experiments
        experiments.push_back(temp);
    }
}
