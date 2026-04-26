#include "MasterEnrollment.h"
#include <iostream>

bool MasterEnrollment::checkEligibility(const Student& student) const {
    // “ут в будущем напишем логику (баллы > 150 и т.д.)
    return true;
}

void MasterEnrollment::printRequirements() const {
    std::cout << "Requirements: Bachelor degree + EVI exam results.\n";
}