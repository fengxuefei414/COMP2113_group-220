#include "score_system.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>

// Store scores for all levels
static std::vector<LevelScore> levelScores;

// Calculate level score
void calculateLevelScore(int level, int timeUsed, int remainingHealth) {
    LevelScore score;
    score.level = level;
    score.timeScore = std::max(0, 60 - timeUsed);  // Time score = 60 - used time
    score.healthScore = remainingHealth * 5;   // Health score = remaining health * 5
    if (score.healthScore == 0) {
        score.totalScore = timeUsed;
    } else {
        score.totalScore = score.timeScore + score.healthScore;
    }
    
    // Calculate grade
    if (score.totalScore >= 40) {
        score.grade = 'A';
    } else if (score.totalScore >= 30) {
        score.grade = 'B';
    } else {
        score.grade = 'C';
    }
    
    // Add to score list
    levelScores.push_back(score);
}

// Display all level scores - Enhanced version
void displayLevelScores() {
    // Get completed level score data
    const auto& levelScores = getLevelScores();
    if (levelScores.empty()) {
        return;
    }

    // Open file (append mode)
    std::ofstream outFile("./record.txt", std::ios::app);
    if (!outFile) {
        std::cerr << "Unable to open record.txt" << std::endl;
        return;
    }

    std::ofstream file("./record.txt", std::ios::app); // Use append mode
    if (!file.is_open()) {
        std::cerr << "Can not open: record.txt" << std::endl;
        return;
    }

    // Calculate average GPA
    float totalGpa = 0.0f;
    for (const auto& score : levelScores) {
        switch (score.grade) {
            case 'A': totalGpa += 4.0f; break;
            case 'B': totalGpa += 3.0f; break;
            case 'C': totalGpa += 2.0f; break;
            default: totalGpa += 2.0f; break;
        }
    }
    float avgGpa = levelScores.size() > 0 ? totalGpa / levelScores.size() : 0.0f;

    // Determine overall result based on GPA
    bool isPass = avgGpa >= 2.0;
    std::string resultText = isPass ? "ACADEMIC VICTORY!" : "ACADEMIC PROBATION";
    std::string resultSymbol = isPass ? "🎓" : "💀";

    // Output file and terminal streams
    std::ostream& out = outFile; // Output to file
    std::ostream& console = std::cout; // Output to terminal

    // Get current time
    std::time_t now = std::time(nullptr); // Get current time (timestamp)
    char timeStr[100];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&now)); // Format time

    // Write creation time of record
    out << std::endl;
    out << timeStr << std::endl;
    out << std::endl;

    // Display title
    out << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n";
    out << "█▓▒░░      ~ GRADE RELEASE ~      ░░▒▓█\n";
    out << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\n";

    console << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n";
    console << "█▓▒░░      ~ GRADE RELEASE ~      ░░▒▓█\n";
    console << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\n";

    // Display overall result
    out << "  " << resultSymbol << "  " << resultText << "  " << resultSymbol << "\n\n";
    console << "  " << resultSymbol << "  " << resultText << "  " << resultSymbol << "\n\n";

    // Display score table header
    out << "  LEVEL     TIME    SCORE   SURV   TOTAL  GRADE\n";
    out << "  ─────────────────────────────────────────────\n";

    console << "  LEVEL     TIME    SCORE   SURV   TOTAL  GRADE\n";
    console << "  ─────────────────────────────────────────────\n";

    // Display each course's score and other data
    for (const auto& score : levelScores) {
        std::string courseName;
        switch (score.level) {
            case 1: courseName = "APAI1001"; break;
            case 2: courseName = "COMP1117"; break;
            case 3: courseName = "CAES1000"; break;
            case 4: courseName = "STAT1016"; break;
            case 5: courseName = "MATH2014"; break;
            case 6: courseName = "STAT2601"; break;
            default: courseName = "LEVEL" + std::to_string(score.level);
        }

        char gradeChar = score.grade;
        int timeUsed = 60 - score.timeScore;
        int scoreVal = score.timeScore;
        bool survived = (score.healthScore > 0);
        int totalScore = score.totalScore;

        std::string survivalSymbol = survived ? "✓" : "✗";

        // Print row data to file and terminal
        out << "  " << std::left << std::setw(9) << courseName
            << std::right << std::setw(4) << timeUsed << "s "
            << std::right << std::setw(8) << scoreVal
            << std::right << std::setw(9) << survivalSymbol
            << std::right << std::setw(8) << totalScore
            << std::right << std::setw(7) << gradeChar << "\n";

        console << "  " << std::left << std::setw(9) << courseName
                << std::right << std::setw(4) << timeUsed << "s "
                << std::right << std::setw(8) << scoreVal
                << std::right << std::setw(9) << survivalSymbol
                << std::right << std::setw(8) << totalScore
                << std::right << std::setw(7) << gradeChar << "\n";
    }

    // Display final GPA
    out << "\nFINAL GPA: " << std::fixed << std::setprecision(1) << avgGpa << "\n";
    console << "\nFINAL GPA: " << std::fixed << std::setprecision(1) << avgGpa << "\n";

    // Close file
    outFile.close();
}

// Display completed level scores
void displayCurrentLevelScores() {
    if (!levelScores.empty()) {
        std::cout << "\nCompleted Level Scores:" << std::endl;
        std::cout << "--------------------------" << std::endl;
        std::cout << "Level\tGrade" << std::endl;
        std::cout << "--------------------------" << std::endl;
        for (const auto& score : levelScores) {
            std::cout << score.level << "\t" << score.grade << std::endl;
        }
        std::cout << "--------------------------" << std::endl;
    }
}

void writeOutputToFile() {
    // Open file
    std::ofstream file("./record.txt", std::ios::app); // Use append mode
    if (!file.is_open()) {
        std::cerr << "Can not open: record.txt" << std::endl;
        return;
    }

    // Get current time
    std::time_t now = std::time(nullptr); // Get current time (timestamp)
    char timeStr[100];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&now)); // Format time

    // Write creation time of record
    file << "Record Time" << std::endl;
    file << timeStr << std::endl;

    // Redirect std::cout to file
    std::streambuf *coutBuf = std::cout.rdbuf(); // Save original buffer
    std::cout.rdbuf(file.rdbuf());              // Redirect std::cout to file

    // Restore original std::cout buffer
    std::cout.rdbuf(coutBuf);

    // Close file
    file.close();
}

// Get score list
std::vector<LevelScore>& getLevelScores() {
    return levelScores;
}

// Calculate GPA
float calculateGPA() {
    float totalPoints = 0.0f;
    int numLevels = levelScores.size();
    
    for (const auto& score : levelScores) {
        switch (score.grade) {
            case 'A':
                totalPoints += 4.0f;
                break;
            case 'B':
                totalPoints += 3.0f;
                break;
            case 'C':
                totalPoints += 2.0f;
                break;
            default:
                totalPoints += 0.0f;
                break;
        }
    }
    
    return numLevels > 0 ? totalPoints / numLevels : 0.0f;
} 