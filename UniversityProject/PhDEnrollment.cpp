#include "PhDEnrollment.h"
#include <iostream>

void PhDEnrollment::printRequirements() const {
    std::cout << "\n****************************************" << std::endl;
    std::cout << "PHD ADMISSION REQUIREMENTS (SCIENTIFIC LEVEL):" << std::endl;
    std::cout << " 1. Master's Degree: MANDATORY" << std::endl;
    std::cout << " 2. Scientific Publications: REQUIRED" << std::endl;
    std::cout << " 3. Minimum EVI Score: 170" << std::endl;
    std::cout << "****************************************" << std::endl;
}

bool PhDEnrollment::checkEligibility(const Student& student) const {
    std::cout << "\n[PhD Committee] Evaluating candidate: " << student.getName() << "..." << std::endl;

    bool master = student.getHasMaster();
    bool papers = student.getHasPublications();
    int score = student.getEviScore();

    if (master && papers && score >= 170) {
        std::cout << ">>> VERDICT: ADMITTED to PhD program. Welcome to science!" << std::endl;
        return true;
    }
    else {
        std::cout << ">>> VERDICT: REJECTED." << std::endl;

        if (!master) std::cout << " - Missing Master's Degree." << std::endl;
        if (!papers) std::cout << " - No scientific publications found." << std::endl;
        if (score < 170) std::cout << " - EVI score " << score << " is below PhD threshold (170)." << std::endl;

        return false;
    }
}