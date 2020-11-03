#include <iostream>
// #include <string>
// #include <stdio.h>
// #include <time.h>
// #include "process.h"
#include "scheduler.h"
// #include "cpu.h"
#include "dispatcher.h"
#include "OS.h"

// Global variables
// Scheduler scheduler;
// CPU cpu;
// Dispatcher dispatcher;

// Driver function
int main(int argc, char *argv[]) {
    // Ensures correct sytax
    if (argc <= 2) {
        std::cout << ("Please specify a template and number of processes to be created") << std::endl;
        std::cout << ("Syntax: ./process template.txt number_of_processes") << std::endl;
        std::cout << ("Example: ./process web_browser.txt 7") << std::endl;
        exit(1);
    }

    const std::string templateFile = argv[1];   // User specified template
    // Might need to convert better for large numbers
    int numProcesses =  *argv[2] - '0';         // User specified number of processes to create

    // Uses current time to as seed for rand()
    srand(time(0));

    // CREATE OS OBJECT AND RUN IT
    OS os(templateFile, numProcesses);
    os.start();

    extern int totalProcesses;
    std::cout << totalProcesses << std::endl;
    return 0;
}
