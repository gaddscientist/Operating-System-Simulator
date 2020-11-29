#include <iostream>
#include "dispatcher.h"
#include "memory.h"

Scheduler scheduler;
extern Memory memory;
extern int totalProcesses;

Dispatcher::Dispatcher() {
}

PCB Dispatcher::getPcbFromReady() {
    PCB pcb = scheduler.getReadyQueue().front();
    if(scheduler.getReadyQueue().size() > 0) {
        scheduler.getReadyQueue().pop_front();
    }
    return pcb;
}

void Dispatcher::addProcessToNewQueue(PCB& p) {
    if(memory.getRemainingMemory() >= p.getReqMem()) {
        addProcessToReadyQueue(p);
        memory.takeMemory(p.getReqMem());
    }
    else {
        scheduler.getNewQueue().push_back(p);
    }
}

void Dispatcher::addProcessToReadyQueue(PCB& p) {
    p.setCurrentState(READY);
    scheduler.getReadyQueue().push_back(p);
    // Needed for SJF scheduling
    if(scheduler.getChosenScheduler() == SJF) {
        scheduler.sortReadyProcesses(); 
    }
}

void Dispatcher::addCriticalToReadyQueue(PCB& p) {
    p.setCurrentState(READY);
    scheduler.getReadyQueue().push_front(p);
}

void Dispatcher::addProcessToWaitingQueue(PCB& p) {
    p.setCurrentState(WAITING);
    scheduler.getWaitingQueue()[p.getPid()] = p;
    // scheduler.sortWaitingProcesses();
}

void Dispatcher::addProcessToTerminatedQueue(PCB& p) {
    p.setCurrentState(TERMINATED);
    memory.returnMemory(p.getReqMem());
    killChildProcesses(p);
    scheduler.getTerminatedQueue().push_back(p);
    totalProcesses--;
    readyNewProcesses();
}

// Function to sort ready queue by remaining time left
// Only needed for SJF scheduling
void Dispatcher::updateReadyQueue() {
    scheduler.sortReadyProcesses();
}

// Function to loop through a given process's child processes and kill them
void Dispatcher::killChildProcesses(PCB& p) {
    // Number of child processes to be killed
    int numChildProcesses = p.getChildProcesses().size();

    // Loops through all child processes in vector
    for(int i = 0; i < numChildProcesses; i++) {
        int childPID = p.getChildProcesses()[i]->getPid();
        // For processes that are ready, find them in the ready queue
        if(p.getChildProcesses()[i]->getCurrentState() == READY) {
            // Checks the ready queue for the process index and removes it
            for (std::deque<PCB>::iterator it = scheduler.getReadyQueue().begin(); it != scheduler.getReadyQueue().end(); it++) {
                // If child process is found
                if((*it).getPid() == p.getChildProcesses()[i]->getPid()) {
                    // Murder
                    scheduler.getReadyQueue().erase(it);
                    totalProcesses--;
                    // Free's the child processes memory
                    memory.returnMemory(p.getChildProcesses()[i]->getReqMem());
                    break;
                }
            }
        }
        // If child process has a state of waiting, could be in waiting queue
        // or could be blocked while IO cycles execute
        else if(p.getChildProcesses()[i]->getCurrentState() == WAITING) {
            // Iterator to index in waiting queue
            std::map<int, PCB>::iterator it = scheduler.getWaitingQueue().find(p.getChildProcesses()[i]->getPid());
            // If the process is found in waiting queue
            if(it != scheduler.getWaitingQueue().end()) {
                // Murder
                scheduler.getWaitingQueue().erase(it);
                totalProcesses--;
                // Free's the child processes memory
                memory.returnMemory(p.getChildProcesses()[i]->getReqMem());
            }
        }
        // For when memory is implemented
        else if(p.getChildProcesses()[i]->getCurrentState() == NEW) {
            // Checks the new queue for the process index and removes it
            for (std::deque<PCB>::iterator it = scheduler.getNewQueue().begin(); it != scheduler.getNewQueue().end(); it++) {
                // If child process is found
                if((*it).getPid() == p.getChildProcesses()[i]->getPid()) {
                    // Murder
                    scheduler.getNewQueue().erase(it);
                    totalProcesses--;
                    break;
                }
            }
        }

        // Regardless, set the child processes state to terminated and add it to terminated queue
        p.getChildProcesses()[i]->setCurrentState(TERMINATED);
        scheduler.getTerminatedQueue().push_back(*(p.getChildProcesses()[i]));

        std::cout << "Child Process with pid: " << childPID << " terminating early" << std::endl;

        // Remove process from parents list of child processes
        std::vector<PCB*>::iterator it = p.getChildProcesses().begin();
        p.getChildProcesses().erase(it + i);
    }
}

// Adds NEW processes to the ready queue while memory permits
// Pulls from new queue in strict FIFO manner
// Could be changed to first process small enough to fit in main memory
void Dispatcher::readyNewProcesses() {
    while((!scheduler.getNewQueue().empty()) && scheduler.getNewQueue().front().getReqMem() < memory.getRemainingMemory()) {
        addProcessToReadyQueue(scheduler.getNewQueue().front());
        memory.takeMemory(scheduler.getNewQueue().front().getReqMem());
        scheduler.getNewQueue().pop_front();
    }
}