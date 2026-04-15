#ifndef GRADE_H
#define GRADE_H

#include <string>

struct Grade {
    std::string subject;
    int score;

    Grade(std::string sub, int sc) : subject(sub), score(sc) {}
};

#endif