#pragma once

#include "scheduler.h"
#include "cpu.h"



class Dispatcher {
    public:
        Dispatcher();


        // void UpdateState(PCB pcb, state newState);
        PCB getPcbFromReady();
        void addProcessToReadyQueue(PCB p);
        void addProcessToWaitingQueue(PCB p);
        void addProcessToTerminatedQueue(PCB p);
        void updateQueues();
};