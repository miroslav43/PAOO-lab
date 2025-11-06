#include "Project.hpp"
#include "Logger.hpp"

Project::Project(const char *desc, int dur, double budg)
    : duration(dur), budget(budg)
{
    Logger::getInstance().logConstructor("Project", "Parameterized", desc);
    description = new char[strlen(desc) + 1];
    strcpy(description, desc);
}

Project::~Project()
{
    if (description)
    {
        Logger::getInstance().logDestructor("Project", description);
        delete[] description;
    }
    else
    {
        Logger::getInstance().logDestructor("Project", "(moved-from object)");
    }
}

Project::Project(const Project &other)
    : duration(other.duration), budget(other.budget)
{
    Logger::getInstance().logConstructor("Project", "Copy", other.description);
    description = new char[strlen(other.description) + 1];
    strcpy(description, other.description);
}

Project &Project::operator=(const Project &other)
{
    Logger::getInstance().logOperation("Project Copy Assignment", "");

    if (this == &other)
    {
        Logger::getInstance().logInfo("Self-assignment detected, skipping");
        return *this;
    }

    delete[] description;

    description = new char[strlen(other.description) + 1];
    strcpy(description, other.description);
    duration = other.duration;
    budget = other.budget;

    return *this;
}

Project::Project(Project &&other) noexcept
    : description(other.description), duration(other.duration), budget(other.budget)
{
    Logger::getInstance().logConstructor("Project", "Move", other.description);

    other.description = nullptr;
    other.duration = 0;
    other.budget = 0.0;
}

Project &Project::operator=(Project &&other) noexcept
{
    Logger::getInstance().logOperation("Project Move Assignment", "");

    if (this == &other)
    {
        return *this;
    }

    delete[] description;

    description = other.description;
    duration = other.duration;
    budget = other.budget;

    other.description = nullptr;
    other.duration = 0;
    other.budget = 0.0;

    return *this;
}

const char *Project::getDescription() const
{
    return description;
}

int Project::getDuration() const
{
    return duration;
}

double Project::getBudget() const
{
    return budget;
}

void Project::setDescription(const char *desc)
{
    delete[] description;
    description = new char[strlen(desc) + 1];
    strcpy(description, desc);
}

void Project::setDuration(int dur)
{
    duration = dur;
}

void Project::setBudget(double budg)
{
    budget = budg;
}

void Project::display() const
{
    std::cout << "  Project: " << description
              << " | Duration: " << duration << " months"
              << " | Budget: $" << budget << std::endl;
}
