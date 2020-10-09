#include "pcb.h"
#include "helpers.h"

// PCB constructor
PCB::PCB (int PID, state CurrentState, int ProgCount, int ReqMem, int Cycle, std::string templateFile){
    pid = PID;
    currentState = CurrentState;
    progCount = ProgCount;
    reqMem = ReqMem;
    cycle = Cycle;
    instructions = ParseTemplate(templateFile);
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

// Getters
int PCB::getPid() {
    return this->pid;
}

state PCB::getCurrentState() {
    return this->currentState;
}

int PCB::getProgCount() {
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


// Setters
void PCB::setPid(int pid) {
    this->pid = pid;
}

void PCB::setCurrentState(state currentState) {
    this->currentState = currentState;
}

void PCB::setProgCount(int progCount) {
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