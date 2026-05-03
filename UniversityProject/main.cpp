#include <iostream>
#include <memory>
#include <string>
#include <limits>
#include "UniversityManager.h"
#include "Student.h"
#include "ValidationException.h"

const std::string ADMIN_PASS = "admin123";
const int MAX_LOGIN_ATTEMPTS = 3;

// ќчищаЇмо cin п≥сл€ некоректного вводу
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void showAdminMenu() {
    std::cout << "\n--- Admin Panel ---\n"
        << "1. Add new student\n"
        << "2. Set student EVI score\n"
        << "3. Set student degrees/publications\n"
        << "4. View all students\n"
        << "5. Save data to file\n"
        << "6. View action history\n"
        << "0. Back to main menu\n";
}

void showUserMenu() {
    std::cout << "\n--- Guest Menu ---\n"
        << "1. View students list\n"
        << "2. View admission programs\n"
        << "3. Check my eligibility\n"
        << "4. View action history\n"
        << "0. Back to main menu\n";
}

void runAdminSession(UniversityManager& uni) {
    int action = -1;
    while (action != 0) {
        showAdminMenu();
        std::cout << "Action: ";
        if (!(std::cin >> action)) { clearInput(); continue; }

        try {
            if (action == 1) {
                std::string name, id;
                int age;
                std::cout << "Enter name: "; std::cin >> name;
                std::cout << "Enter age: ";
                if (!(std::cin >> age)) { clearInput(); throw ValidationException("Age must be a number"); }
                std::cout << "Enter student ID: "; std::cin >> id;
                uni.addStudent(std::make_shared<Student>(name, age, id));
                std::cout << "Student added.\n";
            }
            else if (action == 2) {
                std::string id; int score;
                std::cout << "Enter student ID: "; std::cin >> id;
                std::cout << "Enter EVI score (0-200): ";
                if (!(std::cin >> score)) { clearInput(); throw ValidationException("Score must be a number"); }

                bool found = false;
                for (auto& s : uni.getStudents()) {
                    if (s->getStudentID() == id) {
                        s->setEviScore(score); // кидаЇ ValidationException €кщо поза межами
                        std::cout << "EVI score updated.\n";
                        uni.getLogger().log("admin", "Set EVI=" + std::to_string(score) + " for " + id);
                        found = true; break;
                    }
                }
                if (!found) std::cout << "Student not found.\n";
            }
            else if (action == 3) {
                std::string id; int b, m, p;
                std::cout << "Enter student ID: "; std::cin >> id;
                std::cout << "Has Bachelor? (1/0): "; std::cin >> b;
                std::cout << "Has Master?   (1/0): "; std::cin >> m;
                std::cout << "Has Publications? (1/0): "; std::cin >> p;

                bool found = false;
                for (auto& s : uni.getStudents()) {
                    if (s->getStudentID() == id) {
                        s->setBachelor(b); s->setMaster(m); s->setPublications(p);
                        std::cout << "Degrees updated.\n";
                        uni.getLogger().log("admin", "Updated degrees for " + id);
                        found = true; break;
                    }
                }
                if (!found) std::cout << "Student not found.\n";
            }
            else if (action == 4) {
                const auto& students = uni.getStudents();
                if (students.empty()) { std::cout << "No students yet.\n"; }
                else for (const auto& s : students) s->displayInfo();
            }
            else if (action == 5) {
                uni.saveToDatabase();
            }
            else if (action == 6) {
                uni.showHistory();
            }
        }
        catch (const ValidationException& e) {
            std::cout << "Input error: " << e.what() << "\n";
            clearInput();
        }
        catch (const std::exception& e) {
            std::cout << "Unexpected error: " << e.what() << "\n";
            clearInput();
        }
    }
}

void runUserSession(UniversityManager& uni) {
    int action = -1;
    while (action != 0) {
        showUserMenu();
        std::cout << "Action: ";
        if (!(std::cin >> action)) { clearInput(); continue; }

        try {
            if (action == 1) {
                const auto& students = uni.getStudents();
                if (students.empty()) std::cout << "No students in database.\n";
                else for (const auto& s : students) s->displayInfo();
                uni.getLogger().log("user", "Viewed students list");
            }
            else if (action == 2) {
                for (const auto& p : uni.getPrograms()) p->displayInfo();
                uni.getLogger().log("user", "Viewed admission programs");
            }
            else if (action == 3) {
                std::string name, id; int age;
                std::cout << "Your name: "; std::cin >> name;
                std::cout << "Your age: ";
                if (!(std::cin >> age)) { clearInput(); throw ValidationException("Age must be a number"); }
                std::cout << "Your student ID: "; std::cin >> id;

                Student temp(name, age, id);
                std::cout << "Set your EVI score (0-200): ";
                int evi; std::cin >> evi;
                temp.setEviScore(evi);

                int b, m, p;
                std::cout << "Have Bachelor? (1/0): "; std::cin >> b; temp.setBachelor(b);
                std::cout << "Have Master?   (1/0): "; std::cin >> m; temp.setMaster(m);
                std::cout << "Have Publications? (1/0): "; std::cin >> p; temp.setPublications(p);

                std::cout << "\n--- Eligibility Results ---\n";
                for (const auto& prog : uni.getPrograms()) {
                    prog->checkEligibility(temp);
                }
                uni.getLogger().log("user", name + " checked eligibility");
            }
            else if (action == 4) {
                uni.showHistory();
            }
        }
        catch (const ValidationException& e) {
            std::cout << "Input error: " << e.what() << "\n";
            clearInput();
        }
    }
}

int main() {
    // unique_ptr: UniversityManager is exclusively owned by main
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

        try {
            if (roleChoice == 1) {
                int attempts = 0;
                bool authenticated = false;

                // Req #3 Ч пароль + lockout п≥сл€ 3 спроб
                while (attempts < MAX_LOGIN_ATTEMPTS) {
                    std::string pass;
                    std::cout << "Password (" << (MAX_LOGIN_ATTEMPTS - attempts) << " attempts left): ";
                    std::cin >> pass;

                    if (pass == ADMIN_PASS) {
                        authenticated = true;
                        university->getLogger().log("admin", "Logged in");
                        break;
                    }
                    attempts++;
                    std::cout << "Wrong password.\n";
                }

                if (authenticated) runAdminSession(*university);
                else std::cout << "Account locked. Too many failed attempts.\n";
            }
            else if (roleChoice == 2) {
                university->getLogger().log("user", "Guest session started");
                runUserSession(*university);
            }
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
            clearInput();
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}