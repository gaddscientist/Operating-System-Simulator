#pragma once

#include "scheduler.h"
#include "cpu.h"



class Dispatcher {
    public:
        Dispatcher();


        void UpdateState(PCB pcb, state newState);
        void GetPcbFromReady();
};