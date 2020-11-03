#include "dispatcher.h"

Scheduler scheduler;
extern int totalProcesses;

Dispatcher::Dispatcher() {
}

// Updates the state of the process associated with this PCB
// void Dispatcher::UpdateState(PCB pcb, state newState) {
//     pcb.setCurrentState(newState);
// }

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
    // scheduler.sortReadyProcesses();
}

void Dispatcher::addProcessToWaitingQueue(PCB p) {
    p.setCurrentState(WAITING);
    scheduler.getWaitingQueue()[p.getPid()] = p;
    // scheduler.sortWaitingProcesses();
}

void Dispatcher::addProcessToTerminatedQueue(PCB p) {
    p.setCurrentState(TERMINATED);
    scheduler.getTerminatedQueue().push_back(p);
}

void Dispatcher::updateQueues() {
    scheduler.updateReadyQueue();
    // scheduler.updateWaitingQueue();
}