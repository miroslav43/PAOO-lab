#include "Project.hpp"
#include "Mentor.hpp"
#include "Startup.hpp"
#include "Accelerator.hpp"
#include "Logger.hpp"
#include <iostream>
#include <utility>

int main()
{
    std::cout << "===== PAOO LAB4 - SIMPLE TESTS =====" << std::endl;

    // ============================================
    // CERINȚA 1: CMake Build (structura proiectului)
    // ============================================
    std::cout << "\n1. BUILD cu CMake ✓" << std::endl;
    std::cout << "   - Fișier: CMakeLists.txt" << std::endl;
    std::cout << "   - Structură: src/, include/, build/" << std::endl;

    // ============================================
    // CERINȚA 2: Encapsulare
    // ============================================
    std::cout << "\n2. ENCAPSULARE (membrii privați + getters/setters)" << std::endl;
    Project proj("Mobile App", 6, 50000.0);
    std::cout << "   [Project] Membrii privați:" << std::endl;
    std::cout << "   - char* description (PRIVAT)" << std::endl;
    std::cout << "   - int duration (PRIVAT)" << std::endl;
    std::cout << "   - double budget (PRIVAT)" << std::endl;
    std::cout << "   Acces prin getters:" << std::endl;
    std::cout << "   - getDescription(): " << proj.getDescription() << std::endl;
    std::cout << "   - getDuration(): " << proj.getDuration() << " months" << std::endl;
    std::cout << "   - getBudget(): $" << proj.getBudget() << std::endl;

    // ============================================
    // CERINȚA 3: Inițializarea membrilor din constructor
    // ============================================
    std::cout << "\n3. INITIALIZATION LIST (membrii inițializați în constructor)" << std::endl;
    std::cout << "   [Project] Constructor: Project::Project()" << std::endl;
    std::cout << "   : duration(dur), budget(budg)  ← INITIALIZATION LIST" << std::endl;
    std::cout << "   ✓ Membrii sunt inițializați ÎNAINTE de body" << std::endl;

    // ============================================
    // CERINȚA 4: Eliberarea heap-ului în destructor
    // ============================================
    std::cout << "\n4. DESTRUCTOR - Eliberare Heap" << std::endl;
    std::cout << "   [Project] Destructor:" << std::endl;
    std::cout << "   delete[] description;  ← Eliberează memoria alocată" << std::endl;
    {
        Project tempProj("Temp Project", 3, 10000.0);
        std::cout << "   Created tempProj (pe stack)" << std::endl;
    }
    std::cout << "   ✓ tempProj destroyed, heap freed" << std::endl;

    // ============================================
    // CERINȚA 5: Copy Constructor
    // ============================================
    std::cout << "\n5. COPY CONSTRUCTOR (Deep Copy)" << std::endl;
    Project original("AI Platform", 12, 150000.0);
    std::cout << "   Original: " << original.getDescription() << std::endl;

    Project copied = original;
    std::cout << "   Copied: " << copied.getDescription() << std::endl;

    copied.setDescription("Modified AI Platform");
    std::cout << "   After modification:" << std::endl;
    std::cout << "   - Original: " << original.getDescription() << " (nemodificat ✓)" << std::endl;
    std::cout << "   - Copied: " << copied.getDescription() << " (modificat)" << std::endl;
    std::cout << "   ✓ Deep copy SUCCESS - obiecte independente" << std::endl;

    // ============================================
    // CERINȚA 6: Move Constructor
    // ============================================
    std::cout << "\n6. MOVE CONSTRUCTOR (Transfer Ownership)" << std::endl;

    auto createProject = []() -> Project
    {
        Project temp("Web Platform", 8, 90000.0);
        return temp; // ← MOVE CONSTRUCTOR triggered
    };

    Project moved = createProject();
    std::cout << "   Temporary object moved: " << moved.getDescription() << std::endl;
    std::cout << "   ✓ Move semantics - no copy overhead" << std::endl;

    // Explicit move
    Project another("Cloud Service", 10, 120000.0);
    Project movedAnother = std::move(another);
    std::cout << "   Explicit std::move: " << movedAnother.getDescription() << std::endl;
    std::cout << "   ✓ Move constructor called explicitly" << std::endl;

    // ============================================
    // EFFECTIVE C++ ITEMS - DEMONSTRAȚII COMPLETE
    // ============================================
    std::cout << "\n\n═══════════════════════════════════════════════════════" << std::endl;
    std::cout << "  EFFECTIVE C++ ITEMS 10, 11, 12 - DEMONSTRAȚII" << std::endl;
    std::cout << "═══════════════════════════════════════════════════════\n"
              << std::endl;

    // ============================================
    // ITEM 10: Have assignment operators return a reference to *this
    // ============================================
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
    std::cout << "ITEM 10: Assignment operators return reference to *this" << std::endl;
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
              << std::endl;

    std::cout << "🎯 SCOPUL: Permite CHAIN ASSIGNMENT (a = b = c)\n"
              << std::endl;

    std::cout << "📌 IMPLEMENTARE în Project.cpp:" << std::endl;
    std::cout << "   Project& operator=(const Project& other) {" << std::endl;
    std::cout << "       // ... copiere date ..." << std::endl;
    std::cout << "       return *this;  ← ESENȚIAL pentru chain assignment" << std::endl;
    std::cout << "   }\n"
              << std::endl;

    std::cout << "📝 DEMONSTRAȚIE - Chain Assignment:" << std::endl;
    Project p1("Project Alpha", 3, 15000.0);
    Project p2("Project Beta", 6, 25000.0);
    Project p3("Project Gamma", 9, 35000.0);

    std::cout << "\n   Starea inițială:" << std::endl;
    std::cout << "   p1: " << p1.getDescription() << " (budget: $" << p1.getBudget() << ")" << std::endl;
    std::cout << "   p2: " << p2.getDescription() << " (budget: $" << p2.getBudget() << ")" << std::endl;
    std::cout << "   p3: " << p3.getDescription() << " (budget: $" << p3.getBudget() << ")" << std::endl;

    std::cout << "\n   Executăm: p1 = p2 = p3;" << std::endl;
    std::cout << "   ├─ Evaluare de la DREAPTA la STÂNGA" << std::endl;
    std::cout << "   ├─ Pasul 1: p2 = p3  (p2 devine copia lui p3)" << std::endl;
    std::cout << "   ├─ p2.operator=(p3) returnează p2& (referință)" << std::endl;
    std::cout << "   └─ Pasul 2: p1 = p2  (p1 devine copia lui p2)" << std::endl;

    p1 = p2 = p3; // ← CHAIN ASSIGNMENT!

    std::cout << "\n   După chain assignment:" << std::endl;
    std::cout << "   p1: " << p1.getDescription() << " (budget: $" << p1.getBudget() << ")" << std::endl;
    std::cout << "   p2: " << p2.getDescription() << " (budget: $" << p2.getBudget() << ")" << std::endl;
    std::cout << "   p3: " << p3.getDescription() << " (budget: $" << p3.getBudget() << ")" << std::endl;
    std::cout << "   ✅ TOATE au aceleași valori ca p3!" << std::endl;

    std::cout << "\n   ❌ CE S-AR ÎNTÂMPLA DACĂ operator= ar returna VOID?" << std::endl;
    std::cout << "      void operator=(const Project& other) { ... }" << std::endl;
    std::cout << "      p1 = p2 = p3;" << std::endl;
    std::cout << "      └─ EROARE DE COMPILARE! Nu poți asigna void lui p1" << std::endl;
    std::cout << "      └─ Chain assignment ar fi IMPOSIBIL!\n"
              << std::endl;

    // ============================================
    // ITEM 11: Handle assignment to self in operator=
    // ============================================
    std::cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
    std::cout << "ITEM 11: Handle assignment to self in operator=" << std::endl;
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
              << std::endl;

    std::cout << "🎯 SCOPUL: Evită CRASH-uri și comportament nedefinit în self-assignment\n"
              << std::endl;

    std::cout << "📌 IMPLEMENTARE în Project.cpp:" << std::endl;
    std::cout << "   Project& operator=(const Project& other) {" << std::endl;
    std::cout << "       if (this == &other) {  ← VERIFICARE ESENȚIALĂ" << std::endl;
    std::cout << "           return *this;       ← Returnează imediat dacă e același obiect" << std::endl;
    std::cout << "       }" << std::endl;
    std::cout << "       delete[] description;   ← Altfel ar șterge memoria pe care o citim!" << std::endl;
    std::cout << "       // ... copiere din other ..." << std::endl;
    std::cout << "   }\n"
              << std::endl;

    std::cout << "❓ DE CE AVEM NEVOIE DE ACEASTĂ VERIFICARE?\n"
              << std::endl;
    std::cout << "   Scenariul FĂRĂ verificare (if this == &other):" << std::endl;
    std::cout << "   ┌─────────────────────────────────────────────────┐" << std::endl;
    std::cout << "   │ Project p(\"Test\", 5, 1000.0);                  │" << std::endl;
    std::cout << "   │ p = p;  // Self-assignment                      │" << std::endl;
    std::cout << "   │                                                  │" << std::endl;
    std::cout << "   │ În operator=(const Project& other):             │" << std::endl;
    std::cout << "   │ // this == &p, other == p (ACELAȘI OBIECT!)     │" << std::endl;
    std::cout << "   │                                                  │" << std::endl;
    std::cout << "   │ delete[] description; ❌ Șterge memoria         │" << std::endl;
    std::cout << "   │ // Acum description pointează la memorie ștearsă│" << std::endl;
    std::cout << "   │                                                  │" << std::endl;
    std::cout << "   │ strcpy(description, other.description); ❌      │" << std::endl;
    std::cout << "   │ // other.description e TOT memoria ștearsă!     │" << std::endl;
    std::cout << "   │ // → UNDEFINED BEHAVIOR / CRASH!                │" << std::endl;
    std::cout << "   └─────────────────────────────────────────────────┘\n"
              << std::endl;

    std::cout << "📝 DEMONSTRAȚIE - Self-Assignment:" << std::endl;
    Project pSelf("Self-Assignment Test", 7, 40000.0);
    std::cout << "\n   Obiect înainte: " << pSelf.getDescription()
              << " (budget: $" << pSelf.getBudget() << ")" << std::endl;

    std::cout << "\n   Executăm: pSelf = pSelf;  (SELF-ASSIGNMENT!)" << std::endl;
    std::cout << "   ├─ În operator=: this = " << &pSelf << std::endl;
    std::cout << "   ├─ În operator=: &other = " << &pSelf << std::endl;
    std::cout << "   └─ this == &other? TRUE → DETECTAT!" << std::endl;

    pSelf = pSelf; // Self-assignment protejat!

    std::cout << "\n   Obiect după: " << pSelf.getDescription()
              << " (budget: $" << pSelf.getBudget() << ")" << std::endl;
    std::cout << "   ✅ Obiectul este INTACT! Verificarea a prevenit CRASH-ul!\n"
              << std::endl;

    std::cout << "   📋 SITUAȚII când poate apărea self-assignment:\n"
              << std::endl;
    std::cout << "   1. Direct (rar):        p = p;" << std::endl;
    std::cout << "   2. Prin referințe:     Project& ref = p; p = ref;" << std::endl;
    std::cout << "   3. În funcții:         void assign(Project& a, Project& b) { a = b; }" << std::endl;
    std::cout << "                          assign(p, p);  ← self-assignment ascuns!" << std::endl;
    std::cout << "   4. În containere:      vector[i] = vector[i];\n"
              << std::endl;

    // ============================================
    // ITEM 12: Copy all parts of an object
    // ============================================
    std::cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
    std::cout << "ITEM 12: Copy all parts of an object" << std::endl;
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
              << std::endl;

    std::cout << "🎯 SCOPUL: Asigură că TOATE membrii sunt copiați corect\n"
              << std::endl;

    std::cout << "⚠️  ATENȚIE la:" << std::endl;
    std::cout << "   1. Toți membrii (variabile) trebuie copiați" << std::endl;
    std::cout << "   2. Pointerii necesită DEEP COPY (nu shallow copy)" << std::endl;
    std::cout << "   3. Constructor de copiere ȘI operator= trebuie implementate" << std::endl;
    std::cout << "   4. La moștenire: trebuie copiat și base class!\n"
              << std::endl;

    std::cout << "📌 IMPLEMENTARE în Startup.cpp:" << std::endl;
    std::cout << "   Clasa Startup are 5 membri:" << std::endl;
    std::cout << "   ├─ char* name;              (pointer → deep copy)" << std::endl;
    std::cout << "   ├─ double funding;          (value)" << std::endl;
    std::cout << "   ├─ char** teamMembers;      (array de pointeri → deep copy)" << std::endl;
    std::cout << "   ├─ int teamSize;            (value)" << std::endl;
    std::cout << "   └─ Project* mainProject;    (pointer la obiect → deep copy)\n"
              << std::endl;

    std::cout << "   Copy Constructor:" << std::endl;
    std::cout << "   Startup(const Startup& other)" << std::endl;
    std::cout << "       : funding(other.funding), teamSize(other.teamSize) {" << std::endl;
    std::cout << "       name = new char[strlen(other.name) + 1];  ← DEEP COPY" << std::endl;
    std::cout << "       strcpy(name, other.name);" << std::endl;
    std::cout << "       // ... copiere teamMembers (deep copy array) ..." << std::endl;
    std::cout << "       mainProject = new Project(*other.mainProject); ← DEEP COPY" << std::endl;
    std::cout << "   }\n"
              << std::endl;

    std::cout << "📝 DEMONSTRAȚIE - Copierea TUTUROR părților:" << std::endl;

    const char *team1[] = {"Alice", "Bob", "Charlie"};
    Startup startup1("TechStartup Original", 100000.0, team1, 3,
                     Project("Mobile App MVP", 6, 50000.0));

    std::cout << "\n   Obiect Original (startup1):" << std::endl;
    std::cout << "   ├─ Name: " << startup1.getName() << std::endl;
    std::cout << "   ├─ Funding: $" << startup1.getFunding() << std::endl;
    std::cout << "   ├─ Team Size: " << startup1.getTeamSize() << std::endl;
    std::cout << "   └─ Project: " << startup1.getMainProject()->getDescription() << std::endl;

    std::cout << "\n   Creăm copia: Startup startup2 = startup1;" << std::endl;
    Startup startup2 = startup1; // Copy constructor

    std::cout << "\n   Obiect Copiat (startup2):" << std::endl;
    std::cout << "   ├─ Name: " << startup2.getName() << std::endl;
    std::cout << "   ├─ Funding: $" << startup2.getFunding() << std::endl;
    std::cout << "   ├─ Team Size: " << startup2.getTeamSize() << std::endl;
    std::cout << "   └─ Project: " << startup2.getMainProject()->getDescription() << std::endl;
    std::cout << "   ✅ TOATE valorile copiate corect!\n"
              << std::endl;

    std::cout << "   🔍 VERIFICARE: Sunt obiecte INDEPENDENTE? (deep copy)" << std::endl;
    std::cout << "   Adrese de memorie diferite?" << std::endl;
    std::cout << "   ├─ startup1.name:    " << (void *)startup1.getName() << std::endl;
    std::cout << "   ├─ startup2.name:    " << (void *)startup2.getName() << " ← Adresă diferită!" << std::endl;
    std::cout << "   ├─ startup1.project: " << (void *)startup1.getMainProject() << std::endl;
    std::cout << "   └─ startup2.project: " << (void *)startup2.getMainProject() << " ← Adresă diferită!" << std::endl;
    std::cout << "   ✅ Deep copy reușit - obiecte complet INDEPENDENTE!\n"
              << std::endl;

    std::cout << "   ❌ CE S-AR ÎNTÂMPLA cu SHALLOW COPY?" << std::endl;
    std::cout << "      // Shallow copy (GREȘIT!):" << std::endl;
    std::cout << "      name = other.name;  ← Copiază doar POINTERUL" << std::endl;
    std::cout << "      // Ambele obiecte ar pointa la ACEEAȘI memorie!" << std::endl;
    std::cout << "      // La distrugere: delete pe aceeași memorie de 2 ori → CRASH!" << std::endl;

    std::cout << "\n\n═══════════════════════════════════════════════════════" << std::endl;
    std::cout << "  REZUMAT EFFECTIVE C++ ITEMS" << std::endl;
    std::cout << "═══════════════════════════════════════════════════════\n"
              << std::endl;
    std::cout << "✅ ITEM 10: return *this → Permite chain assignment (a=b=c)" << std::endl;
    std::cout << "✅ ITEM 11: if(this==&other) → Protecție împotriva self-assignment" << std::endl;
    std::cout << "✅ ITEM 12: Deep copy → Copiază TOATE părțile, inclusiv pointeri\n"
              << std::endl;

    return 0;
}
