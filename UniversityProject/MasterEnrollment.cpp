#include "MasterEnrollment.h"
#include <iostream>

bool MasterEnrollment::checkEligibility(const Student& student) {
    return true;
}

void MasterEnrollment::printRequirements() const {
    std::cout << "Master requirements\n";
}