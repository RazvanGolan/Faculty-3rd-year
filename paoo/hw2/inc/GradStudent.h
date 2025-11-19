#ifndef GRADSTUDENT_H
#define GRADSTUDENT_H

#include "Student.h"

class GradStudent : public Student {
public:
    GradStudent(const char* name, int grade, const char* thesis);
    GradStudent(const GradStudent& other);
    ~GradStudent();

    // Item 12: Copy all parts of an object
    GradStudent& operator=(const GradStudent& rhs);

    void print() const;

private:
    char* thesis;
};

#endif // GRADSTUDENT_H
