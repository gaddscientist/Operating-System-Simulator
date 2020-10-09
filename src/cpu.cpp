#include "cpu.h"
#include "scheduler.h"
#include "dispatcher.h"

//testing
#include <iostream>

extern Dispatcher dispatcher;
extern Scheduler scheduler;
extern int totalProcesses;

CPU::CPU() {
    clock = 0;
    swapProcess = false;
    pcb = scheduler.getReadyQueue().front();
}

// On every cpu cycle
void CPU::clockTick() {
    // scheduler.updateQueues();

    // if(swapProcess) {
    //     if(!(scheduler.getReadyQueue().empty())) {
    //         pc;
    //         swapProcess = false;
    //     }
    // }

    std::cout << std::endl;
    std::cout << std::endl;
    // int num = 5;
    // for (int index = 0; num > 0; num--, index++) {
    //     // Prints out PID and Instructions
    //     std::cout << "PID = " << scheduler.getReadyQueue()[index].getPid() << std::endl;
    //     std::cout << "Burst time = " << scheduler.getReadyQueue()[index].getBurst() << std::endl;
    //     std::cout << "Instruction type = " << scheduler.getReadyQueue()[index].getProgCount().instrType << std::endl;
    //     std::cout << "Instruction size = " << scheduler.getReadyQueue()[index].getProgCount().remainingCycles << std::endl;
    // }
    // std::cout << "PID = " << this->pcb.getPid() << std::endl;
    // std::cout << "Burst Time = " << this->pcb.getBurst() << std::endl;
    // std::cout << "Instruction type = " << this->pcb.getProgCount().instrType << std::endl;
    // std::cout << "Instruction size = " << this->pcb.getProgCount().remainingCycles << std::endl;

    this->execute();
    // dispatcher.updateQueues();
    // scheduler.updateQueues(); // PROBLEM HERE

    this->clock++;
}

void CPU::execute() {
    switch (this->pcb.getProgCount().instrType) {
        case 0: // CALCULATE
            std::cout << "MADE IT TO CALCULATE" << std::endl;
            std::cout << "PID: " << this->pcb.getPid() << std::endl;
            std::cout << "Remaining cycles: " << this->pcb.getProgCount().remainingCycles << std::endl;
            if(this->pcb.getProgCount().remainingCycles > 0) {
                std::cout << "MADE IT" << std::endl;
                std::cout << "Remaining cycles: " << this->pcb.getProgCount().remainingCycles << std::endl;
                this->pcb.decrementCycles();
            }
            if(this->pcb.getProgCount().remainingCycles == 0) {
                scheduler.addProcessToTerminatedQueue(this->pcb);
                swapProcess = true;
                totalProcesses--;
            }
            break;
        case 1: // IO
            scheduler.addProcessToWaitingQueue(this->pcb);
            swapProcess = true;
            break;
        default:
            break;
    }

    // 1. get program counter (locally?)
    // 2. check the instruction type
    // 3. if calculate, ensure size > 0 (check this after decrementing remaining cycles too)
    //      -Decrement remaining cycles
    // 4. if IO, call dispatcher to move process to waiting queue and store pcb/pc
    // 5. update queues??
}



// Getters
int CPU::getClock() {
    return this->clock;
}

PCB CPU::getPcb() {
    return this->pcb;
}

// Setters
void CPU::setClock(int clock) {
    this->clock = clock;
}

void CPU::setPcb(PCB pcb) {
    this->pcb = pcb;
}