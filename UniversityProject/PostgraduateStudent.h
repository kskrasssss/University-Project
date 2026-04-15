#ifndef POSTGRADUATE_STUDENT_H
#define POSTGRADUATE_STUDENT_H

#include "Student.h"
#include <string>

class PostgraduateStudent : public Student {
private:
    std::string thesisTopic;

public:
    PostgraduateStudent(std::string n, int a, std::string id, std::string topic);

    // Ми можемо використовувати конструктори копіювання/перенесення від Student
    // Якщо ми не виділяємо нову динамічну пам'ять тут, дефолтні спрацюють ок

    void displayInfo() const;
};

#endif