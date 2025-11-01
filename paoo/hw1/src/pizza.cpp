#include <pizza/pizza.hpp>
#include <iostream>
#include <iomanip>

namespace pizza {

// Constructor with member initialization list
Pizza::Pizza(const std::string& name, int size, int toppingsCount)
    : name_(name)           
    , size_(size)           
    , toppings_(nullptr)    
    , toppingsCount_(0)     
    , toppingsCapacity_(toppingsCount)
    , price_(0.0)           
{
    std::cout << "[Constructor] Creating pizza: " << name_ 
              << " (size: " << size_ << "\"" << ")" << std::endl;
    
    // Allocate heap memory for toppings array
    if (toppingsCapacity_ > 0) {
        toppings_ = new std::string[toppingsCapacity_];
        std::cout << "[Constructor] Allocated heap memory for " 
                  << toppingsCapacity_ << " toppings" << std::endl;
    }
    
    calculatePrice();
}

// Destructor - releases heap memory
Pizza::~Pizza()
{
    std::cout << "[Destructor] Destroying pizza: " << name_;
    
    if (toppings_ != nullptr) {
        std::cout << " - Releasing heap memory (capacity: " 
                  << toppingsCapacity_ << ", used: " << toppingsCount_ << ")";
        delete[] toppings_;
        toppings_ = nullptr;
    }
    
    std::cout << std::endl;
}

// Copy constructor - deep copy
Pizza::Pizza(const Pizza& other)
    : name_(other.name_)
    , size_(other.size_)
    , toppings_(nullptr)
    , toppingsCount_(other.toppingsCount_)
    , toppingsCapacity_(other.toppingsCapacity_)
    , price_(other.price_)
{
    std::cout << "[Copy Constructor] Creating deep copy of pizza: " 
              << name_ << std::endl;
    
    // Deep copy: allocate new heap memory and copy contents
    if (other.toppings_ != nullptr && other.toppingsCapacity_ > 0) {
        toppings_ = new std::string[toppingsCapacity_];
        
        for (int i = 0; i < toppingsCount_; ++i) {
            toppings_[i] = other.toppings_[i];
        }
        
        std::cout << "[Copy Constructor] Deep copied " 
                  << toppingsCount_ << " toppings (capacity: " 
                  << toppingsCapacity_ << ") to new heap memory" 
                  << std::endl;
    }
}

// Move constructor - transfers ownership
// This is EFFICIENT for temporary objects and prevents unnecessary copying
Pizza::Pizza(Pizza&& other) noexcept
    : name_(std::move(other.name_))
    , size_(other.size_)
    , toppings_(other.toppings_)  // Transfer ownership
    , toppingsCount_(other.toppingsCount_)
    , toppingsCapacity_(other.toppingsCapacity_)
    , price_(other.price_)
{
    std::cout << "[Move Constructor] Moving pizza: " << name_ 
              << " (transferring ownership of heap memory)" << std::endl;
    
    // Leave the source object in a valid state
    other.toppings_ = nullptr;
    other.toppingsCount_ = 0;
    other.toppingsCapacity_ = 0;
    other.size_ = 0;
    other.price_ = 0.0;
}

// Copy assignment operator
Pizza& Pizza::operator=(const Pizza& other)
{
    std::cout << "[Copy Assignment] Assigning pizza: " << other.name_ 
              << " to " << name_ << std::endl;
    
    if (this != &other) {
        // Release existing resources
        delete[] toppings_;
        
        // Copy data
        name_ = other.name_;
        size_ = other.size_;
        toppingsCount_ = other.toppingsCount_;
        toppingsCapacity_ = other.toppingsCapacity_;
        price_ = other.price_;
        
        // Deep copy toppings
        if (other.toppings_ != nullptr && other.toppingsCapacity_ > 0) {
            toppings_ = new std::string[toppingsCapacity_];
            for (int i = 0; i < toppingsCount_; ++i) {
                toppings_[i] = other.toppings_[i];
            }
        } else {
            toppings_ = nullptr;
        }
    }
    
    return *this;
}

// Move assignment operator
Pizza& Pizza::operator=(Pizza&& other) noexcept
{
    std::cout << "[Move Assignment] Moving pizza: " << other.name_ 
              << " to " << name_ << std::endl;
    
    if (this != &other) {
        // Release existing resources
        delete[] toppings_;
        
        // Transfer ownership
        name_ = std::move(other.name_);
        size_ = other.size_;
        toppings_ = other.toppings_;
        toppingsCount_ = other.toppingsCount_;
        toppingsCapacity_ = other.toppingsCapacity_;
        price_ = other.price_;
        
        // Leave source in valid state
        other.toppings_ = nullptr;
        other.toppingsCount_ = 0;
        other.toppingsCapacity_ = 0;
        other.size_ = 0;
        other.price_ = 0.0;
    }
    
    return *this;
}

void Pizza::addTopping(const std::string& topping)
{
    // Check if we have pre-allocated space available
    if (toppingsCount_ < toppingsCapacity_) {
        // Use existing allocated slot
        toppings_[toppingsCount_] = topping;
        toppingsCount_++;
        std::cout << "Added topping: " << topping << " to " << name_ 
                  << " (using pre-allocated slot " << toppingsCount_ 
                  << "/" << toppingsCapacity_ << ")" << std::endl;
    } else {
        // Need to reallocate - grow capacity
        int newCapacity = toppingsCapacity_ + 1;
        std::string* newToppings = new std::string[newCapacity];
        
        // Copy existing toppings
        for (int i = 0; i < toppingsCount_; ++i) {
            newToppings[i] = toppings_[i];
        }
        
        // Add new topping
        newToppings[toppingsCount_] = topping;
        
        // Release old array
        delete[] toppings_;
        
        // Update pointer, count, and capacity
        toppings_ = newToppings;
        toppingsCount_++;
        toppingsCapacity_ = newCapacity;
        
        std::cout << "Added topping: " << topping << " to " << name_ 
                  << " (reallocated heap memory, new capacity: " 
                  << toppingsCapacity_ << ")" << std::endl;
    }
    
    calculatePrice();
}

void Pizza::displayInfo() const
{
    std::cout << "\n===================================" << std::endl;
    std::cout << "Pizza: " << name_ << std::endl;
    std::cout << "Size: " << size_ << " inches" << std::endl;
    std::cout << "Toppings (" << toppingsCount_ << "): ";
    
    if (toppingsCount_ == 0) {
        std::cout << "None (plain)";
    } else {
        for (int i = 0; i < toppingsCount_; ++i) {
            std::cout << toppings_[i];
            if (i < toppingsCount_ - 1) std::cout << ", ";
        }
    }
    
    std::cout << std::endl;
    std::cout << "Price: $" << std::fixed << std::setprecision(2) 
              << price_ << std::endl;
    std::cout << "===================================" << std::endl;
}

void Pizza::bake() const
{
    std::cout << "Baking " << name_ << " pizza in the oven..." << std::endl;
}

void Pizza::deliver() const
{
    std::cout << "Delivering " << name_ << " pizza to customer!" << std::endl;
}

void Pizza::calculatePrice()
{
    // Base price based on size
    price_ = 5.0 + (size_ * 0.5);
    
    // Add $1.5 per topping
    price_ += toppingsCount_ * 1.5;
}

}
