#include "process.h"
#include <iostream>
#include <cmath>


// Global variables
int next_pid = 0;
int totalProcesses = 0;
state initialState = NEW;

// Process constructor
Process::Process () {
    pid = next_pid++;
    pcb = PCB(pid, initialState, 0, 1000, 0, 75);
    totalProcesses++;
}

// Process destructor
Process::~Process() {
    totalProcesses--;
}

int Process::calculateBurst() {
    double burst = 0; 
    std::string::size_type sz;
    for (int i = 0; i < this->pcb.instructions.size(); i++) {
        int instrSize = std::stoi(this->pcb.instructions[i].substr(this->pcb.instructions[i].find(' ')), &sz);
        burst += instrSize;
    }
    burst = std::round((burst / this->pcb.instructions.size()));
    return (int)burst;
}



// Process destructor
// void KillProcess(struct Process* p) {
//     // free(p->pcb);
//     free(p);
//     totalProcesses--;
// }
