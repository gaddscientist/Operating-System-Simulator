#pragma once
#include <string>

class OS {
public:
    // Constructor
    OS(std::string, int);

    // Starts up the OS
    void start();


private:
    std::string templateFile;
    int numProcesses;
    void createProcesses(std::string templateFile, int numProcesses);
};