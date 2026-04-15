#include <iostream>
#include <utility>
#include "PostgraduateStudent.h"

using namespace std;

int main() {
    cout << " Testing Student and Deep Copy" << endl;
    Student s1("Kateryna", 19, "ST-2024");
    s1.addGrade("C++", 100);

    Student s2 = s1;
    s2.addGrade("Math", 95);

    cout << "S1 grades: " << s1.getGradesCount() << endl;
    cout << "S2 grades: " << s2.getGradesCount() << endl;

    cout << "\n Testing Move Semantics" << endl;
    Student s3 = move(s2);
    cout << "S3 (moved) name: " << s3.getName() << endl;

    cout << "\n Testing Inheritance" << endl;
    PostgraduateStudent pg("Alex", 25, "PHD-77", "AI Systems");
    pg.addGrade("Research", 99);
    pg.displayInfo();

    cout << "\n End of Program" << endl;
    return 0;
}