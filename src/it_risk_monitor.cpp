#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

// Simple health status for each service
enum class Status {
    OK,
    WARN,
    CRITICAL
};

// Representation of an IT service
struct Service {
    std::string name;
    Status status;
    int riskScore;
};

// Convert Status enum to string for printing
std::string statusToString(Status s) {
    switch (s) {
        case Status::OK:       return "OK";
        case Status::WARN:     return "WARN";
        case Status::CRITICAL: return "CRITICAL";
        default:               return "UNKNOWN";
    }
}

// Map status to a numerical risk score
int riskFromStatus(Status s) {
    switch (s) {
        case Status::OK:       return 10;  // low risk
        case Status::WARN:     return 40;  // medium risk
        case Status::CRITICAL: return 80;  // high risk
        default:               return 0;
    }
}

// Randomly choose a status
Status randomStatus() {
    int r = std::rand() % 100; // 0–99
    if (r < 60) {
        return Status::OK;       // 60% chance
    } else if (r < 85) {
        return Status::WARN;     // 25% chance
    } else {
        return Status::CRITICAL; // 15% chance
    }
}

// Classify total risk score into LOW / MEDIUM / HIGH
std::string classifyOverallRisk(int totalRisk) {
    if (totalRisk < 100) {
        return "LOW";
    } else if (totalRisk < 250) {
        return "MEDIUM";
    } else {
        return "HIGH";
    }
}

// Write a simple log file with the current simulation
void writeLog(const std::string& path,
              const std::vector<Service>& services,
              int totalRisk,
              const std::string& overall) {
    std::ofstream out(path, std::ios::app); // append mode
    if (!out) {
        return; // if logging fails, just skip it
    }

    out << "=== IT Service Health Snapshot ===\n";
    for (const auto& s : services) {
        out << "Service: " << s.name
            << " | Status: " << statusToString(s.status)
            << " | Risk: " << s.riskScore << "\n";
    }
    out << "Total Risk: " << totalRisk
        << " | Overall Level: " << overall << "\n";
    out << "-------------------------------\n";
}

int main() {
    // Seed random generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Define critical IT services
    std::vector<Service> services = {
        {"DATABASE",   Status::OK, 0},
        {"AUTH",       Status::OK, 0},
        {"NETWORK",    Status::OK, 0},
        {"BACKUP",     Status::OK, 0},
        {"LOGGING",    Status::OK, 0}
    };

    // Simulate a status for each service
    int totalRisk = 0;
    for (auto& s : services) {
        s.status = randomStatus();
        s.riskScore = riskFromStatus(s.status);
        totalRisk += s.riskScore;
    }

    std::string overall = classifyOverallRisk(totalRisk);

    // Print summary to console
    std::cout << "=== IT Service Health Monitor (C++) ===\n\n";
    for (const auto& s : services) {
        std::cout << "Service: " << s.name
                  << " | Status: " << statusToString(s.status)
                  << " | Risk: " << s.riskScore << "\n";
    }

    std::cout << "\nTotal Risk Score: " << totalRisk << "\n";
    std::cout << "Overall Risk Level: " << overall << "\n\n";

    if (overall == "LOW") {
        std::cout << "Comment: System looks stable.\n";
    } else if (overall == "MEDIUM") {
        std::cout << "Comment: Some components need attention.\n";
    } else {
        std::cout << "Comment: High operational risk. Immediate action required.\n";
    }

    // Write a log entry to file
    writeLog("logs/system_log.txt", services, totalRisk, overall);

    return 0;
}
