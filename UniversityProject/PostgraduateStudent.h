#ifndef POSTGRADUATE_H
#define POSTGRADUATE_H

#include "Student.h"

class PostgraduateStudent : public Student {
private:
    string thesisTopic;

public:
    PostgraduateStudent(string n, int a, string id, string topic);
    void displayInfo() const;
    string getAge() const override;
};

#endif