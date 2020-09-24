#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define MAXREGISTERS 10
#define MAXINSTRUCTIONS 1000

int next_pid = 0;
int totalProcesses = 0;
typedef enum {NEW, RUNNING, WAITING, READY, TERMINATED} state;
state initialState = NEW;

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
    p->pid = next_pid++;
    p->pcb = *PCB_new(p->pid, initialState, 0, 1000, 0, 75);
    totalProcesses++;
    return p;
}

void UpdateState(struct PCB* pcb, state newState) {
    pcb->currentState = newState;
}

// process destructor
// free(p)



// CLEAN UP THIS MESS
int main(int argc, char *argv[]) {
    if (argc <= 2) {
        printf("Please specify a template and number of processes to be created\n");
        printf("Syntax: ./process template.txt number_of_processes\n");
        printf("Example: ./process web_browser.txt 7\n");
        return 1;
    }

    char* template = argv[1];
    int numProcesses =  *argv[2] - '0';
    struct Process* processes[2000];
    int index;

    printf("Number of processes is %d\n", numProcesses);
    for (index = 0; numProcesses > 0; numProcesses--, index++) {
        processes[index] = Process_new();
        printf("Process: %d\n", processes[index]->pid);
    }

    return 0;
}