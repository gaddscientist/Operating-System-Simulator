#pragma once
#include "pcb.h"

class Core {
public:
    // Default constructor
    Core();
    Core(int);

    // Execute process
    void execute();

    // Core number
    int coreNum;

    // Gets current PCB on core
    PCB& getPcb();

    const int totalCache = 5; // Kilobytes
    int remainingCache;

private:
    PCB pcb;        // Current pcb on CPU
    int cycleTime;  // Time in milliseconds per clock cycle
    int timeSlice;  // Number of cycles before pre-emption

};