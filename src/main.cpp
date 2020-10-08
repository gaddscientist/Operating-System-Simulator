#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include "process.h"
#include "helpers.h"
#include <vector>

extern int totalProcesses;

// Driver function
int main(int argc, char *argv[]) {
    // Ensures correct sytax
    if (argc <= 2) {
        std::cout << ("Please specify a template and number of processes to be created") << std::endl;
        std::cout << ("Syntax: ./process template.txt number_of_processes") << std::endl;
        std::cout << ("Example: ./process web_browser.txt 7") << std::endl;
        exit(1);
    }

    // Uses current time to as seed for rand()
    srand(time(0));

    const std::string templateFile = argv[1];                   // User specified template
    int numProcesses =  *argv[2] - '0';         // User specified number of processes to create
    Process* processes[MAXPROCESSES];    // Array of processes to be created
    int index;                                  // Process index

    // Loop to create processes with randomized instruction cycles
    // for (index = 0; numProcesses > 0; numProcesses--, index++) {
    //     processes[index] = new Process();
    //     ParseTemplate(templateFile, processes[index]->pcb.instructions);
    //     // std::cout << ("PID=%d\n%s\n\n",processes[index]->pcb.pid, processes[index]->pcb.instructions);
    //     std::cout << "PID = " << processes[index]->pcb.pid << std::endl;
    //     for (int i = 0; i < processes[index]->pcb.instructions.size(); i++) {
    //         std::cout << processes[index]->pcb.instructions[i] << std::endl;
    //     }
    //     std::cout << std::endl;
    // }

    Process tempProcess;
    Process* processPtr = &tempProcess;
    ParseTemplate(templateFile, processPtr->pcb.instructions);
    tempProcess.calculateBurst();
    std::cout << tempProcess.calculateBurst() << std::endl;

    std::cout << totalProcesses << " processes were created" << std::endl;



    return 0;
}
