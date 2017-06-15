#include <iostream>
#include "experiment.h"
#include "gene.h"
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

Experiment::Experiment(){
    name_ = "";
    rawTuxFile_ = "";
    sumTuxFile_ = "";
    num_target_replic_ = 0;
    num_control_replic_ = 0;
    mean_threshold_ = 0;
    var_threshold_ = 0;
    average_diff_threshold_ = 0;
}

void Experiment::parseData(){
    // Read in the raw Tuxedo file
    

    ifstream in(rawTuxFile_.c_str());
    string line, str;
    GeneEntry temp;
    

    if(rawTuxFile_ != "\"\""){
    
        if(!in.is_open()){
            cerr << "Could not open " << rawTuxFile_ << endl;
            exit(1);
        }

        //Skip the header line
        getline(in, line);

        while(getline(in, line)){
            
            stringstream ss(line.c_str());
            temp = GeneEntry();
            
            ss >> str;
            //Get gene ID
            temp.setName(str);
            

            //Get control counts
            for(int i = 0; i < num_control_replic_; ++i){
                ss >> str;
                temp.addControlValue(stod(str));
            }

            //Get the target counts
            for(int i = 0; i < num_target_replic_; ++i){
                ss >> str;
                temp.addTargetValue(stod(str));
            }

            gene_entries_.insert(make_pair(temp.getName(), temp));
        }

    }
    // Read in the summary Tuxedo file
    in = ifstream(sumTuxFile_.c_str());

    if(sumTuxFile_ != "\"\""){

        if(!in.is_open()){
            cerr << "Could not open " << sumTuxFile_ << endl;
            exit(1);
        }

        //Skip the header line
        getline(in, line);

        unordered_map<string, GeneEntry>::iterator it;

        while(getline(in, line)){
            stringstream ss(line.c_str());

            ss >> str;

            //Find the gene
            it = gene_entries_.find(str);
            

            //Way of "catching an exception"
            if(it == gene_entries_.end()){
                //Split the gene names apart if possible
                str = str.substr(0, str.find(","));
                it = gene_entries_.find(str);
                
                if(it == gene_entries_.end()){
                    cerr << "Could not find gene: " << str << endl;
                    exit(1);
                }
            }

            ss >> str;
            //Get the fold change
            
            it->second.setFoldChange(str);

            ss >> str;
            //Get the p value
            it->second.setPValue(str);
        }
    }
}

void Experiment::filter(){
    unordered_map<string, GeneEntry>::iterator it, it2;
    it = gene_entries_.begin();
    
    //Check to make sure that the gene's have statistical data
    if(it->second.getTargetAverage() == 0){
        calcStats();
    }

    //Filter by standard deviation and mean
    for(it = gene_entries_.begin(); it != gene_entries_.end();){
        
        //DEBUG
        if(it->first == "Pomc"){
            cout << it->second.getTargetStDev() << endl;
        }

        if(it->second.getTargetStDev() > var_threshold_ ||
           it->second.getControlStDev() > var_threshold_ ||
           it->second.getTargetAverage() < mean_threshold_  ||
           it->second.getTargetAverage() - it->second.getControlAverage() < average_diff_threshold_){
           
            it2 = it;
            ++it;
    
            gene_entries_.erase(it2);
        }else{
            ++it;
        }
    }
}

void Experiment::calcStats(){
    unordered_map<string, GeneEntry>::iterator it;

    for(it = gene_entries_.begin(); it != gene_entries_.end(); ++it){
        it->second.calcStats();    
    }
}

GeneEntry Experiment::getGeneEntry(string name){
    unordered_map<string, GeneEntry>::iterator it;
    it = gene_entries_.find(name);
    if(it == gene_entries_.end()){
        return GeneEntry();
    }else{
        return it->second;
    }
}

bool Experiment::hasGeneEntry(string gene){
    return gene_entries_.find(gene) != gene_entries_.end();
}

unordered_map<string, int> Experiment::getGenesList(){
    unordered_map<string, int> entries;
    unordered_map<string, GeneEntry>::iterator it;

    for(it = gene_entries_.begin(); it != gene_entries_.end();++it){
        entries.insert(make_pair(it->second.getName(), 1));
    }

    return entries;
}
