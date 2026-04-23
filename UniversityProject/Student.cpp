#include "Student.h"

Student::Student(string n, int a, string id)
    : Person(n, a), studentID(id) {
}

Student::Student(const Student& other)
    : Person(other.name, other.age), studentID(other.studentID), grades(other.grades) {
}

Student::Student(Student&& other) noexcept
    : Person(other.name, other.age), studentID(other.studentID), grades(move(other.grades)) {
}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        name = other.name;
        age = other.age;
        studentID = other.studentID;
        grades = other.grades;
    }
    return *this;
}

Student::~Student() {}

void Student::addGrade(int grade) {
    grades.push_back(grade);
}

int Student::getGradesCount() const {
    return grades.size();
}