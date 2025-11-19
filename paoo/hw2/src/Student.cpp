#include "Student.h"

Student::Student(const char* name, int grade) : grade(grade) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

Student::Student(const Student& other) : grade(other.grade) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
}

Student::~Student() {
    delete[] name;
}

// Item 10: Returns a reference to *this
// Item 11: Handles self-assignment
Student& Student::operator=(const Student& rhs) {
    // Item 11: Check for self-assignment
    if (this == &rhs) {
        return *this;
    }

    // Deallocate old memory
    delete[] name;

    // Allocate new memory and copy
    name = new char[strlen(rhs.name) + 1];
    strcpy(name, rhs.name);
    grade = rhs.grade;

    // Item 10: Return *this
    return *this;
}

void Student::print() const {
    std::cout << "Student: " << name << ", Grade: " << grade << std::endl;
}
