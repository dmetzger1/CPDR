#pragma once

#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <string>
#include <sstream>

struct Flights{ //
    string airline;
    string airline_id;
    string source;
    string source_id;
    string dest;
    string dest_id;
    //string codeshare;  pretty pointless, we won't have to use it and it's usually empty anyways
    string num_stops;   //might have to cast this into an integer based off our implementation
    //int num_stops;
};

vector<string> data_list(string filename); //creates vector of each line in the flights dataset
vector<Flights> data_structs(string filename);  //craetes vector of structs made from each node in the dataset

