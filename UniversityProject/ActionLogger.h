#pragma once
#include <string>
#include <fstream>
#include <ctime>
#include <stdexcept>

class ActionLogger {
private:
    std::string logFilePath;

    std::string getCurrentTime() const {
        std::time_t now = std::time(nullptr);
        char buf[20];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        return std::string(buf);
    }

public:
    // unique_ptr: ActionLogger belongs solely to UniversityManager
    explicit ActionLogger(const std::string& path = "history.txt")
        : logFilePath(path) {
    }

    void log(const std::string& role, const std::string& action) {
        try {
            std::ofstream file(logFilePath, std::ios::app);
            if (!file.is_open())
                throw std::ios_base::failure("Cannot open log file: " + logFilePath);
            file << "[" << getCurrentTime() << "] [" << role << "] " << action << "\n";
        }
        catch (const std::ios_base::failure& e) {
            // Log failure is non-fatal — just print a warning
            std::cerr << "Warning: could not write to history log. " << e.what() << std::endl;
        }
    }

    void displayHistory() const {
        try {
            std::ifstream file(logFilePath);
            if (!file.is_open()) {
                std::cout << "No history found." << std::endl;
                return;
            }
            std::string line;
            bool hasAny = false;
            while (std::getline(file, line)) {
                std::cout << line << std::endl;
                hasAny = true;
            }
            if (!hasAny) std::cout << "History is empty." << std::endl;
        }
        catch (const std::ios_base::failure& e) {
            std::cerr << "Error reading history: " << e.what() << std::endl;
        }
    }
};