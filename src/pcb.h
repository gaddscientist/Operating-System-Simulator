#pragma once
#include <deque>
#include <string>

// Possible states of process
enum state {NEW, RUNNING, WAITING, READY, TERMINATED};
// Possible instructions
enum instructionType {CALCULATE, IO, EXIT, ERROR};

// Instruction struct to store instructions as objects instead of plaintext
struct instruction {
    instructionType instrType;
    int remainingCycles;
};

class PCB {
private:
    int pid;                                        // Unique identifier of process
    state currentState;                             // Current state of process
    int progCount;                                  // Location of next instruction
    int reqMem;                                     // Allocated memory
    int cycle;                                      // Current cycle
    std::deque<int> cpuRegisters;                   // Register data
    std::deque<instruction> instructionsList;       // Instructions text
    std::deque<instruction> instructionsRemaining;  // Instructions text
    int burst;                                      // Number of cycles for function to complete
    int io;                                         // IO cycles required for IO instruction

    // Member functions
    int calculateBurst();
    instruction Randomize(std::string& str);
    std::deque<instruction> ParseTemplate(const std::string tp);

public:
    // Constructors
    PCB () {}
    PCB (int PID, state CurrentState, int ReqMem, std::string templateFile);

    // void decrementCycles();
    void incrementInstrNum();

    // Getters
    int getPid();
    state getCurrentState();
    int getProgCount();
    int getReqMem();
    int getCycle();
    std::deque<int> getCpuRegisters();
    std::deque<instruction> getInstructionsList();
    std::deque<instruction> getInstructionsRemaining();
    instruction getNextInstruction();
    void pushInstructionBack(instruction instr);
    int getBurst();
    int getIO();
    instructionType getInstructionType(std::string line);

    // Setters
    void setPid(int pid);
    void setCurrentState(state currentState);
    void setProgCount(int progCount);
    void setReqMem(int reqMem);
    void setCycle(int cycle);
    void setCpuRegisters(std::deque<int> cpuRegisters);
    void setInstructions(std::deque<instruction> instructions);
    void setBurst(int burst);
    void setIO(int io);
    void setInstructionSize(int size);

};