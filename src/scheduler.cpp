#include <vector>
#include <algorithm>
#include "process.h"
#include "scheduler.h"

Scheduler::Scheduler(schedulerType st) {
    chosenScheduler = st;
    this->newQueue = std::vector<Process>();
    this->readyQueue = std::vector<Process>();
    this->waitingQueue = std::vector<Process>();
    this->terminatedQueue = std::vector<Process>();
}

void Scheduler::sortProcesses() {
    std::sort(this->newQueue.begin(), this->newQueue.end());
}