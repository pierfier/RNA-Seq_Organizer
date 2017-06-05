#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include "gene.h"

using namespace std;

void parseRawTuxedoData(const string& fileName, map<string, GeneEntry>& entries, int control_replic, int target_replic){
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

//Remove all data that is above the given stdev threshold
//or below the given mean threshold
void filterGeneEntries(map<string, GeneEntry>& entries, 
        int mean_threshold, int var_threshold){
    map<string, GeneEntry>::iterator it, it2;
    for(it = entries.begin(); it != entries.end();){
        
        //Check if either standard deviations are above the threshold
        if(it->second.getTargetStDev() > var_threshold ||
                it->second.getControlStDev() > var_threshold ||
        it->second.getTargetAverage() < mean_threshold  ||
                it->second.getControlAverage() < mean_threshold){
            
            it2 = it;
            
            //Check if iterator is pointing to the first element in the map
            if(it == entries.begin()){
                it++;
            }else{
                --it;
            }
            
            entries.erase(it2);
            
        }else{
            ++it;
        }
    }
}

// Rank gene entries based on fold change
// copy all of the values from the map to the set
// Ranking is done by GeneEntry class function comparisons
void rankGeneEntries(map<string, GeneEntry>& entries, set<GeneEntry>& sorted_entries){
    map<string, GeneEntry>::iterator it;

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

    out << "log2"<< endl;

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

        out << endl;
    }

    out.close();
}

int main(int argc, char *argv[]){
    //Local Variables
    string fileName;
    map<string, GeneEntry> entries;
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
    cin >> fileName;
    
    //Get the standard deviation threshold
    cout << "Enter the standard deviation threshold: ";
    cin >> var_threshold;

    //Get the average threshold
    cout << "Enter the average threshold: ";
    cin >> mean_threshold;

    //------- Parse all of the gene entries ---------
    parseRawTuxedoData(fileName, entries, num_control_replic, num_target_replic);

    //------- Rank the data -------------------
    // First filter out genes that have a standard deviation that
    // as past the threshold standard deviation
    // then rank based on the fold change
    filterGeneEntries(entries, mean_threshold, var_threshold);
    set<GeneEntry> sorted_entries;
    rankGeneEntries(entries, sorted_entries);

    //------- write all of the sorted genes to a file --------------
    outputData(sorted_entries, num_target_replic, num_control_replic);
}
