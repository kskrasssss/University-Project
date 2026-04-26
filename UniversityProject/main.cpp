#include <iostream>
#include <vector>
#include "Student.h"
#include "MasterEnrollment.h"
#include "PhDEnrollment.h"

void process(const Enrollment& e, const Student& s) {
    e.printRequirements();
    e.checkEligibility(s);
}

int main() {
    Student s1("Kateryna", 21, "ST-777");
    s1.setBachelor(true);
    s1.setEviScore(175);
    s1.setPublications(true);

    std::cout << "[Step 1: Static Binding Demo]" << std::endl;
    Person* pPtr = &s1;
    // Навіть якщо там Студент, викличеться метод Person, бо немає virtual
    pPtr->showType();

    std::cout << "\n[Step 8: Interface Demo]" << std::endl;
    IDisplayable* infoList[2];
    infoList[0] = &s1; // Людина
    infoList[1] = new MasterEnrollment(); // Процес вступу

    for (int i = 0; i < 2; i++) {
        infoList[i]->displayInfo(); // Однаковий виклик для різних світів
    }

    //Поліморфізм через вказівник та посилання
    std::cout << "\n[Step 3 & 6: Pointers and References Demo]" << std::endl;
    std::vector<Enrollment*> universityPrograms;
    universityPrograms.push_back(new MasterEnrollment());
    universityPrograms.push_back((Enrollment*)infoList[1]); // Використаємо вже створений
    universityPrograms.push_back(new PhDEnrollment());

    for (Enrollment* program : universityPrograms) {
		// Виклик через посилання на базовий клас, але виконується код похідного завдяки virtual
        process(*program, s1);
        std::cout << "----------------------------------------" << std::endl;
    }

    // Очищення віртуальними деструкторами
    delete universityPrograms[0];
    delete universityPrograms[2];
    delete infoList[1];

    return 0;
}