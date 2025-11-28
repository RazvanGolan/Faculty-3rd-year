#ifndef LOCK_H
#define LOCK_H

#include <mutex>
#include <iostream>

// Item 14: Think carefully about copying behavior in resource-managing classes.
// This Lock class manages a mutex. Copying a lock object doesn't usually make sense
// (what does it mean to copy a lock? lock it twice? share the lock?).
// Therefore, we PROHIBIT copying.

class Lock {
public:
    explicit Lock(std::mutex& m);
    ~Lock();

    // Delete copy constructor and assignment operator to prevent copying
    Lock(const Lock&) = delete;
    Lock& operator=(const Lock&) = delete;

private:
    std::mutex& mutexPtr;
};

#endif // LOCK_H
