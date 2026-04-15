#ifndef PERSON_H
#define PERSON_H
#include <string>

using namespace std;

class Person {
protected:
    string name;
    int age;
public:
    Person(string n = "None", int a = 0);
    virtual ~Person();
    void info() const;
};
#endif
