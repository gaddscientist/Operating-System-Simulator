#include <stdlib.h>
#include <string.h>

#define MAXREGISTERS 10
#define MAXINSTRUCTIONS 1000

int next_pid = 0;
typedef enum {NEW, RUNNING, WAITING, READY, TERMINATED} state;

struct PCB {
    // Unique identifier of process
    int pid;
    // Current state of process
    state currentState;
    // Location of next instruction
    int progCount;
    // Allocated memory
    int reqMem;
    // Current cycle
    int cycle;
    // Number of cycles allowed before swap
    int givenCycles;
    // Register data
    long *cpuRegisters[MAXREGISTERS];
    // Instructions text
    char *instructions[MAXINSTRUCTIONS];
};

struct Process {
    int pid;
    struct PCB pcb;
};

struct PCB* PCB_new(int pid, state currentState, int progCount, int reqMem, int cycle, int givenCycles) {
    struct PCB* p = malloc(sizeof(struct PCB));
    p->pid = pid;
    p->currentState = currentState;
    p->progCount = progCount;
    p->reqMem = reqMem;
    p->cycle = cycle;
    p->givenCycles = givenCycles;
    long* cpuRegisters;
    char* instructions;
    memset(p->cpuRegisters, 0, sizeof cpuRegisters[MAXREGISTERS]);
    memset(p->instructions, 0, sizeof instructions[MAXINSTRUCTIONS]);
    return p;
}


struct Process* Process_new() {
    struct Process* p = malloc(sizeof(struct Process));
    state initialState = NEW;
    p->pid = next_pid++;
    p->pcb = *PCB_new(p->pid, initialState, 0, 1000, 0, 75);
    return p;
}


// process destructor
// free(p)



int main() {
    return 0;
}