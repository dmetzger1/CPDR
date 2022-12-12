#pragma once

#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <string>
#include <sstream>

//Flights struct
struct Flights{ //
    string airline;
    string airline_id;
    string source;
    string source_id;
    string dest;
    string dest_id;
    string num_stops;   //might have to cast this into an integer based off our implementation
};

//Airport struct
struct Airports{ //
    string IATA;
    string ICAO;
    string latitude;
    string longitude;
};

//creates vector of each line in the flights dataset
vector<string> data_list(string filename);
//creates vector of structs made from each node in the dataset
vector<Flights> data_structs(string filename); 
//creates vector of airport structs made from each node in the dataset
vector<Airports> aiports_data_structs(string filename);
