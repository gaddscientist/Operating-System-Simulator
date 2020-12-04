#include <ctime>
#include <thread>
#include <iostream>
#include "cpu.h"
#include "scheduler.h"
#include "dispatcher.h"
#include "os.h"

extern Dispatcher dispatcher;   // Defined in os.cpp
extern Scheduler scheduler;     // Defined in dispatcher.cpp
extern int totalProcesses;      // Defined in process.cpp
Semaphore S;

CPU::CPU() {
    // Saves starting time and prints OS start
    startTime = std::clock();
    this->interrupts = std::deque<Interrupt>();
    this->numCores = 2;
    this->cores = std::vector<Core>();
    for(int i = 0; i < numCores; ++i) {
        cores.push_back(Core(i));
    }

    // Clears set of cores set by underlying operating system
    CPU_ZERO(&physicalCores);
    
    // Adds a core to the set of cores to work with based on how many simulator allows for
    for(int i = 0; i < numCores; i++) {
        CPU_SET(i, &physicalCores);
    }
}

// Execute process until interruption
void CPU::execute() {

    // Move interrupted processes back to ready queue
    // Processes only added to interrupt queue after finishing IO cycles on separate thread
    // or when pre-empted by expired time slice
    while(!interrupts.empty()) {
        // For each interrupt, remove it from the list of interrupts
        Interrupt interrupt = interrupts.front();
        interrupts.pop_front();

        // Moves the interrupted process from waiting to ready queue
        // Process ID's start at 1, pid=0 signifies an expired time slice interrupt
        if(interrupt.pid > 0) {
            PCB p;
            // Gets the process from the appropriate waiting queue and removes it
            if(interrupt.device == KEYBOARD) {
                p = scheduler.getKeyboardWaitingQueue().at(interrupt.pid);
                scheduler.getKeyboardWaitingQueue().erase(interrupt.pid);
                std::cout << "Process " << interrupt.pid << " finished keyboard IO" << std::endl;
            }
            else if(interrupt.device == MONITOR) {
                p = scheduler.getMonitorWaitingQueue().at(interrupt.pid);
                scheduler.getMonitorWaitingQueue().erase(interrupt.pid);
                std::cout << "Process " << interrupt.pid << " finished monitor IO" << std::endl;
            }
            else if(interrupt.device == DISK) {
                p = scheduler.getDiskWaitingQueue().at(interrupt.pid);
                scheduler.getDiskWaitingQueue().erase(interrupt.pid);
                std::cout << "Process " << interrupt.pid << " finished disk IO" << std::endl;
            }

            // Checks to see if process was killed by parent process
            // Note: This will only occur if child process gets terminated while IO is executing on separate thread
            if (p.getCurrentState() == TERMINATED) {
                dispatcher.addProcessToTerminatedQueue(p);
            }
            else {
                dispatcher.addProcessToReadyQueue(p);
                std::cout << "Process " << interrupt.pid << " moved to ready queue" << std::endl;
            }
        }
    }


    // Vector to track threads created per execution cycle
    std::vector<std::thread> threads;

    // Creates a thread and has a core execute it
    for(int i = 0; i < numCores; ++i) {
        threads.push_back(std::thread([this, i] {
            this->cores[i].execute();
        }));

        // Sets created thread's affinity to only run on cores in the defined set
        pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &physicalCores);
    }
    
    // Forces loop to wait for threads to finish their cycles before next iteration
    for(auto& t : threads) {
        t.join();
    }
}



// Getters
double CPU::getClock() {
    double duration = (std::clock() - startTime) / (double) CLOCKS_PER_SEC;
    return duration;
}

void CPU::wait(Semaphore S, PCB& p) {
    if (S.count == 1) {
        S.count = 0;
    }
    else {
        S.blockedProcesses.push_back(p);
    }
}

void CPU::signal(Semaphore S) {
    if (S.blockedProcesses.empty()) {
        S.count = 1;
    }
    else {
        S.count = 1;
        if(S.blockedProcesses.size() > 0) {
            dispatcher.addCriticalToReadyQueue(S.blockedProcesses.front());
            S.blockedProcesses.pop_front();
        }
    }
}