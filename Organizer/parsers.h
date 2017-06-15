#include <iostream>
#include <string>
#include "gene.h"
#include "experiment.h"
#include <unordered_map>
#include <vector>

using namespace std;

void parseSumaryTuxedoData(const string& fileName, 
            unordered_map<string, GeneEntry>& entries);

void parseRawTuxedoData(const string& fileName,
                       unordered_map<string, GeneEntry>& entries,
                       int control_replic, int target_replic);

void parseConfigFile(const string& fileName, vector<Experiment>& experiments);
