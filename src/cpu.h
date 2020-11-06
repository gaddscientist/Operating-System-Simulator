#pragma once
#include <deque>
#include "pcb.h"

// CPU class to handle execution of process instructions
class CPU {
    public:
        // Default constructor
        CPU();

        // void clockTick();
        void execute();

        // Getters
        double getClock();
        PCB& getPcb();

        // Setters
        void setClock(int clock);
        void setPcb(PCB pcb);

    private:
        PCB pcb;        // Current pcb on CPU
        int cycleTime;  // Time in milliseconds per clock cycle
        int timeSlice;  // Number of cycles before pre-emption
        int startTime;  // Start of execution


        // Creates an interrupt object that corresponds to the interrupted process
        struct Interrupt {
            Interrupt(int id) : pid(id) {}
            int pid;
        };

        // Queue to hold interrupted processes
        std::deque<Interrupt> interrupts;
};