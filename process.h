#define MAXREGISTERS 10         // Max number of registers to be stored in PCB array
#define MAXINSTRUCTIONS 100     // Max number of instructions that can be stored in PCB
#define MAXPROCESSES 2000       // Max number of processes that can be active at once

typedef enum {NEW, RUNNING, WAITING, READY, TERMINATED} state;
state initialState = NEW;

struct PCB {
    int pid;                            // Unique identifier of process
    state currentState;                 // Current state of process
    int progCount;                      // Location of next instruction
    int reqMem;                         // Allocated memory
    int cycle;                          // Current cycle
    int givenCycles;                    // Number of cycles allowed before swap
    long *cpuRegisters[MAXREGISTERS];   // Register data
    char instructions[MAXINSTRUCTIONS]; // Instructions text
};

struct Process {
    int pid;
    struct PCB pcb;
};

// Function prototypes
// Constructors
struct PCB* PCB_new(int pid, state currentState, int progCount, int reqMem, int cycle, int givenCycles);
struct Process* Process_new();

// Methods
void UpdateState(struct PCB* pcb, state newState);
void ParseTemplate(char* tp, char instructions[]);
void KillProcess(struct Process* p);

// From K&R's The C Programming Language
void itoa(int n, char s[]);
void reverse(char s[]);