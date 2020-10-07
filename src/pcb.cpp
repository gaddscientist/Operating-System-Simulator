#include "pcb.h"

// PCB constructor
PCB::PCB (int PID, state CurrentState, int ProgCount, int ReqMem, int Cycle, int GivenCycles){
    pid = PID;
    currentState = CurrentState;
    progCount = ProgCount;
    reqMem = ReqMem;
    cycle = Cycle;
    givenCycles = GivenCycles;
}

// Updates the state of the process associated with this PCB
void PCB::UpdateState(PCB pcb, state newState) {
    pcb.currentState = newState;
}