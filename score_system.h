#ifndef SCORE_SYSTEM_H
#define SCORE_SYSTEM_H

#include <vector>
#include <string>
#include "health_system.h"
#include "ui.h"

/**
 * @brief Structure containing scoring information for a single level
 */
struct LevelScore {
    int level;          // Level number
    int timeScore;      // Score based on completion time
    int healthScore;    // Score based on remaining health
    int totalScore;     // Total combined score
    char grade;         // Final grade (A, B, C, D, or F)
};

/**
 * @brief Calculates the score for a completed level
 * @param level The level number
 * @param timeUsed Time taken to complete the level
 * @param remainingHealth Player's remaining health at level completion
 */
void calculateLevelScore(int level, int timeUsed, int remainingHealth);

/**
 * @brief Displays scores for all levels completed so far
 */
void displayLevelScores();

/**
 * @brief Displays scores for the current level
 */
void displayCurrentLevelScores();

/**
 * @brief Writes all level scores to an output file
 */
void writeOutputToFile();

/**
 * @brief Gets the vector containing all level scores
 * @return Reference to the vector of level scores
 */
std::vector<LevelScore>& getLevelScores();

/**
 * @brief Calculates the overall GPA based on all level grades
 * @return The calculated GPA value
 */
float calculateGPA();

#endif 