#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include "Grade.h"
#include <vector>
#include <string>

class Student : public Person {
private:
    std::string studentID;
    std::vector<Grade>* grades;

public:
    Student(std::string n, int a, std::string id);

    // Копіювання та перенесення
    Student(const Student& other);
    Student(Student&& other) noexcept;
    Student& operator=(const Student& rhs);

    void addGrade(std::string sub, int sc);
    ~Student();

	// Testing methods
    int getGradesCount() const;
    bool isGradesEmpty() const;

    std::string getName() const { return name; }
};

#endif