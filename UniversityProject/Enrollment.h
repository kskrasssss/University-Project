#pragma once
#include "Student.h"
#include "IDisplayable.h"

class Enrollment : public IDisplayable { // Теж наслідуємо інтерфейс
public:
    virtual ~Enrollment() {}
    void displayInfo() const override { cout << "Admission Logic Object" << endl; }

    virtual bool checkEligibility(const Student& student) const = 0;
    virtual void printRequirements() const = 0;
};