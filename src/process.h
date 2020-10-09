#pragma once

#include <string>
#include "pcb.h"

extern state initialState;

class Process {
private:
    int pid;
    PCB pcb;

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
