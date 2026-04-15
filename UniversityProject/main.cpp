#include <iostream>
#include <utility>
#include "Student.h"

using namespace std;

int main() {
    cout << "Student 1" << endl;
    Student s1("Kateryna", 19, "BS-2024");
    s1.addGrade("Math", 95);
    s1.addGrade("C++", 100);

    // Тестуємо Deep Copy (конструктор  копіювання)
    cout << "\n Testing Deep Copy (s2 = s1)" << endl;
    Student s2 = s1;
    s2.addGrade("Physics", 90);

    cout << "Student 1 grades count: " << s1.getGradesCount() << endl; // Має бути 2
    cout << "Student 2 grades count: " << s2.getGradesCount() << endl; // Має бути 3

    // Тестуємо Move Semantics (конструктор перенесення)
    cout << "\n Testing Move Semantics (s3 = move(s1))" << endl;
    Student s3 = std::move(s1);

    cout << "Student 3 name: " << s3.getName() << endl;
    if (s1.isGradesEmpty()) {
        cout << "Student 1 is now empty (resources moved successfully)." << endl;
    }

    cout << "\n--- End of tests (Destructors will be called now) ---" << endl;
    return 0;
}