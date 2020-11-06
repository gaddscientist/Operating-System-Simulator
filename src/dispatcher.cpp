#include "dispatcher.h"

Scheduler scheduler;
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

void Dispatcher::addProcessToReadyQueue(PCB p) {
    p.setCurrentState(READY);
    scheduler.getReadyQueue().push_back(p);
    // Needed for SJF scheduling
    if(scheduler.getChosenScheduler() == SJF) {
        scheduler.sortReadyProcesses(); 
    }
}

void Dispatcher::addProcessToWaitingQueue(PCB& p) {
    p.setCurrentState(WAITING);
    scheduler.getWaitingQueue()[p.getPid()] = p;
    // scheduler.sortWaitingProcesses();
}

void Dispatcher::addProcessToTerminatedQueue(PCB& p) {
    p.setCurrentState(TERMINATED);
    killChildProcesses(p);
    scheduler.getTerminatedQueue().push_back(p);
    totalProcesses--;
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
        // For processes that are ready, find them in the ready queue
        if(p.getChildProcesses()[i]->getCurrentState() == READY) {
            // Iterator to beginning of ready queue
            std::deque<PCB>::iterator it = scheduler.getReadyQueue().begin();

            // Checks the ready queue for the process index and removes it
            for (; it != scheduler.getReadyQueue().end(); it++) {
                // If child process is found
                if((*it).getPid() == p.getChildProcesses()[i]->getPid()) {
                    // Murder
                    scheduler.getReadyQueue().erase(it);
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
            }
        }
        // For when memory is implemented
        else if(p.getChildProcesses()[i]->getCurrentState() == NEW) {
            // Do something when memory is implemented
        }

        // Regardless, set the child processes state to terminated and add it to terminated queue
        p.getChildProcesses()[i]->setCurrentState(TERMINATED);
        scheduler.getTerminatedQueue().push_back(*(p.getChildProcesses()[i]));
        // Remove process from parents list of child processes
        std::vector<PCB*>::iterator it = p.getChildProcesses().begin();
        p.getChildProcesses().erase(it + i);
    }
}