#include "Student.h"
#include <utility>

Student::Student(string n, int a, string id) : Person(n, a), studentID(id) {
    grades = new vector<Grade>();
}

Student::Student(const Student& other) : Person(other), studentID(other.studentID) {
    grades = new vector<Grade>(*other.grades);
}

Student::Student(Student&& other) noexcept
    : Person(move(other)), studentID(move(other.studentID)), grades(other.grades) {
    other.grades = nullptr;
}

Student& Student::operator=(const Student& rhs) {
    if (this == &rhs) return *this;
    Person::operator=(rhs);
    delete grades;
    studentID = rhs.studentID;
    grades = new vector<Grade>(*rhs.grades);
    return *this;
}

void Student::addGrade(string sub, int sc) {
    if (grades) grades->push_back(Grade(sub, sc));
}

int Student::getGradesCount() const {
    return (grades != nullptr) ? (int)grades->size() : 0;
}

bool Student::isGradesEmpty() const {
    return grades == nullptr;
}

Student::~Student() {
    delete grades;
}