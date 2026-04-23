#ifndef STUDENT_H
#define STUDENT_H

#pragma once
#include "Person.h"
#include "Graduate.h"
#include <vector>

class Student : public Person {
private:
    string studentID;
    vector<int> grades;

public:
    Student(string n, int a, string id);
    Student(const Student& other);
    Student(Student&& other) noexcept;
    Student& operator=(const Student& other);
    virtual ~Student();

    void addGrade(int grade);
    int getGradesCount() const;
};

#endif