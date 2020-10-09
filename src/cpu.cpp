#include "cpu.h"
#include "scheduler.h"

extern Scheduler scheduler;

CPU::CPU() {
    clock = 0;
}

// On every cpu cycle
void CPU::clockTick() {
    this->clock++;

    scheduler.updateQueues();
}