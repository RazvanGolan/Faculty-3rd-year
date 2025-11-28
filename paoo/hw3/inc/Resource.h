#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <iostream>

// A simple class representing a resource (e.g., file, memory, connection)
class Resource {
public:
    Resource(const std::string& name);
    ~Resource();

    void use();

private:
    std::string name;
};

#endif // RESOURCE_H
