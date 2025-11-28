#include "Resource.h"

Resource::Resource(const std::string& name) : name(name) {
    std::cout << "[Resource] Acquired: " << name << std::endl;
}

Resource::~Resource() {
    std::cout << "[Resource] Released: " << name << std::endl;
}

void Resource::use() {
    std::cout << "[Resource] Using: " << name << std::endl;
}
