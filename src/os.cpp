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
}

void OS::start() {

    // Creates processes from template file
    createProcesses(templateFile, numProcesses);

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

void OS::createProcesses(std::string tp, int num) {
    extern Scheduler scheduler;
    for (int index = 0; num> 0; num--, index++) {
        // Creates process and adds to scheduler's "new" queue
        Process newProcess(tp);
        std::cout << "Process created with PID: " << newProcess.getPid() << std::endl;
        for(size_t z = 0; z < newProcess.getPcb().getInstructionsList().size(); z++) {
            std::cout << newProcess.getPcb().getInstructionsList()[z].instrType << " " << newProcess.getPcb().getInstructionsList()[z].remainingCycles << std::endl;
        }
        std::cout << "Burst: " << newProcess.getPcb().getBurst() << std::endl;
        dispatcher.addProcessToReadyQueue(newProcess.getPcb());
    }
}