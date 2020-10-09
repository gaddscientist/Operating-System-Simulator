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
        void setSchedulerType(schedulerType st);

        void sortReadyProcesses();
        void sortWaitingProcesses();

        void addProcessToReadyQueue(PCB p);
        void addProcessToWaitingQueue(PCB p);

        void updateQueues();
        void updateReadyQueue();
        void updateWaitingQueue();
};