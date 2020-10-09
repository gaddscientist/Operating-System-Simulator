#pragma once

#include <string>
#include "pcb.h"

extern state initialState;

class Process {
public:
    int pid;
    PCB pcb;

    // Constructor
    Process (std::string templateFile);

    // Destructor
    ~Process();
};
