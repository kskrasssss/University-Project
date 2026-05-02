#ifndef UNIVERSITY_MANAGER_H
#define UNIVERSITY_MANAGER_H

#include <vector>
#include <memory>
#include <string>
#include "Student.h"
#include "Enrollment.h"
#include "MasterEnrollment.h"
#include "PhDEnrollment.h"

class UniversityManager {
private:
    // Використовуємо shared_ptr, бо студенти можуть належати кільком спискам
    std::vector<std::shared_ptr<Student>> allStudents;

    // Використовуємо unique_ptr, бо програми вступу належать тільки менеджеру
    std::vector<std::unique_ptr<Enrollment>> admissionPrograms;

public:
    UniversityManager() {
        // Ініціалізуємо програми вступу за допомогою make_unique (C++14)
        admissionPrograms.push_back(std::make_unique<MasterEnrollment>());
        admissionPrograms.push_back(std::make_unique<PhDEnrollment>());
    }

    // Метод для адміна: додати студента
    void addStudent(std::shared_ptr<Student> student) {
        allStudents.push_back(student);
    }

    // Метод для користувача: отримати список студентів
    const std::vector<std::shared_ptr<Student>>& getStudents() const {
        return allStudents;
    }

    // Отримати доступ до програм для перевірки
    const std::vector<std::unique_ptr<Enrollment>>& getPrograms() const {
        return admissionPrograms;
    }
};

#endif