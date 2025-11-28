#include <iostream>
#include <memory> // For std::unique_ptr (Item 13)
#include <vector>
#include <thread>
#include <mutex>
#include "Resource.h"
#include "Lock.h"

// Global shared resource for Item 14
int sharedCounter = 0;
std::mutex counterMutex;

// Function to demonstrate Item 13
void demonstrateItem13() {
    std::cout << "\n=== Item 13: Use objects to manage resources ===" << std::endl;
    
    // Without RAII, if we returned early or threw an exception, we might leak.
    // With std::unique_ptr, the resource is automatically released.
    std::cout << "Creating Resource with std::unique_ptr..." << std::endl;
    
    // std::make_unique is C++14, so we use constructor for C++11 compatibility if needed,
    // but C++11 supports unique_ptr.
    std::unique_ptr<Resource> res(new Resource("MyManagedResource"));
    
    res->use();
    
    std::cout << "End of demonstrateItem13 scope. Resource should be released now." << std::endl;
} // res is destroyed here, automatically releasing the resource

// Worker function for Item 14
void worker(int id) {
    // Item 14: We use our Lock object to manage the mutex.
    // Upon construction, it locks. Upon destruction (end of scope), it unlocks.
    // We have disabled copying for Lock to prevent incorrect behavior.
    Lock l(counterMutex); 
    
    std::cout << "Thread " << id << " entered critical section." << std::endl;
    
    // Simulate some work
    int temp = sharedCounter;
    temp++;
    // Small delay to increase chance of race condition if lock wasn't working
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    sharedCounter = temp;
    
    std::cout << "Thread " << id << " leaving critical section. Counter: " << sharedCounter << std::endl;
} // l is destroyed here, unlocking the mutex

void demonstrateItem14() {
    std::cout << "\n=== Item 14: Think carefully about copying behavior in resource-managing classes ===" << std::endl;
    std::cout << "Spawning threads to increment shared counter..." << std::endl;

    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.push_back(std::thread(worker, i));
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final Counter Value: " << sharedCounter << " (Expected: 5)" << std::endl;
}

int main() {
    demonstrateItem13();
    demonstrateItem14();
    return 0;
}
