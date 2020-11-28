#include <iostream>
#include "memory.h"

Memory::Memory() {
    remainingMemory = totalMemory;
}

void Memory::takeMemory(int mem) {
    if(mem > remainingMemory) {
        std::cout << "Not enough memory remaining" << std::endl;
    }
    else {
        remainingMemory -= mem;
    }
}

void Memory::returnMemory(int mem) {
    if((remainingMemory + mem) > totalMemory) {
        std::cout << "Exceeding total memory" << std::endl;
    }
    else {
        remainingMemory += mem;
    }
}

int Memory::getTotalMemory() {
    return totalMemory;
}

int Memory::getRemainingMemory() {
    return remainingMemory;
}