#ifndef PERSON_H
#define PERSON_H
#include "IDisplayable.h"
#include <string>
using namespace std;

class Person : public IDisplayable { 
protected:
    string name;
    int age;

public:
    Person(string n, int a);
    virtual ~Person();

    virtual string getAge() const;
    string getName() const;
    void showType() { cout << "Object Type: Person" << endl; } // ¹1: ÑÒÀÒÈ×ÍÀ ïðèâ'ÿçêà (íåìàº virtual)
    void displayInfo() const override { cout << "Person: " << name << endl; } // ¹8: Ðåàë³çàö³ÿ
};

#endif