#include "Student.h"

// Конструктор инициализации
Student::Student(string n, int a, string id)
    : Person(n, a), studentID(id), eviScore(0), hasBachelor(false), hasMaster(false), hasPublications(false) {
}

// Конструктор копирования (Deep Copy для вектора делается автоматически самим вектором)
Student::Student(const Student& other)
    : Person(other), studentID(other.studentID), grades(other.grades) {
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
    return static_cast<int>(grades.size());
}




void Student::setEviScore(int score) {
    if (score >= 0 && score <= 200) {
        eviScore = score;
    }
}

int Student::getEviScore() const {
    return eviScore;
}



void Student::setBachelor(bool status) {
	hasBachelor = status;   
}

bool Student::getHasBachelor() const {
    return hasBachelor;
}



void Student::setMaster(bool status) {
    hasMaster = status;
}

bool Student::getHasMaster() const {
    return hasMaster;
}