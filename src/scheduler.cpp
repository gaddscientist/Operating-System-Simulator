#include <algorithm>
#include "process.h"
#include "scheduler.h"

Scheduler::Scheduler() {
    this->newQueue = std::deque<PCB>();
    this->readyQueue = std::deque<PCB>();
    this->keyboardWaitingQueue = std::map<int, PCB>();
    this->monitorWaitingQueue = std::map<int, PCB>();
    this->diskWaitingQueue = std::map<int, PCB>();
    this->terminatedQueue = std::deque<PCB>();
}

// Getters
std::deque<PCB>& Scheduler::getNewQueue() {
    return this->newQueue;
}

std::deque<PCB>& Scheduler::getReadyQueue() {
    return this->readyQueue;
}

std::map<int, PCB>& Scheduler::getKeyboardWaitingQueue() {
    return this->keyboardWaitingQueue;
}

std::map<int, PCB>& Scheduler::getMonitorWaitingQueue() {
    return this->monitorWaitingQueue;
}

std::map<int, PCB>& Scheduler::getDiskWaitingQueue() {
    return this->diskWaitingQueue;
}

std::deque<PCB>& Scheduler::getTerminatedQueue() {
    return this->terminatedQueue;
}

schedulerType Scheduler::getChosenScheduler() {
    return this->chosenScheduler;
}

// Setters
void Scheduler::setSchedulerType(schedulerType st) {
    this->chosenScheduler = st;
}

// Member functions
// Sorts processes in ready queue by their total run times
void Scheduler::sortReadyProcesses() {
    std::sort(this->readyQueue.begin(), this->readyQueue.end(), [](PCB a, PCB b){ return a.getBurst() < b.getBurst(); });
}
