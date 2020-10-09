#include "process.h"
#include <iostream>
#include <cmath>


// Global variables
int next_pid = 0;
// extern int totalProcesses;
int totalProcesses = 0;
state initialState = NEW;

// Process constructor
Process::Process (std::string templateFile) {
    pid = next_pid++;
    pcb = PCB(pid, initialState, 0, 1000, 0, 75, templateFile);
    totalProcesses++;
}

// Process destructor
Process::~Process() {
    // totalProcesses--;
}

