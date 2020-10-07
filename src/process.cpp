#include "process.h"


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



// Process destructor
// void KillProcess(struct Process* p) {
//     // free(p->pcb);
//     free(p);
//     totalProcesses--;
// }
