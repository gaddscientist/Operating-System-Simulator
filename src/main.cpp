#include <iostream>
#include "os.h"

OS os;

// Driver function
int main(int argc, char *argv[]) {
    // Ensures correct sytax
    if (argc <= 2) {
        std::cout << ("Please specify a template and number of processes to be created") << std::endl;
        std::cout << ("Syntax: ./process template.txt number_of_processes") << std::endl;
        std::cout << ("Example: ./process web_browser.txt 7") << std::endl;
        exit(1);
    }

    const std::string tp = argv[1];   // User specified template
    // Might need to convert better for large numbers
    int np =  *argv[2] - '0';         // User specified number of processes to create

    // Uses current time to as seed for rand()
    srand(time(0));

    os.templateFile = tp;
    os.numProcesses = np;

    // Create os and start it
    // OS os(templateFile, numProcesses);
    os.start();

    extern int totalProcesses;  // Defined in process.cpp
    // std::cout << "Remaining Processes: " << totalProcesses << std::endl;
    return 0;
}
