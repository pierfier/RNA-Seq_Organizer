#include "parsers.h"
#include "gene.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

void parseSumaryTuxedoData(const string& fileName, unordered_map<string, GeneEntry>& entries){
    string line;

    ifstream in(fileName.c_str());

    //Check if file is open
    if(!in.is_open()){
        cerr << "Could not open " << fileName << endl;
        exit(1);
    }

    //Read in header line
    getline(in, line);
    
    //Data to store for each line
    string str;
    int i;
    unordered_map<string, GeneEntry>::iterator it;

    while(getline(in, line)){
        str = line.substr(0, (i = line.find("\t")));
        ++i;
        
        //DEBUG
        cout << str << " ";

        it = entries.find(str);
        
        //DEBUG
        if(it == entries.end()){
            cerr << "Could not find gene " << str << endl;
            exit(1);
        }
        
        //Forward to fold change entry
        for(int j = 0; j < 10; ++j){
            i = line.find("\t", i);
            ++i;
        }
        
        //Grab the fold change
        str = line.substr(i, line.find("\t", i) - i);
        i = line.find("\t", i);
        ++i;
        it->second.setFoldChange(str);
        
        //Forward to p Value entry
        for(int j = 0; j < 2; ++j){
            i = line.find("\t", i);
            ++i;
        }

        //Grab the p Value entry
        str = line.substr(i, line.find("\t", i) - i);
        it->second.setPValue(str);

        //DEBUG
        cout << "=" << str << "=" << endl;
    }
}

void parseRawTuxedoData(const string& fileName, 
                    unordered_map<string, GeneEntry>& entries, 
                    int control_replic, int target_replic){
    
    string line;
    ifstream in(fileName.c_str());

    //Check if file is open
    if(!in.is_open()){
        cerr << "Could not open " << fileName << endl; 
        exit(1);
    }
    
    //Read in header line
    getline(in, line);
    
    string str;
    double val;
    int i;
    
    GeneEntry temp;

    while(getline(in, line)){
        temp = GeneEntry();
        //Get the name of the gene
        str = line.substr(0, (i = line.find("\t")));
        
        temp.setName(str);

        //Skip by finding next tab
        i = line.find("\t", i + 1);
        ++i;

        //Grab all of the control values and store them in this entry
        for(int j = 0; j < control_replic; ++j){
            str = line.substr(i, (line.find("\t", i)) - i); 
            i = line.find("\t", i);
            val = stod(str);
            temp.addControlValue(val);
            ++i;
        }
    
        //Grab all of the target values and store them in this entry
        for(int j = 0; j < target_replic; ++j){
            str = line.substr(i, (line.find("\t", i)) - i); 
            i = line.find("\t", i);
            val = stod(str);
            temp.addTargetValue(val);
            ++i;
        }
 
        temp.calcStats();
        
        entries.insert(make_pair(temp.getName(), temp));
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
