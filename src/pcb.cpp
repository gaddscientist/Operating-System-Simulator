#include "pcb.h"
#include "helpers.h"

// PCB constructor
PCB::PCB (int PID, state CurrentState, int ProgCount, int ReqMem, int Cycle, int GivenCycles, std::string templateFile){
    pid = PID;
    currentState = CurrentState;
    progCount = ProgCount;
    reqMem = ReqMem;
    cycle = Cycle;
    givenCycles = GivenCycles;
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
    // burst = std::round((burst / this->pcb.instructions.size()));
    return (int)burst;
}
