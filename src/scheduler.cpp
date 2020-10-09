#include <vector>
#include <algorithm>
#include "process.h"
#include "scheduler.h"
#include "pcb.h"

Scheduler::Scheduler() {
    // Note: For this iteration, we're assuming no memory constraint.
    // All procecsses will fit in ready queue
    this->newQueue = std::vector<PCB>();
    this->readyQueue = std::vector<PCB>();
    this->waitingQueue = std::vector<PCB>();
    this->terminatedQueue = std::vector<PCB>();
}

void Scheduler::setSchedulerType(schedulerType st) {
    this->chosenScheduler = st;
}

void Scheduler::sortReadyProcesses() {
    std::sort(this->readyQueue.begin(), this->readyQueue.end(), [](PCB a, PCB b){ return a.burst < b.burst; });
}

void Scheduler::sortWaitingProcesses() {
    std::sort(this->waitingQueue.begin(), this->waitingQueue.end(), [](PCB a, PCB b){ return a.io < b.io; });
}

void Scheduler::addProcessToReadyQueue(PCB p) {
    this->readyQueue.push_back(p);
    this->sortReadyProcesses();
}

void Scheduler::addProcessToWaitingQueue(PCB p) {
    this->waitingQueue.push_back(p);
    this->sortWaitingProcesses();
}

void Scheduler::updateQueues() {
    updateWaitingQueue();
    updateReadyQueue();
}

void Scheduler::updateWaitingQueue() {
    while (waitingQueue.front().io == 0) {
        addProcessToReadyQueue(waitingQueue.front());
        waitingQueue.pop_front();
    }

    for (int i = 0; i < this->waitingQueue.size(); i++) {
        if (this->waitingQueue[i].io > 0) {
            this->waitingQueue[i].io--;
        }
        else if (this->waitingQueue[i].io == 0) {

        }
    }
}

void Scheduler::updateReadyQueue() {

}
