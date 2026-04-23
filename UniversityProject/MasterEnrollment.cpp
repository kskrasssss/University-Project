#include "MasterEnrollment.h"
#include <iostream>

bool MasterEnrollment::checkEligibility(const Student& student) {
    return true;
}

void MasterEnrollment::printRequirements() const {
    std::cout << "Master requirements:\n";
    std::cout << "- Bachelor diploma required\n";
    std::cout << "- EVI/EFVV exams required\n";
}