#include "Person.h"
#include <iostream>

using namespace std;

Person::Person(string n, int a) : name{ n }, age{ a } {
    cout << "Constructor Person [" << name << "]\n";
}

Person::~Person() {
    cout << "Destructor Person [" << name << "]\n";
}

void Person::info() const {
    cout << "Name: " << name << ", Age: " << age << endl;
}
