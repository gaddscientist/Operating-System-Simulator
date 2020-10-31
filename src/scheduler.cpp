#include <deque>
#include <algorithm>
#include "process.h"
#include "scheduler.h"
#include "pcb.h"

// testing
#include <iostream>

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

// Tells queues to update order if needed
void Scheduler::updateQueues() {
    updateWaitingQueue();
    updateReadyQueue();
}

void Scheduler::updateWaitingQueue() {
    // Move processes that are done waiting to back of ready queue
    if (!(this->waitingQueue.empty())) {
        while (this->waitingQueue.front().getIO() == 0 && this->waitingQueue.size() > 0) {
            // std::cout << "TEST BEFORE" << std::endl;
            // std::cout << "waiting queue size " << this->waitingQueue.size() << std::endl;
            // this->waitingQueue.front().incrementInstrNum();
            this->addProcessToReadyQueue(this->waitingQueue.front());
            this->waitingQueue.pop_front();
        }
    }

    // Decrement the number of remaining io cycles for 
    // all other processes still waiting
    for (int i = 0; i < this->waitingQueue.size(); i++) {
        if (this->waitingQueue[i].getIO() > 0) {
            int tempIO = this->waitingQueue[i].getIO();
            this->waitingQueue[i].setIO(--tempIO);
            // std::cout << "IO after: " << this->waitingQueue[i].getIO() << std::endl;
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
    this->readyQueue.pop_front();
    this->sortWaitingProcesses();
}

void Scheduler::addProcessToTerminatedQueue(PCB p) {
    p.setCurrentState(TERMINATED);
    this->terminatedQueue.push_back(p);
}
