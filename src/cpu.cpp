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
    pcb = dispatcher.getPcbFromReady();
    interrupted = false;
    currentInstruction = pcb.getProgCount();
}

// On every cpu cycle
void CPU::clockTick() {
    
    // If there are ready processes
    if (!(scheduler.getReadyQueue().empty())) {
        this->pcb = dispatcher.getPcbFromReady();
        std::cout << "Clock: " << clock << " Executing process with PID " << pcb.getPid() << std::endl;
        this->execute();
    }
    else {
        std::cout << "Clock: " << clock << " CPU idle" << std::endl;
    }

    dispatcher.updateQueues();
    // scheduler.updateQueues(); // PROBLEM HERE

    this->clock++;
}

// One clock cycle execution
void CPU::execute() {
    // Gets the type of instruction to execute
    switch (this->pcb.getProgCount().instr.instrType) {
        case 0: // CALCULATE
            // Decrement one cycle from calculate instruction for this clock tick
            if(this->pcb.getProgCount().instr.remainingCycles > 0) {
                this->pcb.decrementCycles();
            }
            // If the last cycle was just decremented
            if(this->pcb.getProgCount().instr.remainingCycles == 0) {
                // Checks to see if that was the last instruction in the list of instructions for this process
                if (this->pcb.getProgCount().instrNum >= (this->pcb.getInstructions().size() - 1)) {
                    // Moves process to terminated queue
                    scheduler.addProcessToTerminatedQueue(this->pcb); // MOVE TO DISPATCHER
                    // swapProcess = true;
                    // Gets the next process
                    this->pcb = scheduler.getReadyQueue().front(); // MOVE TO DISPATCHER
                    totalProcesses--;
                }
                else {
                    // Gets the next instruction from the list of instructions
                    this->pcb.incrementInstrNum();
                }
            }
            break;
        case 1: // IO
            // Sets the number of IO cycles that need to execute
            this->pcb.setIO(this->pcb.getProgCount().instr.remainingCycles);
            // If this wasn't the last instruction in the process
            if(this->pcb.getProgCount().instrNum <= this->pcb.getInstructions().size() - 1){
                // Move to next instruction
                this->pcb.incrementInstrNum();
            }
            else {
                std::cout << "instrNum: " << this->pcb.getProgCount().instrNum;
                std::cout << " instructions size: " << this->pcb.getInstructions().size() << std::endl;
                // Terminates process and gets the next one
                scheduler.addProcessToTerminatedQueue(this->pcb);
                this->pcb = scheduler.getReadyQueue().front();
                totalProcesses--;
            }

            scheduler.addProcessToWaitingQueue(this->pcb);

            if(!(scheduler.getReadyQueue().empty())) {
                this->pcb = scheduler.getReadyQueue().front();
            }
            // totalProcesses--;
            // swapProcess = true;
            break;
        default:
            break;
    }
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