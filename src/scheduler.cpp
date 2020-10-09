#include <vector>
#include <algorithm>
#include "process.h"
#include "scheduler.h"

Scheduler::Scheduler() {
    // Note: For this iteration, we're assuming no memory constraint.
    // All procecsses will fit in ready queue
    this->newQueue = std::vector<PCB>();
    this->readyQueue = std::vector<PCB>();
    this->waitingQueue = std::vector<PCB>();
    this->terminatedQueue = std::vector<PCB>();
}

void Scheduler::sortProcesses() {
    std::sort(this->readyQueue.begin(), this->readyQueue.end());
}

void Scheduler::setSchedulerType(schedulerType st) {
    this->chosenScheduler = st;
}

void Scheduler::addProcessToReadyQueue(PCB p) {
    this->readyQueue.push_back(p);
    this->sortProcesses();
}

void Scheduler::updateQueues() {

}