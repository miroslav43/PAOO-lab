#include "Startup.hpp"
#include "Logger.hpp"

Startup::Startup(const char *n, double fund, const char **members, int size, const Project &proj)
    : funding(fund), teamSize(size)
{
    Logger::getInstance().logConstructor("Startup", "Parameterized", n);

    name = new char[strlen(n) + 1];
    strcpy(name, n);

    teamMembers = new char *[teamSize];
    for (int i = 0; i < teamSize; ++i)
    {
        teamMembers[i] = new char[strlen(members[i]) + 1];
        strcpy(teamMembers[i], members[i]);
    }

    mainProject = new Project(proj);
}

Startup::~Startup()
{
    if (name)
    {
        Logger::getInstance().logDestructor("Startup", name);
    }
    else
    {
        Logger::getInstance().logDestructor("Startup", "(moved-from object)");
    }

    delete[] name;

    for (int i = 0; i < teamSize; ++i)
    {
        delete[] teamMembers[i];
    }
    delete[] teamMembers;

    delete mainProject;
}

Startup::Startup(const Startup &other)
    : funding(other.funding), teamSize(other.teamSize)
{
    Logger::getInstance().logConstructor("Startup", "Copy", other.name);

    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    teamMembers = new char *[teamSize];
    for (int i = 0; i < teamSize; ++i)
    {
        teamMembers[i] = new char[strlen(other.teamMembers[i]) + 1];
        strcpy(teamMembers[i], other.teamMembers[i]);
    }

    mainProject = new Project(*other.mainProject);
}

Startup &Startup::operator=(const Startup &other)
{
    Logger::getInstance().logOperation("Startup Copy Assignment", "");

    if (this == &other)
    {
        Logger::getInstance().logInfo("Self-assignment detected, skipping");
        return *this;
    }

    delete[] name;
    for (int i = 0; i < teamSize; ++i)
    {
        delete[] teamMembers[i];
    }
    delete[] teamMembers;
    delete mainProject;

    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    funding = other.funding;
    teamSize = other.teamSize;

    teamMembers = new char *[teamSize];
    for (int i = 0; i < teamSize; ++i)
    {
        teamMembers[i] = new char[strlen(other.teamMembers[i]) + 1];
        strcpy(teamMembers[i], other.teamMembers[i]);
    }

    mainProject = new Project(*other.mainProject);

    return *this;
}

Startup::Startup(Startup &&other) noexcept
    : name(other.name), funding(other.funding), teamMembers(other.teamMembers),
      teamSize(other.teamSize), mainProject(other.mainProject)
{
    Logger::getInstance().logConstructor("Startup", "Move", other.name);

    other.name = nullptr;
    other.teamMembers = nullptr;
    other.teamSize = 0;
    other.mainProject = nullptr;
    other.funding = 0.0;
}

Startup &Startup::operator=(Startup &&other) noexcept
{
    Logger::getInstance().logOperation("Startup Move Assignment", "");

    if (this == &other)
    {
        return *this;
    }

    delete[] name;
    for (int i = 0; i < teamSize; ++i)
    {
        delete[] teamMembers[i];
    }
    delete[] teamMembers;
    delete mainProject;

    name = other.name;
    funding = other.funding;
    teamMembers = other.teamMembers;
    teamSize = other.teamSize;
    mainProject = other.mainProject;

    other.name = nullptr;
    other.teamMembers = nullptr;
    other.teamSize = 0;
    other.mainProject = nullptr;
    other.funding = 0.0;

    return *this;
}

// Getters
const char *Startup::getName() const
{
    return name;
}

double Startup::getFunding() const
{
    return funding;
}

int Startup::getTeamSize() const
{
    return teamSize;
}

const Project *Startup::getMainProject() const
{
    return mainProject;
}

void Startup::display() const
{
    std::cout << "  Startup: " << name << " | Funding: $" << funding
              << " | Team Size: " << teamSize << std::endl;
    if (mainProject)
    {
        mainProject->display();
    }
}
