#pragma once
#include <string>

// Base class to simulate operating system
class OS {
public:
    // Constructor
    // Takes a template filename and number of processes to spawn
    OS(std::string, int);

    // Starts up the simulator
    void start();


private:
    // Process creation variables
    std::string templateFile;
    int numProcesses;


    // Internal functions
    void createProcesses(std::string templateFile, int numProcesses);
};