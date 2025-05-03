#include "score_system.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>

// 存储所有关卡的评分
static std::vector<LevelScore> levelScores;

// 计算关卡评分
void calculateLevelScore(int level, int timeUsed, int remainingHealth) {
    LevelScore score;
    score.level = level;
    score.timeScore = std::max(0, 60 - timeUsed);  // 时间得分 = 60 - 使用时间
    score.healthScore = remainingHealth * 5;   // 血量得分 = 剩余血量 * 5
    if (score.healthScore == 0) {
        score.totalScore = timeUsed;
    } else {
        score.totalScore = score.timeScore + score.healthScore;
    }
    
    // 计算评级
    if (score.totalScore >= 40) {
        score.grade = 'A';
    } else if (score.totalScore >= 30) {
        score.grade = 'B';
    } else {
        score.grade = 'C';
    }
    
    // 添加到评分列表
    levelScores.push_back(score);
}

// 显示所有关卡评分 - 增强版
void displayLevelScores() {
    // 获取已完成关卡的评分数据
    const auto& levelScores = getLevelScores();
    if (levelScores.empty()) {
        return;
    }

    // 打开文件（追加模式）
    std::ofstream outFile("./record.txt", std::ios::app);
    if (!outFile) {
        std::cerr << "无法打开记录文件 record.txt" << std::endl;
        return;
    }

    std::ofstream file("./record.txt", std::ios::app); // 使用 append 模式
    if (!file.is_open()) {
        std::cerr << "Can not open: record.txt" << std::endl;
        return;
    }



    // 计算平均GPA
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

    // 根据GPA确定总体结果
    bool isPass = avgGpa >= 2.0;
    std::string resultText = isPass ? "ACADEMIC VICTORY!" : "ACADEMIC PROBATION";
    std::string resultSymbol = isPass ? "🎓" : "💀";

    // 输出文件和终端的流
    std::ostream& out = outFile; // 输出到文件
    std::ostream& console = std::cout; // 输出到终端

    // 获取当前时间
    std::time_t now = std::time(nullptr); // 获取当前时间（时间戳）
    char timeStr[100];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&now)); // 格式化时间

    // 写入创建记录的时间
    out << std::endl;
    out << timeStr << std::endl;
    out << std::endl;

    // 显示标题
    out << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n";
    out << "█▓▒░░      ~ GRADE RELEASE ~      ░░▒▓█\n";
    out << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\n";

    console << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n";
    console << "█▓▒░░      ~ GRADE RELEASE ~      ░░▒▓█\n";
    console << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\n";

    // 显示总体结果
    out << "  " << resultSymbol << "  " << resultText << "  " << resultSymbol << "\n\n";
    console << "  " << resultSymbol << "  " << resultText << "  " << resultSymbol << "\n\n";

    // 显示成绩表头
    out << "  LEVEL     TIME    SCORE   SURV   TOTAL  GRADE\n";
    out << "  ─────────────────────────────────────────────\n";

    console << "  LEVEL     TIME    SCORE   SURV   TOTAL  GRADE\n";
    console << "  ─────────────────────────────────────────────\n";

    // 遍历并显示每门课程的成绩与其他数据
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

        // 打印行数据到文件和终端
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

    // 显示最终GPA
    out << "\nFINAL GPA: " << std::fixed << std::setprecision(1) << avgGpa << "\n";
    console << "\nFINAL GPA: " << std::fixed << std::setprecision(1) << avgGpa << "\n";

    // 关闭文件
    outFile.close();
}

// 显示已通关关卡评分
void displayCurrentLevelScores() {
    if (!levelScores.empty()) {
        std::cout << "\n已通关关卡评分：" << std::endl;
        std::cout << "--------------------------" << std::endl;
        std::cout << "关卡\t评级" << std::endl;
        std::cout << "--------------------------" << std::endl;
        for (const auto& score : levelScores) {
            std::cout << score.level << "\t" << score.grade << std::endl;
        }
        std::cout << "--------------------------" << std::endl;
    }
}

void writeOutputToFile() {
    // 打开文件
    std::ofstream file("./record.txt", std::ios::app); // 使用 append 模式
    if (!file.is_open()) {
        std::cerr << "Can not open: record.txt" << std::endl;
        return;
    }

    // 获取当前时间
    std::time_t now = std::time(nullptr); // 获取当前时间（时间戳）
    char timeStr[100];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&now)); // 格式化时间

    // 写入创建记录的时间
    file << "Record Time" << std::endl;
    file << timeStr << std::endl;

    // 重定向 std::cout 到文件
    std::streambuf *coutBuf = std::cout.rdbuf(); // 保存原始缓冲区
    std::cout.rdbuf(file.rdbuf());              // 重定向 std::cout 到文件

    // 恢复 std::cout 的原始缓冲区
    std::cout.rdbuf(coutBuf);

    // 关闭文件
    file.close();
}

// 获取评分列表
std::vector<LevelScore>& getLevelScores() {
    return levelScores;
}

// 计算GPA
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