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
// Takes in the parent process's PCB to fork from
PCB* OS::fork(PCB& p) {
    // Creates a new randomized process
    Process newProcess(templateFile);

    // Gets new processes PCB to manipulate
    PCB childPCB = *(newProcess.getPcb());
    // Gets position of FORK instruction to be removed
    int forkInstrNum = p.getProgCount();

    // Removes FORK instruction from the child processes instructions
    childPCB.getInstructionsList().erase(childPCB.getInstructionsList().begin() + forkInstrNum);
    childPCB.getInstructionsRemaining().erase(childPCB.getInstructionsRemaining().begin() + forkInstrNum);

    // Adds child process to pool of ready processes
    dispatcher.addProcessToReadyQueue(childPCB);

    // Adds new process to total job list
    jobList[newProcess.getPid()] = *(newProcess.getPcb());

    // Returns reference to newly created process's PCB
    return newProcess.getPcb();

    // Adds child process pcb to parents list of children
    // p.getChildProcesses().push_back(*(newProcess.getPcb()));

}