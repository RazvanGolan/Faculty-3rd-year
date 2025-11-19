#include "GradStudent.h"

GradStudent::GradStudent(const char* name, int grade, const char* thesis) 
    : Student(name, grade) {
    this->thesis = new char[strlen(thesis) + 1];
    strcpy(this->thesis, thesis);
}

// Item 12: Copy all parts of an object (invoke base class copy constructor)
GradStudent::GradStudent(const GradStudent& other) 
    : Student(other) { // Invoke base class copy constructor
    thesis = new char[strlen(other.thesis) + 1];
    strcpy(thesis, other.thesis);
}

GradStudent::~GradStudent() {
    delete[] thesis;
}

// Item 12: Copy all parts of an object (invoke base class assignment operator)
GradStudent& GradStudent::operator=(const GradStudent& rhs) {
    if (this == &rhs) {
        return *this;
    }

    // Call base class assignment operator to handle base parts
    Student::operator=(rhs);

    // Handle derived parts
    delete[] thesis;
    thesis = new char[strlen(rhs.thesis) + 1];
    strcpy(thesis, rhs.thesis);

    return *this;
}

void GradStudent::print() const {
    std::cout << "GradStudent: " << name << ", Grade: " << grade << ", Thesis: " << thesis << std::endl;
}
