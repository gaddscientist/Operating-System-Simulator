#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "process.h"


// Global variables
int next_pid = 0;
int totalProcesses = 0;

// Driver function
int main(int argc, char *argv[]) {
    // Ensures correct sytax
    if (argc <= 2) {
        printf("Please specify a template and number of processes to be created\n");
        printf("Syntax: ./process template.txt number_of_processes\n");
        printf("Example: ./process web_browser.txt 7\n");
        exit(1);
    }

    // Uses current time to as seed for rand()
    srand(time(0));

    char* template = argv[1];                   // User specified template
    int numProcesses =  *argv[2] - '0';         // User specified number of processes to create
    struct Process* processes[MAXPROCESSES];    // Array of processes to be created
    int index;                                  // Process index

    // Loop to create processes with randomized instruction cycles
    for (index = 0; numProcesses > 0; numProcesses--, index++) {
        processes[index] = Process_new();
        ParseTemplate(template, processes[index]->pcb.instructions);
        printf("PID=%d\n%s\n\n",processes[index]->pcb.pid, processes[index]->pcb.instructions);
    }
    
    printf("%d processes were created\n", totalProcesses);

    return 0;
}


// Constructor for new PCB struct
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


// Constructor for new Process struct
struct Process* Process_new() {
    struct Process* p = malloc(sizeof(struct Process));
    p->pid = next_pid++;
    p->pcb = *PCB_new(p->pid, initialState, 0, 1000, 0, 75);
    totalProcesses++;
    return p;
}

// Updates the state of the process associated with this PCB
void UpdateState(struct PCB* pcb, state newState) {
    pcb->currentState = newState;
}

void ParseTemplate(char* tp, char instructions[]) {
    // Opens passed file name or prints error
    FILE *fp = fopen(tp, "r");
    if(fp == NULL) {
        printf("ERROR: File not opened");
        exit(1);
    }

    // Buffer to hold line
    char buff[128];

    // Gets lines one at a time
    while(fgets(buff, sizeof(buff), fp) != NULL) {
        char cycles[3];
        int randInt = (rand());

        // Gets a random int between 10 and 90
        while (randInt > 100) {
            randInt = randInt % 10;
            if (randInt == 0) {
                randInt = (rand());
            }
        }
        randInt = randInt * 10;     // Find way to delete this line, shouldnt be necessary

        itoa(randInt, cycles);      // Converts random integer to a string
        strtok(buff, "\n");         // Removes newline character from fgets()
        strcat(buff, " ");
        strcat(buff, cycles);       // Concatenate instruction with random number of cycles
        strcat(instructions, buff); // Adds randomized instruction to list of instructions
        strcat(instructions, "\n");
    }

    fclose(fp); // Closes file pointer
}

// Process destructor
void KillProcess(struct Process* p) {
    // free(p->pcb);
    free(p);
    totalProcesses--;
}


// NOTE: Following two functions pulled from K&R's The C Programming Lanugage
/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

/* reverse:  reverse string s in place */
void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}  
