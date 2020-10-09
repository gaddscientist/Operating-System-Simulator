#pragma once
#include <deque>
#include <string>

enum state {NEW, RUNNING, WAITING, READY, TERMINATED};

class PCB {
private:
    int pid;                                // Unique identifier of process
    state currentState;                     // Current state of process
    int progCount;                          // Location of next instruction
    int reqMem;                             // Allocated memory
    int cycle;                              // Current cycle
    std::deque<int> cpuRegisters;           // Register data
    std::deque<std::string> instructions;   // Instructions text
    int burst;                              // Number of cycles for function to complete
    int io;                                 // IO cycles required for IO instruction

    // Member functions
    int calculateBurst();

public:
    // Constructors
    PCB () {}
    PCB (int PID, state CurrentState, int ProgCount, int ReqMem, int Cycle, std::string templateFile);

    // Getters
    int getPid();
    state getCurrentState();
    int getProgCount();
    int getReqMem();
    int getCycle();
    std::deque<int> getCpuRegisters();
    std::deque<std::string> getInstructions();
    int getBurst();
    int getIO();

    // Setters
    void setPid(int pid);
    void setCurrentState(state currentState);
    void setProgCount(int progCount);
    void setReqMem(int reqMem);
    void setCycle(int cycle);
    void setCpuRegisters(std::deque<int> cpuRegisters);
    void setInstructions(std::deque<std::string> instructions);
    void setBurst(int burst);
    void setIO(int io);

};
