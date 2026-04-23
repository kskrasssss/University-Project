#pragma once
#include "Student.h"

class Enrollment {
public:
    virtual bool checkEligibility(const Student& student) = 0;
    virtual void printRequirements() const = 0;

    virtual ~Enrollment() {}
};