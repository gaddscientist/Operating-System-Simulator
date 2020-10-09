#pragma once
#include "pcb.h"

class CPU {
    private:
        int clock;
        PCB pcb;

        // Member functions
        void clockTick();

    public:
        // Default constructor
        CPU();

        // Getters
        int getClock();
        PCB getPcb();

        // Setters
        void setClock(int clock);
        void setPcb(PCB pcb);
};