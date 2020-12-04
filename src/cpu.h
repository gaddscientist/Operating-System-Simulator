#pragma once
#include <deque>
#include "pcb.h"
#include "core.h"

// Semaphore
struct Semaphore {
    int count = 1;
    std::deque<PCB> blockedProcesses = std::deque<PCB>();
};

// Creates an interrupt object that corresponds to the interrupted process
struct Interrupt {
    int pid;        // Interrupted processes id
    ioType device;  // Which device caused interrupt

    // Constructor for quantum expiration interrupt
    Interrupt(int id) 
        : pid(id), device(NONE) {}
    // Constructor for IO interrupt
    Interrupt(int id, ioType io)
        : pid(id), device(io) {}
};

// CPU class to handle execution of process instructions
class CPU {
public:
    // Default constructor
    CPU();

    // void clockTick();
    void execute();

    // Getters
    double getClock();
    // PCB& getPcb();

    // Setters
    void setClock(int clock);

    // Queue to hold interrupted processes
    std::deque<Interrupt> interrupts;
    
    // Semaphore methods 
    void wait(Semaphore S, PCB& p);
    void signal(Semaphore S);

    // Multi-core variables
    std::vector<Core> cores;
    int numCores;
    // Creates a set of logical cpu's(cores) for operating system
    cpu_set_t physicalCores;

private:
    int startTime;  // Start of execution

};
