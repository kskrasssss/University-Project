#include <iostream>
#include <memory>
#include <string>
#include <limits>
#include "UniversityManager.h"
#include "Student.h"
#include "ValidationException.h"

const std::string ADMIN_PASS = "admin123";
const int MAX_LOGIN_ATTEMPTS = 3;

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void showAdminMenu() {
    std::cout << "\n--- Admin Panel ---\n"
        << "1. Add new student\n"
        << "2. Set student EVI score\n"       // Ќќ¬≈ Ч req #4
        << "3. Set student degrees\n"          // Ќќ¬≈ Ч req #4
        << "4. View all students\n"            // Ќќ¬≈
        << "5. Save data to file\n"
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
            // Req #8 Ч логуЇмо додаванн€ студента
            uni.getLogger().log("admin", "Added student: " + name);
            std::cout << "Student added.\n";
        }
        // Ќќ¬≈ Ч Req #4: встановити EVI score
        else if (action == 2) {
            std::string id; int score;
            std::cout << "Student ID: "; std::cin >> id;
            std::cout << "EVI score (0-200): ";
            if (!(std::cin >> score)) { clearInput(); continue; }

            bool found = false;
            for (auto& s : uni.getStudents()) {
                if (s->getStudentID() == id) {
                    try {
                        s->setEviScore(score);
                        uni.getLogger().log("admin", "Set EVI=" + std::to_string(score) + " for " + id);
                        std::cout << "EVI updated.\n";
                    }
                    catch (const ValidationException& e) {
                        std::cout << e.what() << "\n";
                    }
                    found = true; break;
                }
            }
            if (!found) std::cout << "Student not found.\n";
        }
        // Ќќ¬≈ Ч Req #4: встановити ступен≥ та публ≥кац≥њ
        else if (action == 3) {
            std::string id; int b, m, p;
            std::cout << "Student ID: ";          std::cin >> id;
            std::cout << "Has Bachelor? (1/0): "; std::cin >> b;
            std::cout << "Has Master?   (1/0): "; std::cin >> m;
            std::cout << "Publications? (1/0): "; std::cin >> p;

            bool found = false;
            for (auto& s : uni.getStudents()) {
                if (s->getStudentID() == id) {
                    s->setBachelor(b); s->setMaster(m); s->setPublications(p);
                    // Req #8 Ч логуЇмо зм≥ну ступен≥в
                    uni.getLogger().log("admin", "Updated degrees for " + id);
                    std::cout << "Degrees updated.\n";
                    found = true; break;
                }
            }
            if (!found) std::cout << "Student not found.\n";
        }
        // Ќќ¬≈ Ч перегл€нути вс≥х студент≥в
        else if (action == 4) {
            const auto& students = uni.getStudents();
            if (students.empty()) std::cout << "No students yet.\n";
            else for (const auto& s : students) s->displayInfo();
        }
        else if (action == 5) {
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
                university->getLogger().log("admin", "Logged in");
                runAdminSession(*university);
            }
            else {
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