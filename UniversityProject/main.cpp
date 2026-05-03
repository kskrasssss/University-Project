#include <iostream>
#include <memory>
#include <string>
#include <limits>
#include "UniversityManager.h"
#include "Student.h"
#include "ValidationException.h"

// Req #3 Ч пароль винесено в константу (не хардкод всередин≥ функц≥њ)
const std::string ADMIN_PASS = "admin123";
const int MAX_LOGIN_ATTEMPTS = 3;

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void showAdminMenu() {
    std::cout << "\n--- Admin Panel ---\n"
        << "1. Add new student\n"
        << "2. Save data to file\n"
        << "0. Back\n";
}

void showUserMenu() {
    std::cout << "\n--- Guest Menu ---\n"
        << "1. View students list\n"
        << "2. View admission programs\n"
        << "0. Back\n";
}

void runAdminSession(UniversityManager& uni) {
    int action = -1;
    while (action != 0) {
        showAdminMenu();
        std::cout << "Action: ";
        if (!(std::cin >> action)) { clearInput(); continue; }

        if (action == 1) {
            std::string name, id; int age;
            std::cout << "Name: ";       std::cin >> name;
            std::cout << "Age: ";        std::cin >> age;
            std::cout << "Student ID: "; std::cin >> id;
            uni.addStudent(std::make_shared<Student>(name, age, id));
            std::cout << "Student added.\n";
        }
        else if (action == 2) {
            uni.saveToDatabase();
        }
    }
}

void runUserSession(UniversityManager& uni) {
    int action = -1;
    while (action != 0) {
        showUserMenu();
        std::cout << "Action: ";
        if (!(std::cin >> action)) { clearInput(); continue; }

        if (action == 1) {
            const auto& students = uni.getStudents();
            if (students.empty()) std::cout << "No students.\n";
            else for (const auto& s : students) s->displayInfo();
        }
        else if (action == 2) {
            for (const auto& p : uni.getPrograms()) p->displayInfo();
        }
    }
}

int main() {
    // unique_ptr: ун≥верситет належить т≥льки main()
    auto university = std::make_unique<UniversityManager>();
    university->loadFromDatabase();

    int roleChoice = -1;
    while (roleChoice != 0) {
        std::cout << "\n=== University Admission System ===\n"
            << "1. Login as Admin\n"
            << "2. Continue as Guest\n"
            << "0. Exit\n"
            << "Select: ";

        if (!(std::cin >> roleChoice)) { clearInput(); continue; }

        if (roleChoice == 1) {
            // Req #3 Ч л≥чильник спроб, lockout п≥сл€ MAX_LOGIN_ATTEMPTS
            int attempts = 0;
            bool authenticated = false;

            while (attempts < MAX_LOGIN_ATTEMPTS) {
                std::string pass;
                std::cout << "Password (" << (MAX_LOGIN_ATTEMPTS - attempts) << " attempts left): ";
                std::cin >> pass;
                if (pass == ADMIN_PASS) { authenticated = true; break; }
                attempts++;
                std::cout << "Wrong password.\n";
            }

            if (authenticated) {
                runAdminSession(*university);
            }
            else {
                // Req #3 Ч lockout пов≥домленн€
                std::cout << "Locked out. Too many failed attempts.\n";
            }
        }
        else if (roleChoice == 2) {
            runUserSession(*university);
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}