#include "Student.h"
#include <iostream>
#include <utility> // для move

using namespace std;

Student::Student(string n, int a, string id)
    : Person(n, a), studentID{ id } {
    grades = new vector<Grade>();
}

// Deep Copy
Student::Student(const Student& other)
    : Person(other), studentID{ other.studentID } {
    grades = new vector<Grade>(*other.grades);
}

// Move Constructor
Student::Student(Student&& other) noexcept
    : Person(move(other)), studentID{ move(other.studentID) }, grades{ other.grades } {
    other.grades = nullptr;
}

// Operator=
Student& Student::operator=(const Student& rhs) {
    if (this == &rhs) return *this;
    Person::operator=(rhs);
    delete grades;
    studentID = rhs.studentID;
    grades = new vector<Grade>(*rhs.grades);
    return *this;
}

void Student::addGrade(string sub, int sc) {
    grades->push_back(Grade(sub, sc));
}

Student::~Student() {
    delete grades;
}

int Student::getGradesCount() const {
    if (grades == nullptr) return 0;
    return (int)grades->size();
}

bool Student::isGradesEmpty() const {
    return grades == nullptr;
}