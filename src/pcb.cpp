#include "pcb.h"
#include "helpers.h"
#include <string.h>

// delete this when done testing
#include <iostream>

// PCB constructor
PCB::PCB (int PID, state CurrentState, int ReqMem, std::string templateFile){
    pid = PID;
    currentState = CurrentState;
    reqMem = ReqMem;
    instructions = ParseTemplate(templateFile);
    progCount = {0, getInstructionType(0), getInstructionSize(0)};
    burst = calculateBurst();
    io = 0;
}

int PCB::calculateBurst() {
    double burst = 0; 
    std::string::size_type sz;
    for (int i = 0; i < this->instructions.size(); i++) {
        int instrSize = std::stoi(this->instructions[i].substr(this->instructions[i].find(' ')), &sz);
        burst += instrSize;
    }

    return (int)burst;
}


void PCB::decrementCycles() {
    this->progCount.remainingCycles--;
}

// Getters
int PCB::getPid() {
    return this->pid;
}

state PCB::getCurrentState() {
    return this->currentState;
}

programCounter PCB::getProgCount() {
    return this->progCount;
}

int PCB::getReqMem() {
    return this->reqMem;
}

int PCB::getCycle() {
    return this->cycle;
}

std::deque<int> PCB::getCpuRegisters() {
    return this->cpuRegisters;
}

std::deque<std::string> PCB::getInstructions() {
    return this->instructions;
}

int PCB::getBurst() {
    return this->burst;
}

int PCB::getIO() {
    return this->io;
}

instructionType PCB::getInstructionType(int lineNum) {
    int space = (int)this->instructions[lineNum].find(' '); // Index before cycles
    std::string tempStr = this->instructions[lineNum].substr(0, space);
    const char * str = tempStr.c_str();
    if (strcmp(str, "CALCULATE") == 0) {
        return CALCULATE;
    }
    else if (strcmp(str, "IO") == 0) {
        return IO;
    }
}

int PCB::getInstructionSize(int lineNum) {
    int space = (int)this->instructions[lineNum].find(' '); // Index before cycles
    std::string tempStr = this->instructions[lineNum].substr(space);
    std::string::size_type sz;           // Size of string
    return std::stoi(tempStr, &sz);
}


// Setters
void PCB::setPid(int pid) {
    this->pid = pid;
}

void PCB::setCurrentState(state currentState) {
    this->currentState = currentState;
}

void PCB::setProgCount(programCounter progCount) {
    this->progCount = progCount;
}

void PCB::setReqMem(int reqMem) {
    this->reqMem = reqMem;
}

void PCB::setCycle(int cycle) {
    this->cycle = cycle;
}

void PCB::setCpuRegisters(std::deque<int> cpuRegisters) {
    this->cpuRegisters = cpuRegisters;
}

void PCB::setInstructions(std::deque<std::string> instructions) {
    this->instructions = instructions;
}

void PCB::setBurst(int burst) {
    this->burst = burst;
}

void PCB::setIO(int io) {
    this->io = io;
}