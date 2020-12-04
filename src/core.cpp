#include <thread>
#include <iostream>
#include "os.h"
#include "cpu.h"
#include "core.h"
#include "scheduler.h"
#include "dispatcher.h"

extern OS os;
extern CPU cpu;
extern Dispatcher dispatcher;
extern Scheduler scheduler;
extern int totalProcesses;
extern Semaphore S;

Core::Core() {
    coreNum = 1;
    cycleTime = 10; // 10ms    
    timeSlice = 15; // 15 cycles before pre-emption
    remainingCache = totalCache;
}

Core::Core(int num) {
    coreNum = num;
    cycleTime = 10; // 10ms    
    timeSlice = 15; // 15 cycles before pre-emption
    remainingCache = totalCache;
}

void Core::execute() {
    // If the ready queue has processes
    if(!(scheduler.getReadyQueue().empty()) && scheduler.getReadyQueue().front().getCurrentState() != NEW) {
        this->pcb = dispatcher.getPcbFromReady();
        std::cout << "Process " << this->pcb.getPid() << " on CPU core " << this->coreNum << std::endl;
        this->pcb.setCurrentState(RUNNING);

        // Retrieve instruction to be executed
        instruction currentInstruction = this->pcb.getNextInstruction();

        switch(currentInstruction.instrType) {
            // Calculate Instruction
            case 0:
            {
                std::cout << "Executing process " << this->pcb.getPid() << std::endl;
                remainingCache -= this->pcb.getReqMem();
                // Number of cycles executed this time slice
                int cycleCount = 0;

                // Continue executing while there are cycles left in the instruction
                // and the instruction's time slice hasn't expired
                while(currentInstruction.remainingCycles > 0 && cpu.interrupts.empty()) {
                    cycleCount++;

                    // Sleep the thread for a number of milliseconds to simulate
                    // actual time needed to execute a clock cycle
                    std::this_thread::sleep_for(std::chrono::milliseconds(cycleTime));
                    currentInstruction.remainingCycles--;

                    // Checks to see if time slice has expired
                    if(cycleCount == timeSlice) {
                        // -1 chosen as its an impossible PID
                        cpu.interrupts.push_back(Interrupt(-1));
                        std::cout << "Time slice for process " << this->pcb.getPid() << " Expired" << std::endl;
                    }
                }

                // If instruction finished
                if (currentInstruction.remainingCycles == 0) {
                    std::cout << "Process " << this->pcb.getPid() << " CALCULATE instruction has finished" << std::endl;
                    // Increments the program counter if instruction completed
                    this->pcb.incrementInstrNum();
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
                int pid = this->pcb.getPid();

                if(currentInstruction.device == KEYBOARD) {
                    std::cout << "Process " << pid << " beginning keyboard IO" << std::endl;
                }
                else if(currentInstruction.device == MONITOR) {
                    std::cout << "Process " << pid << " beginning monitor IO" << std::endl;
                }
                else if(currentInstruction.device == MONITOR) {
                    std::cout << "Process " << pid << " beginning disk IO" << std::endl;
                }
                // Increments the program counter
                this->pcb.incrementInstrNum();
                // Add process to appropriate waiting queue until its moved back to ready queue
                if(currentInstruction.device == KEYBOARD) {
                    dispatcher.addProcessToKeyboardWaitingQueue(this->pcb);
                }
                else if(currentInstruction.device == MONITOR) {
                    dispatcher.addProcessToMonitorWaitingQueue(this->pcb);
                }
                else if(currentInstruction.device == DISK) {
                    dispatcher.addProcessToDiskWaitingQueue(this->pcb);
                }

                // Execute IO on separate thread for concurrency
                // Meant to simulate how IO would not tie up the CPU
                // Process sleeps until IO instructions have completed
                std::thread ioThread([this, currentInstruction, pid]() {
                    std::this_thread::sleep_for(std::chrono::milliseconds(currentInstruction.remainingCycles * cycleTime));

                    // Checks to see if process was terminated early by cascading termination while sleeping for IO
                    bool killed = false;
                    // Checks the terminated queue for the process index
                    for (std::deque<PCB>::iterator it = scheduler.getTerminatedQueue().begin(); it != scheduler.getTerminatedQueue().end(); it++) {
                        // If child process is found
                        if((*it).getPid() == pid) {
                            killed = true;
                            totalProcesses--;
                        }
                    }

                    if(!killed) {
                        // Once IO has finished, signal interrupt
                        cpu.interrupts.push_back(Interrupt(pid, currentInstruction.device));
                    }

                });
                // Exception thrown if thread not detached or joined. Join would cause parent thread to wait
                ioThread.detach();


                break;
            }
            // CRITICAL
            case 2:
            {
                cpu.wait(S, this->getPcb());

                std::cout << "Executing critical section for process " << this->pcb.getPid() << std::endl;
                remainingCache -= this->pcb.getReqMem();
                // Number of cycles executed this time slice
                int cycleCount = 0;

                // Continue executing while there are cycles left in the instruction
                // and the instruction's time slice hasn't expired
                while(currentInstruction.remainingCycles > 0 && cpu.interrupts.empty()) {
                    cycleCount++;

                    // Sleep the thread for a number of milliseconds to simulate
                    // actual time needed to execute a clock cycle
                    std::this_thread::sleep_for(std::chrono::milliseconds(cycleTime));
                    currentInstruction.remainingCycles--;

                    // Checks to see if time slice has expired
                    if(cycleCount == timeSlice) {
                        // -1 chosen as its an impossible PID
                        cpu.interrupts.push_back(Interrupt(-1));
                        std::cout << "Time slice for process " << this->pcb.getPid() << " Expired" << std::endl;
                    }
                }

                // If instruction finished
                if (currentInstruction.remainingCycles == 0) {
                    std::cout << "Process " << this->pcb.getPid() << " critical section has finished" << std::endl;
                    // Increments the program counter if instruction completed
                    this->pcb.incrementInstrNum();
                }
                else {
                    // Otherwise put at front of instruction queue
                    this->pcb.pushInstructionBack(currentInstruction);
                }

                cpu.signal(S);
                break;
            }
            // FORK
            case 3:
            {
                remainingCache -= this->pcb.getReqMem();
                // Creates a child process
                PCB* childPCB = os.fork(this->getPcb());
                // Gives parent a pointer to the child
                this->getPcb().getChildProcesses().push_back(childPCB);
                break;
            }
            // EXIT
            case 4:
            {
                remainingCache -= this->pcb.getReqMem();
            }
            default:
            {
                break;
            }
        }

        // Checks to see that there is only the exit instruction left and process is not waiting
        if (this->pcb.getInstructionsRemaining().size() <= 1 && this->pcb.getCurrentState() != WAITING) {
            dispatcher.addProcessToTerminatedQueue(this->pcb);
            std::cout << "Process " << this->pcb.getPid() << " terminated" << std::endl;
            remainingCache += this->pcb.getReqMem();
        }

        // If the processes didnt hit IO instruction or terminate
        if (this->pcb.getCurrentState() == RUNNING) {
            // Dispatch program from cpu back to ready queue
            dispatcher.addProcessToReadyQueue(this->pcb);
            remainingCache += this->pcb.getReqMem();
        }
    }
    // Ready queue has no processes
    else {
        // Stops idle logging when waiting for last processes IO to complete on separate thread
        if(scheduler.getTerminatedQueue().size() < (size_t)os.numProcesses) {
            std::cout << "CPU Idle: No processes ready to be executed" << std::endl;
        }
        // Thread sleeps so there is less output while idle
        std::this_thread::sleep_for(std::chrono::milliseconds(80)); 
    }
}

PCB& Core::getPcb() {
    return this->pcb;
}