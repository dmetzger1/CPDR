
#include "parser.h"
using namespace std;

vector<string> data_list(){
    cout<<"inside function"<<endl;
    string filename = "data_/routes.dat.txt"; //create file 
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
    // for( string x: data_vector){ //print out the vector
    //      cout<<x<<endl;
    // }
    input.close();
    return data_vector;
}

vector<Flights> data_structs(){ //define fli9ghts struct elsewhere

    vector<string> data_vector = data_list(); //makes the vector of the dataset nodes in string form
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
        //string _test;
        //(set_stream, _test, ',');
        //int _num_stops = (int) _test;


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

        flight_list.push_back(cur_flight);
    }
    /* for(Flights z: flight_list){
        //Flights test = flight_list[z];
        cout<<z.airline<<endl;
        cout<<z.airline_id<<endl;
        cout<<z.source<<endl;
        cout<<z.source_id<<endl;
        cout<<z.dest<<endl;
        cout<<z.dest_id<<endl;
        //cout<<z.codeshare<<endl;
        cout<<z.num_stops<<endl;
        cout<<" "<<endl;

    }*/
    return flight_list;
}
