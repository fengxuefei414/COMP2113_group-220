#ifndef PAUSE_DUE_H
#define PAUSE_DUE_H

/**
 * @brief Functions for managing DUE wall pause mechanics
 */

/**
 * @brief Temporarily pauses the DUE wall movement
 */
void pauseDUE();  // 暂停DUE

/**
 * @brief Updates the pause state of the DUE wall
 */
void updateDUEPause();  // 更新DUE暂停状态

/**
 * @brief Checks if the DUE wall is currently paused
 * @return true if DUE is paused, false otherwise
 */
bool isDUECurrentlyPaused();  // 检查DUE是否处于暂停状态

/**
 * @brief Reduces the remaining time in the current level
 * @param time Reference to the current level time to be reduced
 */
void reduceLevelTime(int& time);  // 减少关卡时间

#endif // PAUSE_DUE_H