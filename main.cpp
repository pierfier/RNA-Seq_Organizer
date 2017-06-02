#include <iostream>
#include <fstream>
#include <string>
#include "Gene.h"

using namespace std;

void parseData(const string& fileName, GeneEntry * entries){
    string line;

    while(getline(in, line)){
        
    }
}

int main(int argc, int argv[]){
    //Local Variables
    string fileName;
    GeneEntry * entries;
    int numEntries;
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


    //Initialize variables
    entries = new GeneEntry[numEntries];

    //------- Parse all of the gene entries ---------
    

}
