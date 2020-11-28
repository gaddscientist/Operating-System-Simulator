#include <iostream>
#include <cmath>
#include "process.h"
#include "dispatcher.h"


// Global variables
int next_pid = 1;
int totalProcesses = 0;
state initialState = NEW;
extern Dispatcher dispatcher;

// Process constructor
Process::Process (std::string templateFile) {
    pid = next_pid++;
    pcb = new PCB(pid, initialState, templateFile);
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

PCB* Process::getPcb() {
    return this->pcb;
}

// Setters
void Process::setPid(int pid) {
    this->pid = pid;
}

void Process::setPcb(PCB* pcb) {
    this->pcb = pcb;
}