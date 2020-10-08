#pragma once

#include <string>
#include "pcb.h"

extern state initialState;

class Process {
public:
    int pid;
    PCB pcb;
    int burstCycle;

    // Member functions
    int calculateBurst();

    bool operator<(const Process& otherProcess) const {
        return burstCycle < otherProcess.burstCycle;
    }

    // Constructor
    Process (std::string templateFile);

    // Destructor
    ~Process();

private:
    // Calculate the burst as the average cpu cycle
};
