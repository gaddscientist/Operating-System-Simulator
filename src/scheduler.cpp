#include <deque>
#include <algorithm>
#include "process.h"
#include "scheduler.h"
#include "pcb.h"

Scheduler::Scheduler() {
    // Note: For this iteration, we're assuming no memory constraint.
    // All procecsses will fit in ready queue
    this->newQueue = std::deque<PCB>();
    this->readyQueue = std::deque<PCB>();
    this->waitingQueue = std::deque<PCB>();
    this->terminatedQueue = std::deque<PCB>();
}

// Getters
std::deque<PCB> Scheduler::getNewQueue() {
    return this->newQueue;
}

std::deque<PCB> Scheduler::getReadyQueue() {
    return this->readyQueue;
}

std::deque<PCB> Scheduler::getWaitingQueue() {
    return this->waitingQueue;
}

std::deque<PCB> Scheduler::getTerminatedQueue() {
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
void Scheduler::sortReadyProcesses() {
    std::sort(this->readyQueue.begin(), this->readyQueue.end(), [](PCB a, PCB b){ return a.getBurst() < b.getBurst(); });
}

void Scheduler::sortWaitingProcesses() {
    std::sort(this->waitingQueue.begin(), this->waitingQueue.end(), [](PCB a, PCB b){ return a.getIO() < b.getIO(); });
}


void Scheduler::updateQueues() {
    updateWaitingQueue();
    updateReadyQueue();
}

void Scheduler::updateWaitingQueue() {
    // Move processes that are done waiting to back of ready queue
    while (waitingQueue.front().getIO() == 0) {
        // addProcessToReadyQueue(waitingQueue.front());
        waitingQueue.pop_front();
    }

    // Decrement the number of remaining io cycles for 
    // all other processes still waiting
    for (int i = 0; i < this->waitingQueue.size(); i++) {
        if (this->waitingQueue[i].getIO() > 0) {
            int tempIO = this->waitingQueue[i].getIO();
            this->waitingQueue[i].setIO(tempIO--);
        }
    }
}

void Scheduler::updateReadyQueue() {
    ;
}


void Scheduler::addProcessToReadyQueue(PCB p) {
    p.setCurrentState(READY);
    this->readyQueue.push_back(p);
    this->sortReadyProcesses();
}

void Scheduler::addProcessToWaitingQueue(PCB p) {
    p.setCurrentState(WAITING);
    this->waitingQueue.push_back(p);
    this->sortWaitingProcesses();
}

void Scheduler::addProcessToTerminatedQueue(PCB p) {
    p.setCurrentState(TERMINATED);
    this->terminatedQueue.push_back(p);
}
