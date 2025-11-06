#ifndef MENTOR_HPP
#define MENTOR_HPP

#include <iostream>
#include <cstring>

class Mentor {
private:
    char* name;
    int yearsOfExperience;
    char* expertise;

public:
    Mentor(const char* n, int years, const char* exp);
    
    ~Mentor();
    
    Mentor(const Mentor& other);
    
    Mentor& operator=(const Mentor& other);
    
    Mentor(Mentor&& other) noexcept;
    
    Mentor& operator=(Mentor&& other) noexcept;
    
    const char* getName() const;
    int getYearsOfExperience() const;
    const char* getExpertise() const;
    
    void display() const;
};

#endif // MENTOR_HPP



