#include "Project.hpp"
#include "Mentor.hpp"
#include "Startup.hpp"
#include "Accelerator.hpp"
#include "Logger.hpp"
#include <iostream>
#include <utility>

void printSeparator(const char *title)
{
    Logger::getInstance().logSeparator(title);
}

void demonstrateBasicConstructionDestruction()
{
    printSeparator("1. BASIC CONSTRUCTION & DESTRUCTION");

    std::cout << "\nCreating a Project object:" << std::endl;
    Project proj("AI Platform", 12, 150000.0);
    proj.display();

    std::cout << "\nCreating a Mentor object:" << std::endl;
    Mentor mentor("John Smith", 15, "Machine Learning, Cloud Architecture");
    mentor.display();

    std::cout << "\nObjects will be destroyed when going out of scope:" << std::endl;
}

void demonstrateCopyConstructor()
{
    printSeparator("2. COPY CONSTRUCTOR - DEEP COPY NECESSITY");

    std::cout << "\n--- Creating original Project ---" << std::endl;
    Project original("Blockchain Solution", 18, 250000.0);

    std::cout << "\n--- Copying Project (Deep Copy) ---" << std::endl;
    Project copied = original;

    std::cout << "\n--- Displaying both projects ---" << std::endl;
    std::cout << "Original: ";
    original.display();
    std::cout << "Copied:   ";
    copied.display();

    std::cout << "\n--- Modifying copied project ---" << std::endl;
    copied.setDescription("Modified Blockchain Solution");
    copied.setBudget(300000.0);

    std::cout << "Original (unchanged): ";
    original.display();
    std::cout << "Copied (modified):    ";
    copied.display();

    std::cout << "\n--- WHY DEEP COPY IS NEEDED ---" << std::endl;
    std::cout << "Without a proper copy constructor, both objects would share" << std::endl;
    std::cout << "the same memory address for 'description', leading to:" << std::endl;
    std::cout << "  1. Changes in one object affect the other" << std::endl;
    std::cout << "  2. Double-free error when both destructors try to delete same memory" << std::endl;

    std::cout << "\n--- Destroying both projects ---" << std::endl;
}

void demonstrateMoveConstructor()
{
    printSeparator("3. MOVE CONSTRUCTOR - EFFICIENCY");

    std::cout << "\n--- Creating a temporary Project ---" << std::endl;
    auto createProject = []() -> Project
    {
        Project temp("Temporary IoT Project", 6, 80000.0);
        std::cout << "Returning from function..." << std::endl;
        return temp;
    };

    std::cout << "\n--- Using move semantics (efficient transfer) ---" << std::endl;
    Project moved = createProject();
    moved.display();

    std::cout << "\n--- WHY MOVE IS BENEFICIAL ---" << std::endl;
    std::cout << "Move constructor transfers ownership without copying:" << std::endl;
    std::cout << "  1. No memory allocation for duplicate data" << std::endl;
    std::cout << "  2. Much faster for large objects" << std::endl;
    std::cout << "  3. Original object is left in valid but empty state" << std::endl;

    std::cout << "\n--- Explicit move with std::move ---" << std::endl;
    Project another("Another Project", 10, 120000.0);
    Project movedAnother = std::move(another);
    movedAnother.display();

    std::cout << "\n--- Destroying moved objects ---" << std::endl;
}

void demonstrateEncapsulation()
{
    printSeparator("4. ENCAPSULATION - CONTROLLED ACCESS");

    std::cout << "\n--- All members are private, accessed via getters/setters ---" << std::endl;
    Project proj("Security System", 8, 100000.0);

    std::cout << "\nAccessing private data through getters:" << std::endl;
    std::cout << "  Description: " << proj.getDescription() << std::endl;
    std::cout << "  Duration: " << proj.getDuration() << " months" << std::endl;
    std::cout << "  Budget: $" << proj.getBudget() << std::endl;

    std::cout << "\nModifying private data through setters:" << std::endl;
    proj.setBudget(120000.0);
    std::cout << "  New Budget: $" << proj.getBudget() << std::endl;

    std::cout << "\n--- WHY ENCAPSULATION IS IMPORTANT ---" << std::endl;
    std::cout << "  1. Protects data integrity (validation can be added in setters)" << std::endl;
    std::cout << "  2. Internal implementation can change without affecting users" << std::endl;
    std::cout << "  3. Provides clear interface for object interaction" << std::endl;
}

