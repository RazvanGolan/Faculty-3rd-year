#ifndef PIZZA_HPP
#define PIZZA_HPP

#include <string>

namespace pizza {

/**
 * Pizza class demonstrating:
 * - Encapsulation (private members with public interface)
 * - Member initialization in constructor
 * - Heap allocation and deallocation in destructor
 * - Copy constructor (deep copy)
 * - Move constructor
 */
class Pizza 
{
private:
    // Encapsulated members
    std::string name_;
    int size_; 
    std::string* toppings_;  
    int toppingsCount_;     
    int toppingsCapacity_;   
    double price_;
    
public:
    // Default constructor with member initialization
    Pizza(const std::string& name = "Margherita", 
          int size = 12, 
          int toppingsCount = 0);
    
    // Destructor - releases heap memory
    ~Pizza();
    
    // Copy constructor - performs deep copy
    Pizza(const Pizza& other);
    
    // Move constructor - transfers ownership
    Pizza(Pizza&& other) noexcept;
    
    // Copy assignment operator (bonus)
    Pizza& operator=(const Pizza& other);
    
    // Move assignment operator (bonus)
    Pizza& operator=(Pizza&& other) noexcept;
    
public:
    // Public interface methods
    void addTopping(const std::string& topping);
    void displayInfo() const;
    void bake() const;
    void deliver() const;
    
    // Getters (encapsulation)
    std::string getName() const { return name_; }
    int getSize() const { return size_; }
    int getToppingsCount() const { return toppingsCount_; }
    double getPrice() const { return price_; }
    
private:
    // Private helper methods
    void calculatePrice();
};

}

#endif
