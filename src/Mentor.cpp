#include "Mentor.hpp"
#include "Logger.hpp"

Mentor::Mentor(const char *n, int years, const char *exp)
    : yearsOfExperience(years)
{
    Logger::getInstance().logConstructor("Mentor", "Parameterized", n);

    name = new char[strlen(n) + 1];
    strcpy(name, n);

    expertise = new char[strlen(exp) + 1];
    strcpy(expertise, exp);
}

Mentor::~Mentor()
{
    if (name)
    {
        Logger::getInstance().logDestructor("Mentor", name);
    }
    else
    {
        Logger::getInstance().logDestructor("Mentor", "(moved-from object)");
    }
    delete[] name;
    delete[] expertise;
}

Mentor::Mentor(const Mentor &other)
    : yearsOfExperience(other.yearsOfExperience)
{
    Logger::getInstance().logConstructor("Mentor", "Copy", other.name);

    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    expertise = new char[strlen(other.expertise) + 1];
    strcpy(expertise, other.expertise);
}

Mentor &Mentor::operator=(const Mentor &other)
{
    Logger::getInstance().logOperation("Mentor Copy Assignment", "");

    if (this == &other)
    {
        Logger::getInstance().logInfo("Self-assignment detected, skipping");
        return *this;
    }

    delete[] name;
    delete[] expertise;

    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    expertise = new char[strlen(other.expertise) + 1];
    strcpy(expertise, other.expertise);

    yearsOfExperience = other.yearsOfExperience;

    return *this;
}

Mentor::Mentor(Mentor &&other) noexcept
    : name(other.name), yearsOfExperience(other.yearsOfExperience), expertise(other.expertise)
{
    Logger::getInstance().logConstructor("Mentor", "Move", other.name);

    other.name = nullptr;
    other.expertise = nullptr;
    other.yearsOfExperience = 0;
}

Mentor &Mentor::operator=(Mentor &&other) noexcept
{
    Logger::getInstance().logOperation("Mentor Move Assignment", "");

    if (this == &other)
    {
        return *this;
    }

    delete[] name;
    delete[] expertise;

    name = other.name;
    expertise = other.expertise;
    yearsOfExperience = other.yearsOfExperience;

    other.name = nullptr;
    other.expertise = nullptr;
    other.yearsOfExperience = 0;

    return *this;
}

const char *Mentor::getName() const
{
    return name;
}

int Mentor::getYearsOfExperience() const
{
    return yearsOfExperience;
}

const char *Mentor::getExpertise() const
{
    return expertise;
}

void Mentor::display() const
{
    std::cout << "  Mentor: " << name
              << " | Experience: " << yearsOfExperience << " years"
              << " | Expertise: " << expertise << std::endl;
}
