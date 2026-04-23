#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include "Graduate.h"
#include <vector>

class Student : public Person {
private:
    string studentID;
    vector<Graduate>* grades;

public:
    Student(string n, int a, string id);
    Student(const Student& other);
    Student(Student&& other) noexcept;
    Student& operator=(const Student& rhs);
    virtual ~Student();
    virtual string getAge() const override;

    void addGrade(string sub, int sc);
    int getGradesCount() const;
    bool isGradesEmpty() const;
};

#endif