# Markov Generator
A command line C++ application generating text from two files based on Markov Chains of n-th order.  

## Run
Compile the project by running `g++ --std c++11 markov.cpp` on the terminal in the project directory.  
Run it with `./a.out`  

### Custom files
You can input your own text files by changing the `std::ifstream fileIn("text.txt");` line.  

### Order
You can change the order of the Markov chain by changing the line initialising the order. A smaller order produces more gibberish, higher order makes the generated takes more similar to the inputed text(s).
