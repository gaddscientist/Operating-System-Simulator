#include "dispatcher.h"

extern Scheduler scheduler;

Dispatcher::Dispatcher() {
}

// Updates the state of the process associated with this PCB
// void Dispatcher::UpdateState(PCB pcb, state newState) {
//     pcb.setCurrentState(newState);
// }

PCB Dispatcher::getPcbFromReady() {
    PCB pcb = scheduler.getReadyQueue().front();
    scheduler.getReadyQueue().pop_front();
    return pcb;
}

void Dispatcher::addProcessToReadyQueue(PCB p) {
    p.setCurrentState(READY);
    scheduler.getReadyQueue().push_back(p);
    scheduler.sortReadyProcesses();
}

void Dispatcher::addProcessToWaitingQueue(PCB p) {
    p.setCurrentState(WAITING);
    scheduler.getWaitingQueue().push_back(p);
    scheduler.sortWaitingProcesses();
}

void Dispatcher::updateQueues() {
    scheduler.updateReadyQueue();
    scheduler.updateWaitingQueue();
}