#ifndef PAUSE_DUE_H
#define PAUSE_DUE_H

/**
 * @brief Functions for managing DUE wall pause mechanics
 */

/**
 * @brief Temporarily pauses the DUE wall movement
 */
void pauseDUE();  // Pause DUE

/**
 * @brief Updates the pause state of the DUE wall
 */
void updateDUEPause();  // Update DUE pause state

/**
 * @brief Checks if the DUE wall is currently paused
 * @return true if DUE is paused, false otherwise
 */
bool isDUECurrentlyPaused();  // Check if DUE is currently paused

/**
 * @brief Reduces the remaining time in the current level
 * @param time Reference to the current level time to be reduced
 */
void reduceLevelTime(int& time);  // Reduce level time

#endif // PAUSE_DUE_H