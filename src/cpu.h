#pragma once
#include "pcb.h"

class CPU {
    private:
        int clock;
        PCB pcb;
        bool swapProcess;
        bool wait;

        // Member functions
        void execute();

    public:
        // Default constructor
        CPU();

        void clockTick();

        // Getters
        int getClock();
        PCB getPcb();

        // Setters
        void setClock(int clock);
        void setPcb(PCB pcb);
};