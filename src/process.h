#pragma once

#include "pcb.h"

#define MAXPROCESSES 2000       // Max number of processes that can be active at once

extern state initialState;

class Process {
public:
    int pid;
    PCB pcb;

    // Default constructor
    Process ();

    // Destructor
    ~Process();
};