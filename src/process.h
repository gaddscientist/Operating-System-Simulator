#pragma once

#include <string>
#include "pcb.h"

extern state initialState;

// Class to define a process object
class Process {
private:
    int pid;    // Process ID number
    PCB pcb;    // PCB associated with this process

public:
    // Constructor
    Process (std::string templateFile);

    // Destructor
    ~Process();

    // Getters
    int getPid();
    PCB getPcb();

    // Setters
    void setPid(int pid);
    void setPcb(PCB pcb);
};
