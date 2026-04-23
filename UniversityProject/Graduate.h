#ifndef GRADE_H
#define GRADE_H

#include <string>
using namespace std;

struct Graduate {
    string subject;
    int score;

    Graduate(string sub, int sc) : subject(sub), score(sc) {}
};

#endif