#pragma once

#include <deque>
#include <map>
#include "pcb.h"

enum schedulerType {INVALID = 0, SJF, RR};

// Scheduler class to hold processes in different queues and organize them if needed
class Scheduler {
    private:
        schedulerType chosenScheduler;              // Chosen scheduling algorithm
        std::deque<PCB> newQueue;                   // Processes that haven't been alotted memory
        std::deque<PCB> readyQueue;                 // Processes ready to execute
        std::map<int, PCB> keyboardWaitingQueue;    // Processes blocked by IO or expired timeslice
        std::map<int, PCB> monitorWaitingQueue;     // Processes blocked by IO or expired timeslice
        std::map<int, PCB> diskWaitingQueue;        // Processes blocked by IO or expired timeslice
        std::deque<PCB> terminatedQueue;            // To keep track of finished processes

    public:
        // Default constructor
        Scheduler ();

        // Getters
        std::deque<PCB>& getNewQueue();
        std::deque<PCB>& getReadyQueue();
        std::map<int, PCB>& getKeyboardWaitingQueue();
        std::map<int, PCB>& getMonitorWaitingQueue();
        std::map<int, PCB>& getDiskWaitingQueue();
        std::deque<PCB>& getTerminatedQueue();
        schedulerType getChosenScheduler();

        // Setters
        void setSchedulerType(schedulerType st);

        // Member functions
        // Sorts processes in ready queue by their total run times
        void sortReadyProcesses();

};