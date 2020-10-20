#include <fstream>
#include <deque>
#include "helpers.h"
#include "dispatcher.h"
#include "scheduler.h"
#include <iostream>

        // TESTING CODE
        // Prints out PID and Instructions
        // std::cout << "PID = " << newProcess.getPcb().getPid() << std::endl;
        // std::cout << "Burst time = " << newProcess.getPcb().getBurst() << std::endl;
        // std::cout << std::endl;

        // std::cout << "index: " << index << std::endl;
        // std::cout << "PID = " << scheduler.getReadyQueue()[index].getPid() << std::endl;
        // std::cout << "Burst time = " << scheduler.getReadyQueue()[index].getBurst() << std::endl;
        // std::cout << "Instruction type = " << scheduler.getReadyQueue()[index].getProgCount().instrType << std::endl;
        // std::cout << "Instruction size = " << scheduler.getReadyQueue()[index].getProgCount().remainingCycles << std::endl;
//     }
// }