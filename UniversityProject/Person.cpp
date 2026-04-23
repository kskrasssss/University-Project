#include "Person.h"
#include <iostream>

Person::Person(string n, int a) : name(n), age(a) {}

Person::~Person() {}

string Person::getAge() const {
    return to_string(age);
}

string Person::getName() const {
    return name;
}