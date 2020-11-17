#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <fstream>
#include <time.h> //used to change the seed

// return random int in the range 0-max
int randInt(int max){
    double r = std::rand();
    r /= RAND_MAX;
    r *= max;
    int i = r;
    return i;
}

//make the markov model
std::map <std::string,std::string> addToMarkov(int order, std::map <std::string,std::string> markov, std::string input){
    
    std::string gram;
    std::string nexts;
    
    //discard the text if it's too short
    if(input.length() < order) { return markov; }
    
    //iterate over the inputed string
    for (std::string::size_type i = 0; i <= input.size() - order - 1; i++) {
        
        //get the substring of current n-gram
        gram = input.substr(i, order);
        
        nexts = "";
        //check if the n-gram already exists
        if(markov.count(gram)<=0){
            //std::cout << "Not found\n";
            
            //make a new key value pair (empty value for now)
            markov[gram] = "";
            
        } else {
            //std::cout << "I exist\n";
            
            //get all the prior nexts
            nexts = markov[gram];
        }
        
        //add the character after the gram to the nexts
        nexts += input.at(i + order);
        //std::cout << "nexts: " << nexts << std::endl;
        
        //put all the nexts (including new) as the values for the gram key
        markov[gram] = nexts;
        
        //std::cout << "Markov gram " << gram << " Nexts: " << markov[gram] << std::endl;
        
    }
    
    return markov;
    
}

// returns a vector of strings representing the string keys of the sent map
std::vector <std::string> getMapKeys(std::map<std::string,std::string> theMap){
  std::vector<std::string> vec;
  
  // from the example code here:  http://www.cplusplus.com/reference/map/map/begin/
  for (std::map<std::string,std::string>::iterator it=theMap.begin(); it!=theMap.end(); ++it){
    //std::cout << it->first << " => " << it->second << '\n';
    vec.push_back(it->first);
  }
  return vec;

}


int main(){
    
    std::map <std::string,std::string> markovModel; //this will hold the model
    std::ifstream fileIn("trump_tweets_all.txt"); //load in the text file for the model
    std::ifstream fileIn2("shakespeare.txt"); //load in the second text file
    //trump tweets from here https://github.com/thomashikaru/faketrumptweets
    std::string line, text, beginning; //used for making the model
    std::vector <std::string> beginnings; //store all of the line beginnings
    std::string current, output, allNexts, next, input;
    srand(time(0)); //set the seed
    
    int order = 10;
    
    text = "";
    beginning = "";
    while(std::getline(fileIn, line)){
        
        //skip over empty lines
        if (line == "" || line.length() == 0) continue;
        
        //check for carriage returns and delete those lines - prevents out of range errors
        //adapted from https://stackoverflow.com/questions/2528995/remove-r-from-a-string-in-c
        std::string::size_type pos = 0;
        while ( ( pos = line.find ("\r\n",pos) ) != std::string::npos )
        {
            line.erase ( pos, 2 );
        }
        
        //erase empty lines
        line.erase( std::remove(line.begin(), line.end(), '\r'), line.end() );
        
        beginning = line.substr(0, order); //gets the first n-gram of the line
        //if it's not just an empty line
        if (beginning != "" || !beginning.empty()){
            //std::cout << "an Actual beginning!: " << beginning << std::endl;
            //push the n-gram to the beginnings vector
            beginnings.push_back(beginning);
        }
        
        //removing the \r character code from https://stackoverflow.com/questions/48696447/c-reading-multiple-lines-from-a-file-to-a-single-string
        const std::string::size_type position = line.find('\r');
        if (position != std::string::npos)
        {
            line.erase(position);
        }
        text += line; //put all lines together in a single string - solves the issue of line breaks
        
        //get each line from the text and make the model - sometimes gives out of range errors - not good
        //markovModel = addToMarkov(order, markovModel, line);
    }
    //make the model
    markovModel = addToMarkov(order, markovModel, text);
    
    //make the second model
    text = "";
    while(std::getline(fileIn2, line)){
        
        //skip over empty lines
        if (line == "" || line.length() == 0) continue;
        
        //check for carriage returns and delete those lines - prevents out of range errors
        //adapted from https://stackoverflow.com/questions/2528995/remove-r-from-a-string-in-c
        std::string::size_type pos = 0;
        while ( ( pos = line.find ("\r\n",pos) ) != std::string::npos )
        {
            line.erase ( pos, 2 );
        }
        
        //erase empty lines
        line.erase( std::remove(line.begin(), line.end(), '\r'), line.end() );
        
        beginning = line.substr(0, order); //gets the first n-gram of the line
        //if it's not just an empty line
        if (beginning != "" || !beginning.empty()){
            //std::cout << "an Actual beginning!: " << beginning << std::endl;
            //push the n-gram to the beginnings vector
            beginnings.push_back(beginning);
        }
        
        //removing the \r character code from https://stackoverflow.com/questions/48696447/c-reading-multiple-lines-from-a-file-to-a-single-string
        const std::string::size_type position = line.find('\r');
        if (position != std::string::npos)
        {
            line.erase(position);
        }
        text += line; //put all lines together in a single string - solves the issue of line breaks
        
        //get each line from the text and make the model - sometimes gives out of range errors - not good
        //markovModel = addToMarkov(order, markovModel, line);
    }
    //make the model
    markovModel = addToMarkov(order, markovModel, text);
    
    // print out a prompt to the user
    std::cout << "Type something to generate..." << std::endl;
    std::cout << "--------------------------------------- " << std::endl;

    while(true){
                //get the input from the console
        std::getline(std::cin, input);
    
        //Generating an output
        //pick a random beginning
        current = beginnings[randInt(beginnings.size())];
        //std::cout << "Random Beg: " << randomBeginning << std::endl;
        
        //start building the output
        output = current;
        
        //generate the output some number of times (amount of chars in the output)
        for (int i = 0; i < 160; i++){
            
            //get all the possible next chars for the current n-gram
            allNexts = markovModel[current];
            
    //        for(int j = 0; j < allNexts.size(); j++){
    //            std::cout << "Nexts: " << allNexts[j] << std::endl;
    //        }
            
            //pick one random next
            next = allNexts[randInt(allNexts.size())];
            //add it to the output
            output += next;
            // Get the last N entries of the output; we'll use this to look up an ngram in the next iteration of the loop
            current = output.substr(output.size() - order, output.size());
        }
        
        std::cout << "Generated: " << output << std::endl;
        std::cout << "--------------------------------------- " << std::endl;
    }
    
}



