#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <random>

// return random int in the range 0-max
int randInt(int max);

//make the markov model
std::map <std::string,std::string> addToMarkov(int order, std::map <std::string,std::string> markov, std::string input);

// returns a vector of strings representing the string keys of the sent map
std::vector <std::string> getMapKeys(std::map<std::string,std::string> theMap);
