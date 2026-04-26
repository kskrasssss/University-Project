#include "MasterEnrollment.h"
#include <iostream>
using namespace std;

bool MasterEnrollment::checkEligibility(const Student& student) const {
    cout << "\n Master`s Admission Committee is checking: " << student.getName();

	bool hasBachelor = student.getHasBachelor();
	int eviScore = student.getEviScore();

    if (hasBachelor && eviScore >= 130) {
        cout << "[SUCCESS] Bachelor degree found. EVI score " << eviScore << " is sufficient.";
        return true;
    }
    else {
        cout << "[DENIED] Eligibility criteria not met. " << endl;
        if (!hasBachelor) {
            cout << " - Bachelor degree is missing." << endl;
		}
        if (eviScore < 130) {
            cout << " - EVI score " << eviScore << " is below the required threshold of 130." << endl;
        }
		return false;
    }


}

void MasterEnrollment::printRequirements() const {
    cout << "========================================" << std::endl;
    cout << "OFFICIAL MASTER'S REQUIREMENTS 2026:" << std::endl;
    cout << " - Must hold a Bachelor's degree." << std::endl;
    cout << " - Minimum EVI (TZNK + Language) score: 130." << std::endl;
    cout << "========================================" << std::endl;
}