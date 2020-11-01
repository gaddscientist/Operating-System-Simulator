#include <string>
#include <iostream>
#include "OS.h"
#include "scheduler.h"
#include "dispatcher.h"
#include "cpu.h"
#include "process.h"
#include "pcb.h"

// // Global objects
Dispatcher dispatcher;
extern Scheduler scheduler;

OS::OS(std::string tp, int num) {
    templateFile = tp;
    numProcesses = num;
}

void OS::start() {
    createProcesses(templateFile, numProcesses);

    extern int totalProcesses;
    std::cout << totalProcesses << " processes were created" << std::endl;

    int x;
    std::cout << "What type of scheduler?\n1.SJF\n2.RR" << std::endl;
    // std::cin >> x;
    x = 1;

    schedulerType st = static_cast<schedulerType>(x);

    // Create scheduler
    scheduler.setSchedulerType(st);
    std::cout << scheduler.getChosenScheduler() << std::endl;

    CPU cpu;
    while(totalProcesses > 0) {
            cpu.clockTick();
    }
}

void OS::createProcesses(std::string tp, int num) {
    extern Scheduler scheduler;
    for (int index = 0; num> 0; num--, index++) {
        // Creates process and adds to scheduler's "new" queue
        Process newProcess(tp);
        std::cout << "Process created with PID: " << newProcess.getPid() << std::endl;
        for(int z = 0; z < newProcess.getPcb().getInstructionsList().size(); z++) {
            std::cout << newProcess.getPcb().getInstructionsList()[z].instrType << " " << newProcess.getPcb().getInstructionsList()[z].remainingCycles << std::endl;
        }
        std::cout << "Burst: " << newProcess.getPcb().getBurst() << std::endl;
        scheduler.addProcessToReadyQueue(newProcess.getPcb());
    }
}