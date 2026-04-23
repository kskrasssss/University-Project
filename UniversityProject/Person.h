#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;

public:
    Person(string n, int a);
    virtual ~Person();

    virtual string getAge() const;
    string getName() const;
};
#endif