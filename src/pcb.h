#pragma once
#include <vector>
#include <string>

enum state {NEW, RUNNING, WAITING, READY, TERMINATED};

class PCB {
public:
    int pid;                // Unique identifier of process
    state currentState;     // Current state of process
    int progCount;          // Location of next instruction
    int reqMem;             // Allocated memory
    int cycle;              // Current cycle
    int givenCycles;        // Number of cycles allowed before swap
    std::vector<int> cpuRegisters;   // Register data
    std::vector<std::string> instructions;    // Instructions text

    PCB () {}
    PCB (int PID, state CurrentState, int ProgCount, int ReqMem, int Cycle, int GivenCycles, std::string templateFile);


    void UpdateState(PCB pcb, state newState);
};