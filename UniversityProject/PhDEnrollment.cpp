#include "PhDEnrollment.h"
#include <iostream>

bool PhDEnrollment::checkEligibility(const Student& student) const {
    return true;
}

void PhDEnrollment::printRequirements() const {
    std::cout << "PhD requirements\n";
}