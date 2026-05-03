#pragma once
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Student.h"
#include "Enrollment.h"
#include "MasterEnrollment.h"
#include "PhDEnrollment.h"
#include "ActionLogger.h"
#include "ValidationException.h"

class UniversityManager {
private:
    // shared_ptr: students can appear in multiple filtered lists
    std::vector<std::shared_ptr<Student>> allStudents;

    // unique_ptr: admission programs are exclusively owned by this manager
    std::vector<std::unique_ptr<Enrollment>> admissionPrograms;

    // unique_ptr: the logger belongs solely to this manager instance
    std::unique_ptr<ActionLogger> logger;

    const std::string DB_FILE = "students.txt";

public:
    UniversityManager()
        : logger(std::make_unique<ActionLogger>("history.txt"))
    {
        admissionPrograms.push_back(std::make_unique<MasterEnrollment>());
        admissionPrograms.push_back(std::make_unique<PhDEnrollment>());
    }

    void addStudent(std::shared_ptr<Student> student) {
        allStudents.push_back(student);
        logger->log("admin", "Added student: " + student->getName());
    }

    const std::vector<std::shared_ptr<Student>>& getStudents() const {
        return allStudents;
    }

    const std::vector<std::unique_ptr<Enrollment>>& getPrograms() const {
        return admissionPrograms;
    }

    ActionLogger& getLogger() { return *logger; }

    // Req #6, #7 Ч збер≥гаЇмо у файл CSV-формату
    void saveToDatabase() {
        try {
            std::ofstream file(DB_FILE);
            if (!file.is_open())
                throw std::ios_base::failure("Cannot open file for writing: " + DB_FILE);

            for (const auto& s : allStudents) {
                // ‘ормат: name,age,id,evi,bachelor,master,publications
                file << s->getName() << ","
                    << s->getAge() << ","
                    << s->getStudentID() << ","
                    << s->getEviScore() << ","
                    << s->getHasBachelor() << ","
                    << s->getHasMaster() << ","
                    << s->getHasPublications() << "\n";
            }
            std::cout << "Data saved successfully." << std::endl;
            logger->log("admin", "Saved " + std::to_string(allStudents.size()) + " students to database");
        }
        catch (const std::ios_base::failure& e) {
            std::cerr << "Error saving data: " << e.what() << std::endl;
        }
    }

    // Req #7 Ч завантажуЇмо при старт≥, дан≥ не губл€тьс€
    void loadFromDatabase() {
        try {
            std::ifstream file(DB_FILE);
            if (!file.is_open()) {
                std::cout << "No saved data found. Starting fresh." << std::endl;
                return;
            }

            allStudents.clear();
            std::string line;
            int lineNum = 0;

            while (std::getline(file, line)) {
                lineNum++;
                if (line.empty()) continue;

                std::stringstream ss(line);
                std::string name, ageStr, id, eviStr, bachStr, mastStr, pubStr;

                if (!std::getline(ss, name, ',') ||
                    !std::getline(ss, ageStr, ',') ||
                    !std::getline(ss, id, ',') ||
                    !std::getline(ss, eviStr, ',') ||
                    !std::getline(ss, bachStr, ',') ||
                    !std::getline(ss, mastStr, ',') ||
                    !std::getline(ss, pubStr, ','))
                {
                    std::cerr << "Warning: skipping malformed line " << lineNum << std::endl;
                    continue;
                }

                try {
                    auto student = std::make_shared<Student>(name, std::stoi(ageStr), id);
                    student->setEviScore(std::stoi(eviStr));
                    student->setBachelor(std::stoi(bachStr));
                    student->setMaster(std::stoi(mastStr));
                    student->setPublications(std::stoi(pubStr));
                    allStudents.push_back(student);
                }
                catch (const ValidationException& e) {
                    std::cerr << "Warning: invalid data on line " << lineNum << ": " << e.what() << std::endl;
                }
                catch (const std::invalid_argument&) {
                    std::cerr << "Warning: bad number format on line " << lineNum << std::endl;
                }
            }

            std::cout << "Loaded " << allStudents.size() << " students." << std::endl;
        }
        catch (const std::ios_base::failure& e) {
            std::cerr << "Error loading data: " << e.what() << std::endl;
        }
    }

    void showHistory() const {
        logger->displayHistory();
    }
};