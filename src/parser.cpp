
#include "parser.h"
#include <algorithm>

using namespace std;

std::vector<string> filter = {
    "ACU",
    "AGM",
    "AOQ",
    "AOS",
    "ATT",
    "BCV",
    "BFQ",
    "BLD",
    "BNY",
    "BVV",
    "CBS",
    "CGA",
    "CKD",
    "CKX",
    "CUK",
    "CXF",
    "CZH",
    "DGA",
    "DHB",
    "DIW",
    "EAR",
    "EDA",
    "ELL",
    "EXI",
    "FBS",
    "FDE",
    "FSZ",
    "FVM",
    "GCW",
    "GHE",
    "GLN",
    "GNU",
    "GRV",
    "GSM",
    "HKB",
    "HYL",
    "IGM",
    "IKE",
    "INB",
    "INC",
    "IOQ",
    "IOT",
    "IUI",
    "JJA",
    "JUK",
    "JUU",
    "KAE",
    "KBC",
    "KBU",
    "KCC",
    "KCG",
    "KCL",
    "KCQ",
    "KGQ",
    "KGX",
    "KHQ",
    "KKB",
    "KKI",
    "KLL",
    "KOZ",
    "KPB",
    "KTB",
    "KUS",
    "KUZ",
    "KWF",
    "KXU",
    "LBP",
    "LCR",
    "LGQ",
    "LKE",
    "LMC",
    "LNV",
    "LSA",
    "MCM",
    "MJU",
    "MLH",
    "MNT",
    "MPP",
    "MRA",
    "NIQ",
    "NKI",
    "NSQ",
    "NTG",
    "NUP",
    "OGM",
    "OHH",
    "OLH",
    "ORI",
    "ORZ",
    "OTD",
    "PAF",
    "PEC",
    "PHO",
    "PLJ",
    "PND",
    "PPV",
    "PQS",
    "PUM",
    "PVE",
    "PYC",
    "QFN",
    "QJH",
    "QOQ",
    "QUB",
    "QUV",
    "QUW",
    "RCE",
    "RDV",
    "RIG",
    "RKA",
    "RMP",
    "SAE",
    "SAX",
    "SGG",
    "SHC",
    "SIC",
    "SLI",
    "SQS",
    "SRK",
    "SRV",
    "SSB",
    "SVC",
    "SVK",
    "SVR",
    "SVS",
    "SXP",
    "SYB",
    "SZE",
    "SZI",
    "TAL",
    "TCD",
    "TCR",
    "TCT",
    "TFI",
    "TGC",
    "THD",
    "TKE",
    "TLT",
    "TNK",
    "TNO",
    "TQA",
    "TQI",
    "TVS",
    "TZA",
    "UGB",
    "UPK",
    "WBB",
    "WNH",
    "WSX",
    "WTL",
    "WWP",
    "WWT",
    "XEQ",
    "YKT",
    "ZBL",
    "ZDY",
    "ZEL",
    "BSS",
    "MTE",
    "QFX"};

vector<string> data_list(string filename){
    
    //string filename = "data_/test_cases_1";  //use this for test cases
    ifstream input;

    input.open(filename); //open the file
    vector<string> data_vector; 

    if(!input.is_open()){ //just in case it's empty or read wrong
        cout<<"read file wrong"<<endl;
        return data_vector; //return the empty vector if that's teh case
    }
    string line_;
    //int index = 100000; //index is only used to get the first 10 datapoints for testing
    //while(getline(input, line_) && index != 0){
    while(getline(input, line_)){
        data_vector.push_back(line_);   //push back each line of dataset into the vector
        //index--;
    }
    
    input.close();
    return data_vector;
}

vector<Flights> data_structs(string filename){ //define fli9ghts struct elsewhere
    vector<string> data_vector = data_list(filename); //makes the vector of the dataset nodes in string form
    //break down into structs
    vector<Flights> flight_list;

    for(string x: data_vector){
        string cur_set = x;
        stringstream set_stream(cur_set);

        string _airline;
        getline(set_stream, _airline, ','); //seperate the different strings of data value from each line of the dataset
        string _airline_id;
        getline(set_stream, _airline_id, ',');
        string _source;
        getline(set_stream, _source, ',');
        string _source_id;
        getline(set_stream, _source_id, ',');
        string _dest;
        getline(set_stream, _dest, ',');
        string _dest_id;
        getline(set_stream, _dest_id, ',');
        string _codeshare;
        getline(set_stream, _codeshare, ',');
        string _num_stops;
        getline(set_stream, _num_stops, ',');

        Flights cur_flight = { //create struct from the seperted strings
            _airline,
            _airline_id,
            _source,
            _source_id,
            _dest,
            _dest_id,
            //_codeshare, pointless unless we need it somehow
            _num_stops
        };
        if (std::find(filter.begin(), filter.end(), _source) == filter.end() && std::find(filter.begin(), filter.end(), _dest) == filter.end()) {
            flight_list.push_back(cur_flight);
        }  
    }
    return flight_list;
}


vector<Airports> aiports_data_structs(string filename) { //define fli9ghts struct elsewhere
    vector<string> data_vector = data_list(filename); //makes the vector of the dataset nodes in string form
    vector<Airports> airport_list;

    for(string x: data_vector){
        string cur_set = x;
        stringstream set_stream(cur_set);

        string number;
        getline(set_stream, number, ','); //seperate the different strings of data value from each line of the dataset
        string name;
        getline(set_stream, name, ',');
        string city;
        getline(set_stream, city, ',');
        string country;
        getline(set_stream, country, ',');
        string IATA;
        getline(set_stream, IATA, ','); //seperate the different strings of data value from each line of the dataset
        string ICAO;
        getline(set_stream, ICAO, ',');
        string latitude;
        getline(set_stream, latitude, ',');
        string longitude;
        getline(set_stream, longitude, ',');

        Airports cur_aiport = { //create struct from the seperted strings
            IATA.substr(1, IATA.size()-2),
            ICAO.substr(1, ICAO.size()-2),
            latitude,
            longitude
        };

        airport_list.push_back(cur_aiport);
    }

    return airport_list;
}
