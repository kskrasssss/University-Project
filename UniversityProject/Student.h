#pragma once
#include "Person.h"
#include "Graduate.h"
#include "ValidationException.h"
#include <vector>

class Student : public Person {
private:
    int eviScore;
    bool hasBachelor;
    bool hasMaster;
    bool hasPublications;
    std::string studentID;
    std::vector<int> grades;

public:
    Student(std::string n, int a, std::string id);
    Student(const Student& other);
    Student(Student&& other) noexcept;
    Student& operator=(const Student& other);
    virtual ~Student();

    void addGrade(int grade);
    int getGradesCount() const;

    // Тепер кидає ValidationException якщо score поза межами
    void setEviScore(int score);
    int getEviScore() const;

    void setBachelor(bool status);
    bool getHasBachelor() const;
    void setMaster(bool status);
    bool getHasMaster() const;
    void setPublications(bool status);
    bool getHasPublications() const;
    std::string getStudentID() const { return studentID; }

    void showType() { std::cout << "Type: STUDENT (Static)" << std::endl; }
};