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
    scheduler.getTerminatedQueue().push_back(p);
    totalProcesses--;
}

// Function to sort ready queue by remaining time left
// Only needed for SJF scheduling
void Dispatcher::updateReadyQueue() {
    scheduler.sortReadyProcesses();
}