#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <cstring>

class Student {
public:
    Student(const char* name, int grade);
    Student(const Student& other);
    virtual ~Student();

    // Item 10: Have assignment operators return a reference to *this
    // Item 11: Handle assignment to self in operator=
    Student& operator=(const Student& rhs);

    void print() const;

protected:
    char* name;
    int grade;
};

#endif // STUDENT_H
