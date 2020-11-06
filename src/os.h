#pragma once
#include <string>
#include <map>
#include "pcb.h"

// Base class to simulate operating system
class OS {
public:
    // Constructor
    // Takes a template filename and number of processes to spawn
    OS(std::string, int);
    OS();

    // Process creation variables
    std::string templateFile;
    int numProcesses;

    // List of all processes, key:value is pid:pcb
    std::map<int, PCB> jobList;    

    // Starts up the simulator
    void start();

    // Creates a child process from process with given pid
    void fork(int pid);

private:

    // Internal functions
    void createProcess();
};
