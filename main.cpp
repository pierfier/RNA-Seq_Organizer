#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Gene.h"

using namespace std;

void parseData(const string& fileName, vector<GeneEntry>& entries){
    string line;

    while(getline(in, line)){
        
    }
}

//Remove all data that is above the given threshold
void filterGeneEntries(vector<GeneEntry>& entries, int threshold){
    vector<GeneEntry>::iterator it;
    for(it = entries.begin(); it != entries.end(); ++it){
        
        //Check if either standard deviations are above the threshold
        if(it->getTargetStDev() > threshold 
                || it->getControlStDev() > threshold){
            entries.erase(it);
            --it;
        }
    }
}

// Rank gene entries based on fold change
void rankGeneEntries(vector<GeneEntry>& entries){
    sort(entries.rbegin(), entries.rend());
}

void outputData(const vector<GeneEntry>& entries, int target_replic,
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
        out << "Target Replicate " << i+1 << "\t";
    }

    //Output the control replicates heading
    for(int i = 0; i < control_replic; ++i){
        out << "Control Replicate " << i+1 << "\t";
    }

    out << "log2"<< endl;

    // Output gene entries

    vector<GeneEntry>::iterator it;
    for(it = entries.begin(); it != entries.end(); ++it){
        
        //Ouput name
        out << it->getName() << "\t";
      
        //Output the replicate values
        
        for(int i = 0; i < it->numTargetValues(); ++i){
            out << it->getTargetValueAt(i) << "\t";
        }

        for(int i = 0; i < it->numControlValues(); ++i){
            out << it->getControlValueAt(i) << "\t";
        }

        //Ouput fold change
        out << it->getFoldChange();

        out << endl;
    }

    out.close();
}

int main(int argc, int argv[]){
    //Local Variables
    string fileName;
    vector<GeneEntry> entries;//TODO this might have to change to a Treemap
    int num_target_replic;
    int num_control_replic;
    int target_threshold;

    //------ Prompt user for necessary data --------
    
    // Get number of gene entries
    cout << "Enter the number of gene entries:";
    cin >> numEntries;

    //Get number of target replicates
    cout << "Enter the number of target replicates:";
    cin >> num_target_replic;

    //Get the number of control replicates
    cout << "Enter the number of  control replicates:";
    cin >> num_control_replic;
    
    //Get the file name of the raw Tuxedo data
    cout << "Enter the file name of the raw Tuxedo data:";
    getline(cin, fileName);
    
    //Get the threshold for the target data
    cout << "Enter the threshold to filter out for the target:";
    cin >> target_threshold;

    //------- Parse all of the gene entries ---------
    parseData(fileName);

    //------- Rank the data -------------------
    // First filter out genes that have a standard deviation that
    // as past the threshold standard deviation
    // then rank based on the fold change
    filterGeneEntries(entries, target_threshold);
    rankGeneEntries(entries);

    //------- write all of the sorted genes to a file --------------
    outputData(entries, num_target_replic, num_control_replic);
}
