#pragma once

#include <vector>
#include "process.h"

enum schedulerType {INVALID = 0, SJF, RR};

class Scheduler {
    public:
        // clock
        // cpu
        schedulerType chosenScheduler;
        std::vector<Process> newQueue;
        std::vector<Process> readyQueue;
        std::vector<Process> waitingQueue;
        // If you want to keep track of finished processes
        std::vector<Process> terminatedQueue;

        // Default constructor
        Scheduler (schedulerType st);

        // Member functions
        void sortProcesses();
};