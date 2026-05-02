#include <iostream>
#include <memory>
#include "UniversityManager.h"

int main() {
    // Головний об'єкт - автоматично видалиться, коли програма завершиться
    std::unique_ptr<UniversityManager> university = std::make_unique<UniversityManager>();

    std::cout << "--- University Admission System Loaded ---" << std::endl;



    return 0;
}