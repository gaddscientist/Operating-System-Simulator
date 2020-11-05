#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "pcb.h"

// Counting semaphore
class Semaphore {
public:
    std::queue<std::thread::id> blockedProcesses;

    Semaphore();

    void wait();
    void signal();

private:
    int count;
    std::mutex mutex;
    std::condition_variable cond;
};