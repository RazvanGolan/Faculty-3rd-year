#include <pizza/pizza.hpp>
#include <iostream>
#include <vector>

using namespace pizza;

// Helper function to demonstrate copy constructor issue
Pizza createPizzaWithoutCopyConstructor()
{
    Pizza temp("Pepperoni", 14, 2);
    temp.addTopping("Pepperoni");
    temp.addTopping("Mozzarella");
    return temp;  // Without copy/move constructor, this would cause issues
}

// Helper function to demonstrate move constructor
Pizza createPizzaForMove()
{
    Pizza temp("Hawaiian", 16, 2);
    temp.addTopping("Ham");
    temp.addTopping("Pineapple");
    return temp;  // Move constructor is called here 
}

int main()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << "   PIZZA APPLICATION - OOP CONCEPTS DEMO" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    // ==================================================================
    // 1. ENCAPSULATION DEMO
    // ==================================================================
    std::cout << "\n--- 1. ENCAPSULATION DEMONSTRATION ---\n" << std::endl;
    std::cout << "Creating pizza with private members accessed via public interface\n" 
              << std::endl;
    
    Pizza margherita("Margherita", 12, 2);
    margherita.addTopping("Tomato Sauce");
    margherita.addTopping("Mozzarella");
    
    // Can't access private members directly: margherita.price_ = 100.0; // ERROR!
    // Instead, we use public getters
    std::cout << "\nAccessing encapsulated data through getters:" << std::endl;
    std::cout << "  Name: " << margherita.getName() << std::endl;
    std::cout << "  Size: " << margherita.getSize() << " inches" << std::endl;
    std::cout << "  Toppings Count: " << margherita.getToppingsCount() << std::endl;
    
    margherita.displayInfo();
    
    // ==================================================================
    // 2. MEMBER INITIALIZATION IN CONSTRUCTOR
    // ==================================================================
    std::cout << "\n--- 2. MEMBER INITIALIZATION DEMONSTRATION ---\n" << std::endl;
    std::cout << "Members are initialized in constructor initialization list\n" 
              << std::endl;
    
    Pizza quattroStagioni("Quattro Stagioni", 14, 4);
    std::cout << "All members initialized before constructor body executes" 
              << std::endl;
    
    // ==================================================================
    // 3. HEAP ALLOCATION AND DESTRUCTOR
    // ==================================================================
    std::cout << "\n--- 3. HEAP MEMORY MANAGEMENT DEMONSTRATION ---\n" << std::endl;
    std::cout << "Creating pizza in a local scope to demonstrate destructor\n" 
              << std::endl;
              
    {
        Pizza veggie("Veggie Supreme", 12, 3);
        veggie.addTopping("Mushrooms");
        veggie.addTopping("Bell Peppers");
        veggie.addTopping("Olives");
        veggie.displayInfo();
        std::cout << "\nExiting scope - destructor will be called..." << std::endl;
    }  // Destructor called here, releasing heap memory
    
    std::cout << "\nScope exited - heap memory was released!\n" << std::endl;
    
    // ==================================================================
    // 4. COPY CONSTRUCTOR DEMONSTRATION
    // ==================================================================
    std::cout << "\n--- 4. COPY CONSTRUCTOR DEMONSTRATION ---\n" << std::endl;
    std::cout << "WHY WE NEED IT: Without copy constructor, shallow copy causes:" 
              << std::endl;
    std::cout << "  - Double-free error (both objects delete same heap memory)" 
              << std::endl;
    std::cout << "  - Data corruption (changes in copy affect original)\n" 
              << std::endl;
    
    Pizza original("Meat Lovers", 16, 3);
    original.addTopping("Bacon");
    original.addTopping("Sausage");
    original.addTopping("Ham");
    
    std::cout << "\nCreating a copy of the pizza:" << std::endl;
    Pizza copy = original;  // Copy constructor called
    
    std::cout << "\nOriginal pizza:" << std::endl;
    original.displayInfo();
    
    std::cout << "\nCopied pizza (independent heap memory):" << std::endl;
    copy.displayInfo();
    
    std::cout << "\nAdding topping to copy only:" << std::endl;
    copy.addTopping("Pepperoni");
    
    std::cout << "\nOriginal (unchanged):" << std::endl;
    std::cout << "  Toppings: " << original.getToppingsCount() << std::endl;
    
    std::cout << "Copy (modified):" << std::endl;
    std::cout << "  Toppings: " << copy.getToppingsCount() << std::endl;
    
    // ==================================================================
    // 5. MOVE CONSTRUCTOR DEMONSTRATION
    // ==================================================================
    std::cout << "\n--- 5. MOVE CONSTRUCTOR DEMONSTRATION ---\n" << std::endl;
    std::cout << "WHY WE NEED IT: Move constructor is more efficient for temporary objects" 
              << std::endl;
    std::cout << "  - Avoids expensive deep copy operations" << std::endl;
    std::cout << "  - Transfers ownership of heap memory instead of copying\n" 
              << std::endl;
    
    std::cout << "\nCreating pizza via function return (move semantics):" 
              << std::endl;
    Pizza moved = createPizzaForMove();  // Move constructor may be called
    
    moved.displayInfo();
    
    std::cout << "\nUsing std::move explicitly:" << std::endl;
    Pizza bbqChicken("BBQ Chicken", 14, 3);
    bbqChicken.addTopping("BBQ Sauce");
    bbqChicken.addTopping("Chicken");
    bbqChicken.addTopping("Onions");
    
    Pizza transferred = std::move(bbqChicken);  // Move constructor called
    
    std::cout << "\nTransferred pizza:" << std::endl;
    transferred.displayInfo();
    
    // ==================================================================
    // 6. PRACTICAL EXAMPLE WITH VECTOR
    // ==================================================================
    std::cout << "\n--- 6. PRACTICAL USAGE WITH STL CONTAINERS ---\n" << std::endl;
    std::cout << "Copy and move constructors are essential for STL containers\n" 
              << std::endl;
    
    std::vector<Pizza> pizzaOrder;
    
    std::cout << "Adding pizzas to order (uses move constructor):" << std::endl;
    pizzaOrder.push_back(Pizza("Marinara", 10, 1));
    pizzaOrder.push_back(Pizza("Diavola", 12, 2));
    
    std::cout << "\nOrder summary:" << std::endl;
    for (size_t i = 0; i < pizzaOrder.size(); ++i) {
        std::cout << "\nPizza #" << (i + 1) << ":" << std::endl;
        pizzaOrder[i].displayInfo();
    }
    
    // ==================================================================
    // 7. ASSIGNMENT OPERATORS DEMO (COPY AND MOVE)
    // ==================================================================
    std::cout << "\n--- 7. ASSIGNMENT OPERATORS DEMONSTRATION ---\n" << std::endl;
    
    Pizza aAssign("Assignment A", 12, 2);
    aAssign.addTopping("Cheese");
    aAssign.addTopping("Basil");
    
    Pizza bAssign("Assignment B", 14, 1);
    bAssign.addTopping("Tomato");
    
    std::cout << "\nCopy-assign bAssign to aAssign (operator=(const Pizza&)):" << std::endl;
    aAssign = bAssign; // Triggers Copy Assignment
    aAssign.displayInfo();
    
    std::cout << "\nMove-assign temporary to aAssign (operator=(Pizza&&)):" << std::endl;
    aAssign = Pizza("Temp Assign", 10, 1); // Triggers Move Assignment from rvalue
    aAssign.addTopping("Oregano"); // May reallocate capacity by +1
    aAssign.displayInfo();
    
    bAssign.displayInfo();

    std::cout << "\nMove-assign bAssign to aAssign using std::move (operator=(Pizza&&)):" << std::endl;
    aAssign = std::move(bAssign); // Explicit move assignment
    aAssign.displayInfo();
    
    // ==================================================================
    // FINAL DEMONSTRATION
    // ==================================================================
    std::cout << "\n--- COMPLETE WORKFLOW DEMONSTRATION ---\n" << std::endl;
    
    Pizza finalPizza("Supreme Deluxe", 18, 5);
    finalPizza.addTopping("Pepperoni");
    finalPizza.addTopping("Sausage");
    finalPizza.addTopping("Mushrooms");
    finalPizza.addTopping("Onions");
    finalPizza.addTopping("Green Peppers");
    
    finalPizza.displayInfo();
    finalPizza.bake();
    finalPizza.deliver();
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "   DESTRUCTORS WILL NOW BE CALLED" << std::endl;
    std::cout << "   (Watch heap memory being released)" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    return 0;
}
