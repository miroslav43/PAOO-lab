#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <cstring>
#include <iostream>

class Project {
private:
    char* description;
    int duration;
    double budget;

public:
    Project(const char* desc, int dur, double budg);
    
    ~Project();
    
    Project(const Project& other);
    
    Project& operator=(const Project& other);
    
    Project(Project&& other) noexcept;
    
    Project& operator=(Project&& other) noexcept;
    
    const char* getDescription() const;
    int getDuration() const;
    double getBudget() const;
    
    void setDescription(const char* desc);
    void setDuration(int dur);
    void setBudget(double budg);
    
    void display() const;
};

#endif // PROJECT_HPP



