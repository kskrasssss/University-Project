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
    string getName() const;
    virtual string getAge() const;
    Person& operator=(const Person& other);
    // ми змінюємо поведінку оператора присвоєння, копіюємо з (const Person& other). Перед operator= це те, що функція поверне, тобто посилання на себе ж
};

#endif