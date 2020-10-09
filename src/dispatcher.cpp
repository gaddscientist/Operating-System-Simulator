#include "dispatcher.h"

extern Scheduler scheduler;
extern CPU cpu;

Dispatcher::Dispatcher() {
}

// Updates the state of the process associated with this PCB
// void Dispatcher::UpdateState(PCB pcb, state newState) {
//     pcb.setCurrentState(newState);
// }

PCB Dispatcher::getPcbFromReady() {
    return scheduler.getReadyQueue().front();
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