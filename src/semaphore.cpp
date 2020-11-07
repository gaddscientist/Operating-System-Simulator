// #include "semaphore.h"

// Semaphore::Semaphore() {
//     count = 0;
//     blockedProcesses = std::queue<PCB>();
// }

// void Semaphore::wait() {
//     count--;
//     if (count < 0) {
//         blockedProcesses.push(std::this_thread::get_id());
//     }
// }

// void Semaphore::signal() {

// }