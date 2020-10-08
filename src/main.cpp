#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include "process.h"
#include "helpers.h"
#include <vector>
#include "scheduler.h"

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

    int x;
    std::cout << "What type of scheduler?\n1.SJF\n2.RR" << std::endl;
    std::cin >> x;
    auto st = static_cast<schedulerType>(x);

    // Create scheduler
    Scheduler scheduler(st);
    std::cout << scheduler.chosenScheduler << std::endl;

    // Uses current time to as seed for rand()
    srand(time(0));

    const std::string templateFile = argv[1];   // User specified template
    // Might need to convert better for large numbers
    int numProcesses =  *argv[2] - '0';         // User specified number of processes to create
    // std::vector<Process> processes;             // Vector of created processes 

    // Loop to create processes
    for (int index = 0; numProcesses > 0; numProcesses--, index++) {
        // Creates process and adds to scheduler's "new" queue
        Process newProcess(templateFile);
        scheduler.newQueue.push_back(newProcess);

        // Prints out PID and Instructions
        std::cout << "PID = " << scheduler.newQueue[index].pcb.pid << std::endl;
        std::cout << "Bust time = " << scheduler.newQueue[index].burstCycle << std::endl;
        std::cout << std::endl;
    }
    std::cout << "Sorted" << std::endl;
    scheduler.sortProcesses();
    int num = 5;
    for (int index = 0; num > 0; num--, index++) {
        // Prints out PID and Instructions
        std::cout << "PID = " << scheduler.newQueue[index].pcb.pid << std::endl;
        std::cout << "Bust time = " << scheduler.newQueue[index].burstCycle << std::endl;
        std::cout << std::endl;
    }

    // Process tempProcess(templateFile);
    // Process* processPtr = &tempProcess;
    // ParseTemplate(templateFile);
    // std::cout << tempProcess.burstCycle << std::endl;

    std::cout << totalProcesses << " processes were created" << std::endl;



    return 0;
}
