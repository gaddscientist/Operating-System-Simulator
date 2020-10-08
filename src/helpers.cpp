#include <string>
#include <fstream>
#include <vector>
#include "helpers.h"
#include <iostream>

std::vector<std::string> ParseTemplate(const std::string tp) {
    std::vector<std::string> instructions;
    // Opens passed file name or prints error
    std::ifstream in(tp);
    std::string str;
    if(!in) {
        std::cout << ("ERROR: File not opened") << std::endl;
        exit(1);
    }

    // Loops until all lines have been read
    while (std::getline(in, str)) {
        // Ensures that the line is not blank
        if(str.size() > 0) {
            // Randomizes the number of instruction cycles for the given line
            std::string randStr = Randomize(str);
            // Adds the randomized instruction to the vector of instructions
            instructions.push_back(randStr); 
        }
    }

    // Close the file
    in.close();

    return instructions;
}

// Replaces seeds with appropriate instruction cycles
std::string Randomize(std::string& str) {
    int firstSpace = (int)str.find(' '); // Index before min
    int lastSpace = (int)str.rfind(' '); // Index before max
    std::string::size_type sz;           // Size of string

    // Minimum and maximum values for randomization of cycles
    int min = std::stoi(str.substr(firstSpace, lastSpace), &sz);
    int max = std::stoi(str.substr(lastSpace), &sz);

    // Randomly generates a number of cycles in the given range
    int randCycles = (rand() % (max - min + 1)) + min;

    // Creates a new string with randomized cycles to be returned
    std::string randomizedStr = str.substr(0, firstSpace) + " " + std::to_string(randCycles);

    return randomizedStr;
}