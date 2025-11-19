#include <iostream>
#include "Student.h"
#include "GradStudent.h"

int main() {
    std::cout << "=== Item 10: Have assignment operators return a reference to *this ===" << std::endl;
    Student s1("Alice", 90);
    Student s2("Bob", 80);
    Student s3("Charlie", 70);

    std::cout << "Initial states:" << std::endl;
    s1.print();
    s2.print();
    s3.print();

    std::cout << "Chained assignment (s1 = s2 = s3):" << std::endl;
    s1 = s2 = s3; // Item 10

    s1.print();
    s2.print();
    s3.print();

    std::cout << "\n=== Item 11: Handle assignment to self in operator= ===" << std::endl;
    std::cout << "Assigning s1 to s1:" << std::endl;
    s1 = s1; // Item 11
    s1.print();

    std::cout << "\n=== Item 12: Copy all parts of an object ===" << std::endl;
    GradStudent g1("Dave", 95, "AI Research");
    GradStudent g2("Eve", 85, "Cybersecurity");

    std::cout << "Initial GradStudents:" << std::endl;
    g1.print();
    g2.print();

    std::cout << "Assigning g1 = g2:" << std::endl;
    g1 = g2; // Item 12

    std::cout << "After assignment:" << std::endl;
    g1.print();
    g2.print();

    return 0;
}
