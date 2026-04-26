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

    s1.setBachelor(true);
    s1.setEviScore(145);

    MasterEnrollment masterCommittee;

    masterCommittee.printRequirements();

    if (masterCommittee.checkEligibility(s1)) {
        std::cout << "\nCongratulations! You can proceed to document submission." << std::endl;
    }
    else {
        std::cout << "\nWe are sorry. Please try again next year." << std::endl;
    }

    return 0;
}