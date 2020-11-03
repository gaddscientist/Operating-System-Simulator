#pragma once

#include <deque>
#include <map>
#include "pcb.h"

enum schedulerType {INVALID = 0, SJF, RR};

class Scheduler {
    private:
        // clock
        // cpu
        schedulerType chosenScheduler;
        std::deque<PCB> newQueue;
        std::deque<PCB> readyQueue;
        std::map<int, PCB> waitingQueue;
        // If you want to keep track of finished processes
        std::deque<PCB> terminatedQueue;

    public:
        // Default constructor
        Scheduler ();

        // Getters
        std::deque<PCB> getNewQueue();
        std::deque<PCB>& getReadyQueue();
        std::map<int, PCB>& getWaitingQueue();
        std::deque<PCB>& getTerminatedQueue();
        schedulerType getChosenScheduler();

        // Setters
        void setSchedulerType(schedulerType st);

        // Member functions
        void sortReadyProcesses();
        void sortWaitingProcesses();


        // void updateQueues();
        void updateReadyQueue();
        void updateWaitingQueue();


        void addProcessToReadyQueue(PCB p);
        void addProcessToWaitingQueue(PCB p);
        void addProcessToTerminatedQueue(PCB p);
};