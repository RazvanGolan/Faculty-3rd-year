#include "Lock.h"

Lock::Lock(std::mutex& m) : mutexPtr(m) {
    mutexPtr.lock();
    std::cout << "[Lock] Mutex locked." << std::endl;
}

Lock::~Lock() {
    mutexPtr.unlock();
    std::cout << "[Lock] Mutex unlocked." << std::endl;
}
