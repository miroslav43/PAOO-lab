#ifndef STARTUP_HPP
#define STARTUP_HPP

#include "Project.hpp"
#include <iostream>
#include <cstring>

class Startup {
private:
    char* name;
    double funding;
    char** teamMembers;
    int teamSize;
    Project* mainProject;

public:
    Startup(const char* n, double fund, const char** members, int size, const Project& proj);
    
    ~Startup();
    
    Startup(const Startup& other);
    
    Startup& operator=(const Startup& other);
    
    Startup(Startup&& other) noexcept;
    
    Startup& operator=(Startup&& other) noexcept;
    
    const char* getName() const;
    double getFunding() const;
    int getTeamSize() const;
    const Project* getMainProject() const;
    
    void display() const;
};

#endif // STARTUP_HPP



