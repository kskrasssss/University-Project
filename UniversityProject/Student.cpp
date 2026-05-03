#include "Student.h"
#include <iostream>

Student::Student(std::string n, int a, std::string id)
    : Person(n, a), studentID(id), eviScore(0),
    hasBachelor(false), hasMaster(false), hasPublications(false) {
}

Student::Student(const Student& other)
    : Person(other), studentID(other.studentID), grades(other.grades),
    eviScore(other.eviScore), hasBachelor(other.hasBachelor),
    hasMaster(other.hasMaster), hasPublications(other.hasPublications) {
}

// БАГ ВИПРАВЛЕНО: прибрано [other.name](http://other.name)
Student::Student(Student&& other) noexcept
    : Person(other.name, other.age),
    studentID(std::move(other.studentID)),
    grades(std::move(other.grades)),
    eviScore(other.eviScore),
    hasBachelor(other.hasBachelor),
    hasMaster(other.hasMaster),
    hasPublications(other.hasPublications) {
}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        name = other.name;
        age = other.age;
        studentID = other.studentID;
        grades = other.grades;
        eviScore = other.eviScore;
        hasBachelor = other.hasBachelor;
        hasMaster = other.hasMaster;
        hasPublications = other.hasPublications;
    }
    return *this;
}

Student::~Student() {}

void Student::addGrade(int grade) { grades.push_back(grade); }
int Student::getGradesCount() const { return static_cast<int>(grades.size()); }

// Кидає ValidationException замість мовчазного ігнорування
void Student::setEviScore(int score) {
    if (score < 0 || score > 200)
        throw ValidationException("EVI score must be between 0 and 200, got: " + std::to_string(score));
    eviScore = score;
}

int Student::getEviScore() const { return eviScore; }
void Student::setBachelor(bool status) { hasBachelor = status; }
bool Student::getHasBachelor() const { return hasBachelor; }
void Student::setMaster(bool status) { hasMaster = status; }
bool Student::getHasMaster() const { return hasMaster; }
void Student::setPublications(bool status) { hasPublications = status; }
bool Student::getHasPublications() const { return hasPublications; }