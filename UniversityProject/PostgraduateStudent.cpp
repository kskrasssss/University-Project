#include "PostgraduateStudent.h"
#include <iostream>

PostgraduateStudent::PostgraduateStudent(std::string n, int a, std::string id, std::string topic)
    : Student(n, a, id), thesisTopic(topic) {
}

void PostgraduateStudent::displayInfo() const {
    std::cout << "Postgraduate Student: " << getName() << "\nTopic: " << thesisTopic << std::endl;
}