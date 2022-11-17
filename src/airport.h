#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>

class Airport {

  public:

    

    Airport();
    Airport(std::string mySource, std::string mySourceId);


    bool operator < (const Airport &other) {
      if (source < other.source) {
        return true;
      }
      return false;
    }

  private:
    std::string source;
    std::string source_id;
};