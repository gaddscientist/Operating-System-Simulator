#include "dispatcher.h"

extern Scheduler scheduler;
extern CPU cpu;

Dispatcher::Dispatcher() {
}

// Updates the state of the process associated with this PCB
// void Dispatcher::UpdateState(PCB pcb, state newState) {
//     pcb.setCurrentState(newState);
// }

void GetPcbFromReady() {
    cpu.setPcb(*scheduler.getReadyQueue().begin());
}

void Dispatcher::addProcessToReadyQueue(PCB p) {
    scheduler.getReadyQueue().push_back(p);
    p.setCurrentState(READY);
    scheduler.sortReadyProcesses();
}

void Dispatcher::addProcessToWaitingQueue(PCB p) {
    scheduler.getWaitingQueue().push_back(p);
    p.setCurrentState(WAITING);
    scheduler.sortWaitingProcesses();
}