#pragma once


#include <string>

using std::string;

class Edge
{
    public:

        std::string source;
        std::string dest;
        std::string airline;
        std::string num_stops;

        //Constructors for initializing edges

        Edge() : source(""), dest(""), airline(""), num_stops("-1") {}

        Edge(std::string u, std::string v): source(u), dest(v), airline(""), num_stops("-1") {}

        Edge(std::string u, std::string v, string my_airline, string my_num_stops): source(u), dest(v), airline(my_airline), num_stops(my_num_stops) {}
        
        // Edge Getter Functions

        string getAirline() const
        {
            return this->airline;
        }

        string getNumStops() const
        {
            return this->num_stops;
        }

    private:

};
