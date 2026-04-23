#ifndef GRADE_H
#define GRADE_H

#include <string>
using namespace std;

class Graduate {
public:
    virtual string getDegree() const = 0;
    virtual ~Graduate() {}
};
#endif