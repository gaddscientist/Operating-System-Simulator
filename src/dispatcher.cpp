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

void Dispatcher::addProcessToKeyboardWaitingQueue(PCB& p) {
    p.setCurrentState(WAITING);
    scheduler.getKeyboardWaitingQueue()[p.getPid()] = p;
    // scheduler.sortWaitingProcesses();
}

void Dispatcher::addProcessToMonitorWaitingQueue(PCB& p) {
    p.setCurrentState(WAITING);
    scheduler.getMonitorWaitingQueue()[p.getPid()] = p;
    // scheduler.sortWaitingProcesses();
}

void Dispatcher::addProcessToDiskWaitingQueue(PCB& p) {
    p.setCurrentState(WAITING);
    scheduler.getDiskWaitingQueue()[p.getPid()] = p;
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

        // Checks the ready queue for the process index and removes it if found
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


        // Checks the waiting queues for the process index and removes it if found

        // Iterator to index in keyboard waiting queue
        std::map<int, PCB>::iterator itk = scheduler.getKeyboardWaitingQueue().find(p.getChildProcesses()[i]->getPid());
        // If the process is found in waiting queue
        if(itk != scheduler.getKeyboardWaitingQueue().end()) {
            // Murder
            scheduler.getKeyboardWaitingQueue().erase(itk);
            totalProcesses--;
            // Free's the child processes memory
            memory.returnMemory(p.getChildProcesses()[i]->getReqMem());
        }
        // Iterator to index in monitor waiting queue
        std::map<int, PCB>::iterator itm = scheduler.getMonitorWaitingQueue().find(p.getChildProcesses()[i]->getPid());
        // If the process is found in waiting queue
        if(itm != scheduler.getMonitorWaitingQueue().end()) {
            // Murder
            scheduler.getMonitorWaitingQueue().erase(itm);
            totalProcesses--;
            // Free's the child processes memory
            memory.returnMemory(p.getChildProcesses()[i]->getReqMem());
        }
        // Iterator to index in disk waiting queue
        std::map<int, PCB>::iterator itd = scheduler.getDiskWaitingQueue().find(p.getChildProcesses()[i]->getPid());
        // If the process is found in waiting queue
        if(itd != scheduler.getDiskWaitingQueue().end()) {
            // Murder
            scheduler.getDiskWaitingQueue().erase(itd);
            totalProcesses--;
            // Free's the child processes memory
            memory.returnMemory(p.getChildProcesses()[i]->getReqMem());
        }


        // Checks the new queue for the process index and removes it if found
        for (std::deque<PCB>::iterator it = scheduler.getNewQueue().begin(); it != scheduler.getNewQueue().end(); it++) {
            // If child process is found
            if((*it).getPid() == p.getChildProcesses()[i]->getPid()) {
                // Murder
                scheduler.getNewQueue().erase(it);
                totalProcesses--;
                break;
            }
        }


        // Regardless, set the child processes state to terminated and add it to terminated queue
        p.getChildProcesses()[i]->setCurrentState(TERMINATED);
        scheduler.getTerminatedQueue().push_back(*(p.getChildProcesses()[i]));

        std::cout << "Child Process with pid: " << childPID << " terminating early" << std::endl;

        // Remove process from parents list of child processes
        std::vector<PCB*>::iterator iter = p.getChildProcesses().begin();
        p.getChildProcesses().erase(iter + i);
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