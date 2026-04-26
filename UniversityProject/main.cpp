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


	Student s2("Oleh", 25, "ST-02");

	s2.setMaster(true);
	s2.setPublications(false);
	s2.setEviScore(185);

    PhDEnrollment phdOffice;
    phdOffice.printRequirements();

    if (!phdOffice.checkEligibility(s2)) {
        std::cout << "\nOleh, you need to publish a research paper first!" << std::endl;
        std::cout << "--- Publishing paper in 'Nature'... ---" << std::endl;
        s2.setPublications(true);

        phdOffice.checkEligibility(s2);
    }
    return 0;
}