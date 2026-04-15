#include "PostgraduateStudent.h"
#include <iostream>

PostgraduateStudent::PostgraduateStudent(string n, int a, string id, string topic)
    : Student(n, a, id), thesisTopic(topic) {
}

void PostgraduateStudent::displayInfo() const {
    cout << "Postgrad: " << getName() << " | Thesis: " << thesisTopic << endl;
}