#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>

class Airport {

  public:
    Airport();
    Airport(std::string mySource, std::string mySourceId);

    std::string getSource() { return source; }
    
    bool operator >(Airport other) {
      std::cout << other.getSource() << std::endl;
      return false;
    }

  private:
    std::string source;
    std::string source_id;
};