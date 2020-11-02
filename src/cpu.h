#pragma once
#include <deque>
#include "pcb.h"

class CPU {
    public:
        // Default constructor
        CPU();

        // void clockTick();
        void execute();

        // Getters
        double getClock();
        PCB getPcb();

        // Setters
        void setClock(int clock);
        void setPcb(PCB pcb);

    private:
        PCB pcb;
        bool interrupted;
        int cycleTime;
        int timeSlice;
        // Beginning of simulation
        // std::chrono::time_point<std::chrono::system_clock> startTime;
        int startTime;

        // Member functions

        // Creats an interrupt object that corresponds to the interrupted process
        struct Interrupt {
            Interrupt(int id) : pid(id) {}
            int pid;
        };

        std::deque<Interrupt> interrupts;
};