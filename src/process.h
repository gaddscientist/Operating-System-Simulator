#pragma once

#include "pcb.h"

#define MAXPROCESSES 2000       // Max number of processes that can be active at once

extern state initialState;

class Process {
public:
    int pid;
    PCB pcb;
    int burstCycle;
    int calculateBurst();

    // Default constructor
    Process ();

    // Destructor
    ~Process();

private:
    // Calculate the burst as the average cpu cycle
};
