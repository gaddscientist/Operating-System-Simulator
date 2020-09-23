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
    long *CpuRegisters[MAXREGISTERS];
    // Instructions text
    char *instructions[MAXINSTRUCTIONS];
};

struct Process {
    int pid;
    struct PCB pcb;
};

struct PCB* PCB_new(int pid, state currentState, int progCount, int reqMem, int cycle, int givenCycles, long *CpuRegisters, char *instructions) {
    struct PCB* p = malloc(sizeof(struct PCB));
    p->pid = pid;
    p->currentState = currentState;
    p->progCount = progCount;
    p->reqMem = reqMem;
    p->cycle = cycle;
    p->givenCycles = givenCycles;
    memcpy(p->CpuRegisters, CpuRegisters, sizeof CpuRegisters[MAXREGISTERS]);
    memcpy(p->instructions, instructions, sizeof instructions[MAXINSTRUCTIONS]);
    return p;
}

/*
struct CpuRegister* CpuRegister_new() {

}
*/

struct Process* Process_new() {
    struct Process* p = malloc(sizeof(struct Process));
    // p->pcb.pid = next_pid++;
    // p->pcb.currentState = new;
    // p->pcb.progCount = 0;
    // p->pcb.reqMem = 1000;
    // p->pcb.cycle = 0;
    // p->pcb.givenCycles = 75;
    // memset(&p->pcb.CpuRegisters, sizeof p->pcb.CpuRegisters, 0);
    // memset(&p->pcb.instructions, sizeof p->pcb.instructions, 0);
    long* cpuRegisters = malloc(sizeof(cpuRegisters[MAXREGISTERS]));
    char* instructions = malloc(sizeof(instructions[MAXINSTRUCTIONS]));
    state initialState = NEW;
    p->pid = next_pid++;
    p->pcb = *PCB_new(p->pid, initialState, 0, 1000, 0, 75, cpuRegisters, instructions);
    return p;
}

// reanimate process

// process destructor



int main() {
    return 0;
}