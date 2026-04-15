#include "Person.h"
#include <iostream>

Person::Person(string n, int a) : name(n), age(a) {
    cout << "Constructor Person [" << name << "]" << endl;
}

Person::~Person() {
    cout << "Destructor Person [" << name << "]" << endl;
}

string Person::getName() const {
    return name;
}

Person& Person::operator=(const Person& other) {
    if (this != &other) {
        name = other.name;
        age = other.age;
    }
    return *this;
}