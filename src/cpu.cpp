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
    wait = false;
}

// On every cpu cycle
void CPU::clockTick() {
    // scheduler.updateQueues();

    // if(swapProcess) {
    //     if(!(scheduler.getReadyQueue().empty())) {
    //         swapProcess = false;
    //     }
    // }

    if (!(scheduler.getReadyQueue().empty())) {
        wait = false;
    }

    // std::cout << std::endl;
    // std::cout << std::endl;
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
    // std::cout << "Instruction line " << this->pcb.getProgCount().instrNum << std::endl;
    // std::cout << "Num of instructions " << this->pcb.getInstructions().size() - 1 << std::endl;
    // std::cout << "Instruction type = " << this->pcb.getProgCount().instrType << std::endl;
    // std::cout << "Instruction size = " << this->pcb.getProgCount().remainingCycles << std::endl;

    if (wait == false) {
        this->execute();
        // std::cout << "Executing" << std::endl;
    }
    // dispatcher.updateQueues();
    scheduler.updateQueues(); // PROBLEM HERE

    this->clock++;
}

void CPU::execute() {
    // std::cout << "Instruction type: " << this->pcb.getProgCount().instrType << std::endl;
    switch (this->pcb.getProgCount().instrType) {
        case 0: // CALCULATE
            // std::cout << "PID: " << this->pcb.getPid() << std::endl;
            if(this->pcb.getProgCount().remainingCycles > 0) {
                // std::cout << "Remaining cycles: " << this->pcb.getProgCount().remainingCycles << std::endl;
                this->pcb.decrementCycles();
            }
            if(this->pcb.getProgCount().remainingCycles == 0) {
                if (this->pcb.getProgCount().instrNum >= (this->pcb.getInstructions().size() - 1)) {
                    // std::cout << "FINALLY" << std::endl;
                    scheduler.addProcessToTerminatedQueue(this->pcb);
                    // std::cout << "Process with PID: " << this->pcb.getPid() << " exited" << std::endl;
                    // swapProcess = true;
                    this->pcb = scheduler.getReadyQueue().front();
                    totalProcesses--;
                }
                else {
                    this->pcb.incrementInstrNum();
                }
            }
            break;
        case 1: // IO
            this->pcb.setIO(this->pcb.getProgCount().remainingCycles);
            // std::cout << "IO before: " << this->pcb.getIO() << std::endl;
            //     std::cout << "instruction num " << this->pcb.getProgCount().instrNum << std::endl;
            //     std::cout << "instructions size " << this->pcb.getInstructions().size() << std::endl;
            if(this->pcb.getProgCount().instrNum < this->pcb.getInstructions().size() - 1){

                // std::cout << "TEST" << std::endl;
                this->pcb.incrementInstrNum();
            }
            else {
                scheduler.addProcessToTerminatedQueue(this->pcb);
                this->pcb = scheduler.getReadyQueue().front();
                totalProcesses--;
            }

            scheduler.addProcessToWaitingQueue(this->pcb);

            if(!(scheduler.getReadyQueue().empty())) {
                this->pcb = scheduler.getReadyQueue().front();
            }
            else {
                wait = true;
            }
            // totalProcesses--;
            // swapProcess = true;
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