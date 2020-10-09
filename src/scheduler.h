#pragma once

#include <vector>
#include "pcb.h"

enum schedulerType {INVALID = 0, SJF, RR};

class Scheduler {
    public:
        // clock
        // cpu
        schedulerType chosenScheduler;
        std::vector<PCB> newQueue;
        std::vector<PCB> readyQueue;
        std::vector<PCB> waitingQueue;
        // If you want to keep track of finished processes
        std::vector<PCB> terminatedQueue;

        // Default constructor
        Scheduler ();

        // Member functions
        void sortProcesses();
        void setSchedulerType(schedulerType st);
        void addProcessToReadyQueue(PCB p);
        void updateQueues();
};