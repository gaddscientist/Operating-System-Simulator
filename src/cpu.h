#pragma once
#include "pcb.h"

class CPU {
    public:

        CPU();

        int clock;
        PCB pcb;

        // Member functions
        void clockTick();
};