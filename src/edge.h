#pragma once

#include "airport.h"
#include <string>

using std::string;

class Edge
{
    public:
        Airport source; 
        Airport dest;
        std::string airline;
        std::string num_stops;

        Edge() : source(Airport()), dest(Airport()), airline(""), num_stops("-1") {}

        Edge(Airport u, Airport v): source(u), dest(v), airline(""), num_stops("-1") {}

        Edge(Airport u, Airport v, string my_airline, string my_num_stops): source(u), dest(v), airline(my_airline), num_stops(my_num_stops) {}
        
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
