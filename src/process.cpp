#include "process.h"
#include <iostream>
#include <cmath>


// Global variables
int next_pid = 1;
// extern int totalProcesses;
int totalProcesses = 0;
state initialState = NEW;

// Process constructor
Process::Process (std::string templateFile) {
    pid = next_pid++;
    pcb = PCB(pid, initialState, 1000, templateFile);
    totalProcesses++;
}

// Process destructor
Process::~Process() {
    // totalProcesses--;
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