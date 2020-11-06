#include <string>
#include <iostream>
#include "os.h"
#include "scheduler.h"
#include "dispatcher.h"
#include "cpu.h"
#include "process.h"
#include "pcb.h"

// // Global objects
Dispatcher dispatcher;
extern Scheduler scheduler; // Defined in dispatcher.cpp

OS::OS(std::string tp, int num) {
    templateFile = tp;
    numProcesses = num;
    this->jobList = std::map<int, PCB>();
}
OS::OS() {
    this->jobList = std::map<int, PCB>();
}

void OS::start() {

    // Creates processes from template file
    for (int i = numProcesses; i > 0; i--) {
        createProcess();
    }

    extern int totalProcesses;  // Defined in process.cpp
    std::cout << totalProcesses << " processes were created" << std::endl;

    int x;
    std::cout << "What type of scheduler?\n1.SJF\n2.RR" << std::endl;
    // std::cin >> x;
    x = 2;

    schedulerType st = static_cast<schedulerType>(x);

    // Create scheduler
    scheduler.setSchedulerType(st);
    std::cout << scheduler.getChosenScheduler() << std::endl;

    CPU cpu;
    std::cout << std::fixed << cpu.getClock() << " Operating system starting" << std::endl;
    // Until all processes have terminated
    while(totalProcesses > 0) {
        // Tell the cpu to execute the next ready process
        cpu.execute();
    }
    std::cout << std::fixed << cpu.getClock() << " Operating system ending" << std::endl;
}

void OS::createProcess() {
    extern Scheduler scheduler;
    // Creates process and adds to scheduler's "new" queue
    Process newProcess(templateFile);
    std::cout << "Process created with PID: " << newProcess.getPid() << std::endl;
    PCB tempPCB = *(newProcess.getPcb());
    // for(size_t z = 0; z < newProcess.getPcb().getInstructionsList().size(); z++) {
    //     std::cout << newProcess.getPcb().getInstructionsList()[z].instrType << " " << newProcess.getPcb().getInstructionsList()[z].remainingCycles << std::endl;
    // }
    // std::cout << "Burst: " << newProcess.getPcb().getBurst() << std::endl;
    for(size_t z = 0; z < tempPCB.getInstructionsList().size(); z++) {
        std::cout << tempPCB.getInstructionsList()[z].instrType << " " << tempPCB.getInstructionsList()[z].remainingCycles << std::endl;
    }
    std::cout << "Burst: " << tempPCB.getBurst() << std::endl;
    dispatcher.addProcessToReadyQueue(*(newProcess.getPcb()));
    // Adds newly created process to map of jobs where key, value = pid, pcb
    this->jobList[newProcess.getPid()] = *(newProcess.getPcb());
}



// Creates a child process
// Takes in the parent process's pid to fork from
void OS::fork(int pid) {
    // Creates a new randomized process
    Process newProcess(templateFile);

    PCB parentPCB = this->jobList[pid];
    PCB childPCB = *(newProcess.getPcb());
    int forkInstrNum = parentPCB.getProgCount();
    childPCB.getInstructionsList().erase(parentPCB.getInstructionsList().begin() + forkInstrNum);
    dispatcher.addProcessToReadyQueue(childPCB);


    // Gets position of FORK instruction to be removed
    // int forkInstrNum = newProcess.getPcb().getProgCount();
    // Removes FORK instruction from the child processes instructions
    // newProcess.getPcb().getInstructionsList().erase(newProcess.getPcb().getInstructionsList().begin() + forkInstrNum);

    // Adds child process to pool of ready processes
    // dispatcher.addProcessToReadyQueue(newProcess.getPcb());
    // Adds child process pid to parents list of children
    jobList[pid].getChildProcesses().push_back(newProcess.getPid());

}