#include "Accelerator.hpp"
#include "Logger.hpp"

Accelerator::Accelerator(const char *n, int cap)
    : capacity(cap), currentSize(0)
{
    Logger::getInstance().logConstructor("Accelerator", "Parameterized", n);

    name = new char[strlen(n) + 1];
    strcpy(name, n);

    startups = new Startup *[capacity];
    for (int i = 0; i < capacity; ++i)
    {
        startups[i] = nullptr;
    }
}

Accelerator::~Accelerator()
{
    if (name)
    {
        Logger::getInstance().logDestructor("Accelerator", name);
    }
    else
    {
        Logger::getInstance().logDestructor("Accelerator", "(moved-from object)");
    }

    delete[] name;

    for (int i = 0; i < currentSize; ++i)
    {
        delete startups[i];
    }
    delete[] startups;
}

Accelerator::Accelerator(const Accelerator &other)
    : capacity(other.capacity), currentSize(other.currentSize)
{
    Logger::getInstance().logConstructor("Accelerator", "Copy", other.name);

    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    startups = new Startup *[capacity];
    for (int i = 0; i < currentSize; ++i)
    {
        startups[i] = new Startup(*other.startups[i]);
    }
    for (int i = currentSize; i < capacity; ++i)
    {
        startups[i] = nullptr;
    }
}

Accelerator &Accelerator::operator=(const Accelerator &other)
{
    Logger::getInstance().logOperation("Accelerator Copy Assignment", "");

    if (this == &other)
    {
        Logger::getInstance().logInfo("Self-assignment detected, skipping");
        return *this;
    }

    delete[] name;
    for (int i = 0; i < currentSize; ++i)
    {
        delete startups[i];
    }
    delete[] startups;

    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    capacity = other.capacity;
    currentSize = other.currentSize;

    startups = new Startup *[capacity];
    for (int i = 0; i < currentSize; ++i)
    {
        startups[i] = new Startup(*other.startups[i]);
    }
    for (int i = currentSize; i < capacity; ++i)
    {
        startups[i] = nullptr;
    }

    return *this;
}

Accelerator::Accelerator(Accelerator &&other) noexcept
    : name(other.name), startups(other.startups),
      capacity(other.capacity), currentSize(other.currentSize)
{
    Logger::getInstance().logConstructor("Accelerator", "Move", other.name);

    other.name = nullptr;
    other.startups = nullptr;
    other.capacity = 0;
    other.currentSize = 0;
}

Accelerator &Accelerator::operator=(Accelerator &&other) noexcept
{
    Logger::getInstance().logOperation("Accelerator Move Assignment", "");

    if (this == &other)
    {
        return *this;
    }

    delete[] name;
    for (int i = 0; i < currentSize; ++i)
    {
        delete startups[i];
    }
    delete[] startups;

    name = other.name;
    startups = other.startups;
    capacity = other.capacity;
    currentSize = other.currentSize;

    other.name = nullptr;
    other.startups = nullptr;
    other.capacity = 0;
    other.currentSize = 0;

    return *this;
}

bool Accelerator::addStartup(const Startup &startup)
{
    if (currentSize >= capacity)
    {
        Logger::getInstance().logWarning("Accelerator is full, cannot add more startups");
        return false;
    }

    startups[currentSize] = new Startup(startup);
    currentSize++;
    return true;
}

const char *Accelerator::getName() const
{
    return name;
}

int Accelerator::getCurrentSize() const
{
    return currentSize;
}

int Accelerator::getCapacity() const
{
    return capacity;
}

void Accelerator::display() const
{
    std::cout << "\nAccelerator: " << name
              << " | Capacity: " << currentSize << "/" << capacity << std::endl;
    for (int i = 0; i < currentSize; ++i)
    {
        startups[i]->display();
    }
}
