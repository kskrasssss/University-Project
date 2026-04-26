#pragma once
#include "Enrollment.h"

class PhDEnrollment final : public Enrollment {
public:
    bool checkEligibility(const Student& student) const override;
    void printRequirements() const override;
};