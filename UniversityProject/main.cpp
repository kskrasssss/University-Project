#include <iostream>
#include "Student.h"
#include "MasterEnrollment.h"
#include "PhDEnrollment.h"

using namespace std;

void process(const Enrollment& e, const Student& s) {
    e.printRequirements();
    e.checkEligibility(s);
}

int main() {
    Student s1("Kateryna", 19, "ST-01");

    cout << "Testing MasterEnrollment\n";
    MasterEnrollment m;
    m.printRequirements();
    m.checkEligibility(s1);

    cout << "\nTesting polymorphism (pointer)\n";
    Enrollment* e = new MasterEnrollment();
    e->printRequirements();
    e->checkEligibility(s1);

    cout << "\nTesting polymorphism (reference)\n";
    process(m, s1);

    delete e;

    return 0;
}