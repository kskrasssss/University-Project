#include "PostgraduateStudent.h"
#include <iostream>

PostgraduateStudent::PostgraduateStudent(string n, int a, string id, string topic)
    : Student(n, a, id), thesisTopic(topic) {
    // thesisTopic для збервг. теми наук. роботи
}

void PostgraduateStudent::displayInfo() const {
    cout << "Postgrad: " << getAge() << " | Thesis: " << thesisTopic << endl;
}