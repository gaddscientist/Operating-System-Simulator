#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include "process.h"
#include "helpers.h"
#include "scheduler.h"
#include "cpu.h"
#include "dispatcher.h"

// Global variables
Scheduler scheduler;
CPU cpu;

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
    schedulerType st = static_cast<schedulerType>(x);

    // Create scheduler
    scheduler.setSchedulerType(st);
    std::cout << scheduler.getChosenScheduler() << std::endl;

    // Create Dispatcher
    Dispatcher dispatcher;

    // Uses current time to as seed for rand()
    srand(time(0));

    const std::string templateFile = argv[1];   // User specified template
    // Might need to convert better for large numbers
    int numProcesses =  *argv[2] - '0';         // User specified number of processes to create
    // std::deque<Process> processes;             // deque of created processes 

    // Function to create processes
    createProcesses(numProcesses, templateFile);




    // TESTING
    std::cout << std::endl;
    int num = 5;
    for (int index = 0; num > 0; num--, index++) {
        // Prints out PID and Instructions
        std::cout << "PID = " << scheduler.getReadyQueue()[index].getPid() << std::endl;
        std::cout << "Burst time = " << scheduler.getReadyQueue()[index].getBurst() << std::endl;
        std::cout << "Instruction type = " << scheduler.getReadyQueue()[index].getProgCount().type << std::endl;
        std::cout << "Instruction size = " << scheduler.getReadyQueue()[index].getProgCount().remainingCycles << std::endl;
    }

    extern int totalProcesses;
    std::cout << totalProcesses << " processes were created" << std::endl;
    // END TESTING


    return 0;
}
