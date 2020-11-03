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


// On every cpu cycle
// void CPU::clockTick() {
      


    // If there are ready processes
    // if (!(scheduler.getReadyQueue().empty())) {
    //     if(interrupted) {
    //         interrupted = false;
    //         this->pcb = dispatcher.getPcbFromReady();
    //     }
    //     std::cout << "Clock: " << clock << " Executing process with PID " << pcb.getPid() << std::endl;
    //     this->execute();
    // }
    // else {
    //     std::cout << "Clock: " << clock << " CPU idle" << std::endl;
    // }

    // dispatcher.updateQueues();
    // // scheduler.updateQueues(); // PROBLEM HERE

    // this->clock++;
// }

// One clock cycle execution
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
    // switch (currentInstruction.instrType) {
    //     case 0: // CALCULATE




            // // Decrement one cycle from calculate instruction for this clock tick
            // if(currentInstruction.remainingCycles > 0) {
            //     currentInstruction.remainingCycles--;
            // }
            // // If the last cycle was just decremented
            // if(currentInstruction.remainingCycles == 0) {
            //     // Checks to see if that was the last instruction in the list of instructions for this process
            //     // if (this->pcb.getProgCount().instrNum >= (this->pcb.getInstructions().size() - 1)) {
            //     if (this->pcb.getInstructionsRemaining().empty()) {
            //         // Moves process to terminated queue
            //         scheduler.addProcessToTerminatedQueue(this->pcb); // MOVE TO DISPATCHER
            //         // swapProcess = true;
            //         // Gets the next process
            //         // this->pcb = scheduler.getReadyQueue().front(); // MOVE TO DISPATCHER
            //         // this->pcb = dispatcher.getPcbFromReady();
            //         interrupted = true;
            //         totalProcesses--;
            //     }
            //     // else {
            //     //     // Gets the next instruction from the list of instructions
            //     //     // this->pcb.incrementInstrNum();
                    
            //     // }
            //     // scheduler.addProcessToWaitingQueue();
            //     this->pcb.incrementInstrNum();
            //     std::cout << "Calculate Instruction " << this->pcb.getProgCount() << " from PID: " << this->pcb.getPid() << " Finished" << std::endl;
            // }
            // else {
            //     // this->pcb.getInstructionsRemaining().push_front(currentInstruction);
            //     this->pcb.pushInstructionBack(currentInstruction);
            // }
        //     break;
        // case 1: // IO
        //     // Sets the number of IO cycles that need to execute
        //     this->pcb.setIO(currentInstruction.remainingCycles);
        //     // If this wasn't the last instruction in the process
        //     if(!(this->pcb.getInstructionsRemaining().empty())){
        //         // Move to next instruction
        //         // this->pcb.incrementInstrNum();
        //     }
        //     else {
        //         std::cout << "instrNum: " << this->pcb.getProgCount() << std::endl;
        //         // std::cout << " instructions size: " << this->pcb.getInstructions().size() << std::endl;
        //         // Terminates process and gets the next one
        //         scheduler.addProcessToTerminatedQueue(this->pcb);
        //         // this->pcb = scheduler.getReadyQueue().front();
        //         interrupted = true;
        //         totalProcesses--;
        //     }

        //     scheduler.addProcessToWaitingQueue(this->pcb);
        //     interrupted = true;

        //     // if(!(scheduler.getReadyQueue().empty())) {
        //     //     this->pcb = scheduler.getReadyQueue().front();
        //     // }
        //     // totalProcesses--;
        //     // swapProcess = true;
        //     break;
        // default:
        //     break;
    // }
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