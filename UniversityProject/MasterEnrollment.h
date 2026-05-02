#pragma once
#include "Enrollment.h"

class MasterEnrollment : public Enrollment {
public:
    bool checkEligibility(const Student& student) const override;
    void printRequirements() const override;
};