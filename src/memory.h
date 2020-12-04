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
    // totalMemory can be changed to 10 to demonstrate when not all
    // processes can be loaded into main memory
    const int totalMemory = 4096; // Kilobytes
    // const int totalMemory = 10; // Kilobytes
    int remainingMemory;

};