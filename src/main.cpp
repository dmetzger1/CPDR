#include <iostream>
 
#include "functions.hpp"
 
int main(int argc, char* argv[]) {
 for (int i = 1; i < argc; ++i) {
   std::cout << "Howdy, " << argv[i] << std::endl;
 }
 std::cout << Howdy("Rachel") << std::endl;
}
