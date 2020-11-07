#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "pcb.h"

// Counting semaphore
class Semaphore {
public:
    std::queue<PCB> blockedProcesses;

    Semaphore();

    void wait();
    void signal();

    int count;
    std::mutex mutex;
    std::condition_variable cond;
};