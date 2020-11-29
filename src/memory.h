#pragma once

// Class to simulate main memory
class Memory {
public:

    Memory();

    void takeMemory(int mem);
    void returnMemory(int mem);
    int getTotalMemory();
    int getRemainingMemory();

private:
    const int totalMemory = 10;//4096; // Kilobytes
    int remainingMemory;

};