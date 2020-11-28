#pragma once
#include "scheduler.h"


// Dispatcher class to handle moving processes between states/queues
class Dispatcher {
public:
    // Constructor
    Dispatcher();


    // void UpdateState(PCB pcb, state newState);
    PCB getPcbFromReady();
    void addProcessToNewQueue(PCB p);
    void addProcessToReadyQueue(PCB p);
    void addCriticalToReadyQueue(PCB p);
    void addProcessToWaitingQueue(PCB& p);
    void addProcessToTerminatedQueue(PCB& p);

    // Function to sort ready queue by remaining time left
    // Only needed for SJF scheduling
    void updateReadyQueue();

    void killChildProcesses(PCB& p);
    void readyNewProcesses();
};