void demonstrateAssignmentOperators()
{
    printSeparator("5. ASSIGNMENT OPERATORS - EFFECTIVE C++");

    std::cout << "\n--- Item 10: Assignment returns reference to *this ---" << std::endl;
    Project p1("Project A", 10, 100000.0);
    Project p2("Project B", 12, 150000.0);
    Project p3("Project C", 8, 80000.0);

    std::cout << "\nChaining assignments (a = b = c):" << std::endl;
    p1 = p2 = p3;
    std::cout << "All projects now have same data:" << std::endl;
    p1.display();
    p2.display();
    p3.display();

    std::cout << "\n--- Item 11: Handle self-assignment ---" << std::endl;
    std::cout << "Assigning object to itself:" << std::endl;
    p1 = p1;
    std::cout << "Self-assignment handled correctly, object still valid:" << std::endl;
    p1.display();

    std::cout << "\n--- WHY SELF-ASSIGNMENT CHECK IS NEEDED ---" << std::endl;
    std::cout << "Without check: operator= would delete resources before copying, " << std::endl;
    std::cout << "leading to reading from freed memory!" << std::endl;

    std::cout << "\n--- Item 12: Copy ALL parts of an object ---" << std::endl;
    Mentor m1("Alice Johnson", 10, "DevOps");
    Mentor m2("Bob Williams", 5, "Backend Development");
    std::cout << "\nBefore assignment:" << std::endl;
    m1.display();
    m2.display();

    std::cout << "\nAfter assignment (all members copied):" << std::endl;
    m1 = m2;
    m1.display();
    m2.display();
}

void demonstrateComplexObjects()
{
    printSeparator("6. COMPLEX OBJECTS - COMPOSITION");

    std::cout << "\n--- Creating Startup with Project and team ---" << std::endl;
    Project proj("Mobile App", 10, 120000.0);
    const char *team[] = {"Alice", "Bob", "Charlie"};
    Startup startup("TechVenture", 500000.0, team, 3, proj);
    startup.display();

    std::cout << "\n--- Copying Startup (deep copy of all components) ---" << std::endl;
    Startup startupCopy = startup;
    startupCopy.display();

    std::cout << "\n--- Creating Accelerator and adding startups ---" << std::endl;
    Accelerator accelerator("Innovation Hub", 3);

    Project proj2("Web Platform", 8, 90000.0);
    const char *team2[] = {"David", "Eve"};
    Startup startup2("WebCorp", 300000.0, team2, 2, proj2);

    accelerator.addStartup(startup);
    accelerator.addStartup(startup2);

    accelerator.display();

    std::cout << "\n--- All objects will be properly destroyed ---" << std::endl;
}

void demonstrateInitializationList()
{
    printSeparator("7. INITIALIZATION LIST VS ASSIGNMENT");

    std::cout << "\n--- WHY USE INITIALIZATION LISTS ---" << std::endl;
    std::cout << "Initialization lists are used in all constructors because:" << std::endl;
    std::cout << "  1. More efficient (direct initialization vs default + assignment)" << std::endl;
    std::cout << "  2. Required for const members and reference members" << std::endl;
    std::cout << "  3. Required for base class initialization" << std::endl;
    std::cout << "  4. Members are initialized in declaration order" << std::endl;

    std::cout << "\nExample: Project constructor uses initialization list" << std::endl;
    std::cout << "  Project::Project(...) : duration(dur), budget(budg) { ... }" << std::endl;

    Project proj("Demo", 6, 50000.0);
    proj.display();
}

int main()
{
    std::cout << "===============================================" << std::endl;
    std::cout << "   PAOO LAB4 - C++ CONCEPTS DEMONSTRATION" << std::endl;
    std::cout << "   Startup Accelerator Management System" << std::endl;
    std::cout << "===============================================" << std::endl;

    try
    {
        demonstrateBasicConstructionDestruction();
        demonstrateCopyConstructor();
        demonstrateMoveConstructor();
        demonstrateEncapsulation();
        demonstrateAssignmentOperators();
        demonstrateComplexObjects();
        demonstrateInitializationList();

        printSeparator("ALL DEMONSTRATIONS COMPLETED");
        std::cout << "\nKey Concepts Demonstrated:" << std::endl;
        std::cout << "  [✓] CMake Build Structure" << std::endl;
        std::cout << "  [✓] Encapsulation (private members)" << std::endl;
        std::cout << "  [✓] Constructor Initialization Lists" << std::endl;
        std::cout << "  [✓] Heap Memory Management (new/delete)" << std::endl;
        std::cout << "  [✓] Copy Constructor (Deep Copy)" << std::endl;
        std::cout << "  [✓] Move Constructor" << std::endl;
        std::cout << "  [✓] Copy Assignment Operator" << std::endl;
        std::cout << "  [✓] Move Assignment Operator" << std::endl;
        std::cout << "  [✓] Effective C++ Items 10, 11, 12" << std::endl;
        std::cout << "  [✓] Singleton Design Pattern (Logger)" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
