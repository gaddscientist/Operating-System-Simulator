#include <iostream>
#include <cmath>
#include "process.h"
#include "dispatcher.h"


// Global variables
int next_pid = 1;
// extern int totalProcesses;
int totalProcesses = 0;
state initialState = NEW;
extern Dispatcher dispatcher;

// Process constructor
Process::Process (std::string templateFile) {
    pid = next_pid++;
    pcb = PCB(pid, initialState, 1000, templateFile);
    totalProcesses++;
}

Process::Process(std::deque<instruction> instrs) {
    pid = next_pid++;
    pcb = PCB(pid, initialState, 1000, instrs);
    totalProcesses++;
}

// Process destructor
Process::~Process() {
    // totalProcesses--;
}

// Creates a child process
// Currently creates an identical process to deal with processes being created from external templates
// Alternatively could make templateFile global and use that here to create new randomized process
int Process::fork() {
    Process newProcess(this->getPcb().getInstructionsList());
    dispatcher.addProcessToReadyQueue(newProcess.getPcb());
    return newProcess.getPid();
}

// Getters
int Process::getPid() {
    return this->pid;
}

PCB Process::getPcb() {
    return this->pcb;
}

// Setters
void Process::setPid(int pid) {
    this->pid = pid;
}

void Process::setPcb(PCB pcb) {
    this->pcb = pcb;
}