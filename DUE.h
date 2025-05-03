#ifndef DUE_H
#define DUE_H

#include <vector>
#include <ctime>

// Constants for DUE mechanics
const double DUE_SPEED = 0.2;     // Speed of DUE advancement (in seconds)
const int DUE_WIDTH = 2;          // Width of each DUE advancement step

// Global variables for DUE state
extern time_t lastDUETime;        // Time of last DUE advancement
extern int DUEPosition;           // Current position of DUE
extern time_t levelStartTime;     // Time when the current level started

/**
 * @brief Initializes the DUE system
 * Sets up initial position and timing for the DUE mechanic
 */
void initDUE();

/**
 * @brief Updates the DUE position and state on the game map
 * @param map Reference to the game map to be updated
 */
void updateDUE(std::vector<std::vector<char> >& map);

/**
 * @brief Checks if a position collides with the DUE wall
 * @param map The current game map
 * @param x X-coordinate to check
 * @param y Y-coordinate to check
 * @return true if collision detected, false otherwise
 */
bool checkDUECollision(const std::vector<std::vector<char> >& map, int x, int y);

#endif // DUE_H 