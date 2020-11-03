#include "cpu.h"
#include "scheduler.h"
#include "dispatcher.h"
#include <ctime>
#include <thread>

//testing
#include <iostream>

extern Dispatcher dispatcher;
extern Scheduler scheduler;
extern int totalProcesses;

CPU::CPU() {
    // pcb = dispatcher.getPcbFromReady(); // ERROR HERE
    interrupted = false;
    cycleTime = 10; // 10ms    
    timeSlice = 15; // 15 cycles before pre-emption
    // Saves starting time and prints OS start
    startTime = std::clock();
    this->interrupts = std::deque<Interrupt>();
}

void CPU::execute() {
    // Gets the type of instruction to execute
    // currentInstruction = this->pcb.getNextInstruction();

    while(!(scheduler.getReadyQueue().empty()) || !(scheduler.getWaitingQueue().empty())) {
        // Move interrupted processes back to ready queue
        while(!interrupts.empty()) {
            // For each interrupt, remove it from the list of interrupts
            Interrupt interrupt = interrupts.front();
            interrupts.pop_front();

            // Moves the interrupted process from waiting to ready queue
            if(interrupt.pid > 0) {
                PCB p = scheduler.getWaitingQueue().at(interrupt.pid);
                scheduler.getWaitingQueue().erase(interrupt.pid);

                p.setCurrentState(READY);
                dispatcher.addProcessToReadyQueue(p);
                std::cout << "Process " << interrupt.pid << " completed IO" << std::endl;
            }
        }

        // If the ready queue has processes
        if(!(scheduler.getReadyQueue().empty())) {
            this->pcb = dispatcher.getPcbFromReady();
            std::cout << "Process " << this->pcb.getPid() << " on CPU" << std::endl;
            this->pcb.setCurrentState(RUNNING);

            // Execute current instruction
            instruction currentInstruction = this->pcb.getNextInstruction();

            switch(currentInstruction.instrType) {
                // Calculate Instruction
                case 0:
                {
                    std::cout << "Executing process " << this->pcb.getPid() << std::endl;
                    int cycleCount = 0;

                    while(currentInstruction.remainingCycles > 0 && interrupts.empty()) {
                        cycleCount++;

                        std::this_thread::sleep_for(std::chrono::milliseconds(cycleTime));
                        currentInstruction.remainingCycles--;

                        if(cycleCount == timeSlice) {
                            // 0 chosen for interrupt as PID's start at 1
                            interrupts.push_back(Interrupt(0));
                            std::cout << "Time slice for process " << this->pcb.getPid() << " Expired" << std::endl;
                        }
                    }

                    // If instruction finished
                    if (currentInstruction.remainingCycles == 0) {
                        std::cout << "Process " << this->pcb.getPid() << " CALCULATE instruction has finished" << std::endl;
                    }
                    else {
                        // Otherwise put at front of instruction queue
                        this->pcb.pushInstructionBack(currentInstruction);
                    }

                    break;
                }
                // IO Instruction
                case 1:
                {
                    std::cout << "Process " << this->pcb.getPid() << " beginning IO" << std::endl;
                    // Execute IO on separate thread for concurrency
                    int pid = this->pcb.getPid();
                    std::thread ioThread([this, currentInstruction, pid]() {
                        std::this_thread::sleep_for(std::chrono::milliseconds(currentInstruction.remainingCycles * cycleTime));
                        std::cout << "Process " << pid << " finished IO" << std::endl;
                        interrupts.push_back(pid);
                    });
                    ioThread.detach();
                        // std::this_thread::sleep_for(std::chrono::milliseconds(currentInstruction.remainingCycles * cycleTime));
                        // std::cout << "Process " << pid << " finished IO" << std::endl;
                        // interrupts.push_back(pid);

                    this->pcb.setCurrentState(WAITING);
                    dispatcher.addProcessToWaitingQueue(this->pcb);

                    break;
                }
                default:
                {
                    break;
                }
            }

            if (this->pcb.getInstructionsRemaining().size() <= 1 && this->pcb.getCurrentState() != WAITING) {
            // if (this->pcb.getInstructionsRemaining().size() <= 1) {
                this->pcb.setCurrentState(TERMINATED);
                dispatcher.addProcessToTerminatedQueue(this->pcb);
                totalProcesses--;
            }

            // If the processes didnt hit IO instruction or terminate
            if (this->pcb.getCurrentState() == RUNNING) {
                // Dispatch program from cpu back to ready queue
                dispatcher.addProcessToReadyQueue(this->pcb);
            }
        }
        // Ready queue has no processes
        else {
            std::cout << "CPU Idle: No processes ready to be executed" << std::endl;
            std::this_thread::sleep_for(
                std::chrono::milliseconds(50)
            ); 
        }
    }
}



// Getters
double CPU::getClock() {
    double duration = (std::clock() - startTime) / (double) CLOCKS_PER_SEC;
    return duration;
}

PCB CPU::getPcb() {
    return this->pcb;
}

// Setters
void CPU::setPcb(PCB pcb) {
    this->pcb = pcb;
}



