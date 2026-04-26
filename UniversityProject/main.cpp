#include <iostream>
#include <vector>
#include "Student.h"
#include "MasterEnrollment.h"
#include "PhDEnrollment.h"

//void process(const Enrollment& e, const Student& s) {
//    e.printRequirements();
//    e.checkEligibility(s);
//}

int main() {
    Student s1("Kateryna", 21, "ST-777");
    s1.setBachelor(true);
    s1.setMaster(false);
    s1.setEviScore(175);
    s1.setPublications(true);

    std::vector<Enrollment*> universityPrograms;

    universityPrograms.push_back(new MasterEnrollment());
    universityPrograms.push_back(new PhDEnrollment());

    std::cout << "--- UNIVERSITY ADMISSION SYSTEM START ---" << std::endl;

    //ПОЛІМОРФНИЙ ЦИКЛ
    for (Enrollment* program : universityPrograms) {
        // Для кожного вказівника р(типу Enrollment), який лежить у контейнері programs, зроби:
        program->printRequirements();

        if (program->checkEligibility(s1)) {
            std::cout << ">>> Decision: You are eligible for this program!" << std::endl;
        }
        else {
            std::cout << ">>> Decision: Sorry, you do not meet the criteria." << std::endl;
        }
        std::cout << "----------------------------------------" << std::endl;
    }

    //Очищення пам'яті
    for (Enrollment* program : universityPrograms) {
        delete program;
    }

    return 0;
}