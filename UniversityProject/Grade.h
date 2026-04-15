#ifndef GRADE_H
#define GRADE_H

#include <string>
using namespace std;

struct Grade {
    string subject;
    int score;

    Grade(string sub, int sc) : subject(sub), score(sc) {}
};

#endif