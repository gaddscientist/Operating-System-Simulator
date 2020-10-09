#include "cpu.h"
#include "scheduler.h"

extern Scheduler scheduler;

CPU::CPU() {
    clock = 0;
}

// On every cpu cycle
void CPU::clockTick() {
    scheduler.updateQueues();

    this->execute();

    this->clock++;
}

void CPU::execute() {
    // if (this->pcb.getProgCount())
}


// Getters
int CPU::getClock() {
    return this->clock;
}

PCB CPU::getPcb() {
    return this->pcb;
}

// Setters
void CPU::setClock(int clock) {
    this->clock = clock;
}

void CPU::setPcb(PCB pcb) {
    this->pcb = pcb;
}