#ifndef ACCELERATOR_HPP
#define ACCELERATOR_HPP

#include "Startup.hpp"
#include <iostream>
#include <cstring>

class Accelerator {
private:
    char* name;
    Startup** startups;
    int capacity;
    int currentSize;

public:
    Accelerator(const char* n, int cap);
    
    ~Accelerator();
    
    Accelerator(const Accelerator& other);
    
    Accelerator& operator=(const Accelerator& other);
    
    Accelerator(Accelerator&& other) noexcept;
    
    Accelerator& operator=(Accelerator&& other) noexcept;
    
    bool addStartup(const Startup& startup);
    
    const char* getName() const;
    int getCurrentSize() const;
    int getCapacity() const;
    
    void display() const;
};

#endif // ACCELERATOR_HPP



