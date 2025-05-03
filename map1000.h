#ifndef MAP1000_H
#define MAP1000_H

#include <vector>
#include <iostream>
#include "./map_utils.h"

using namespace std;

// Map constants
extern const int MAP_WIDTH;   // Width of the game map
extern const int MAP_HEIGHT;  // Height of the game map

/**
 * @brief Map manipulation functions
 */

/**
 * @brief Displays the current state of the map
 * @param map The game map to display
 */
void displayMap(const vector<vector<char> >& map);

/**
 * @brief Initializes an empty map with default values
 * @param map Reference to the map vector to initialize
 */
void initializeMap(vector<vector<char> >& map);

/**
 * @brief Sets a floor tile at specified coordinates
 * @param map Reference to the game map
 * @param x X-coordinate for the floor tile
 * @param y Y-coordinate for the floor tile
 */
void setfloor(vector<vector<char> >& map, int x, int y);

/**
 * @brief Sets a vertical obstacle at specified coordinates
 * @param map Reference to the game map
 * @param x X-coordinate for the obstacle
 * @param y Y-coordinate for the obstacle
 */
void setv(vector<vector<char> >& map, int x, int y);

/**
 * @brief Sets a wall tile at specified coordinates
 * @param map Reference to the game map
 * @param x X-coordinate for the wall
 * @param y Y-coordinate for the wall
 */
void setwall(vector<vector<char> >& map, int x, int y);

/**
 * @brief Places pattern A at specified coordinates
 * @param map Reference to the game map
 * @param x Starting X-coordinate for the pattern
 * @param y Starting Y-coordinate for the pattern
 */
void A(vector<vector<char> >& map, int x, int y);

/**
 * @brief Places pattern B at specified coordinates
 * @param map Reference to the game map
 * @param x Starting X-coordinate for the pattern
 * @param y Starting Y-coordinate for the pattern
 */
void B(vector<vector<char> >& map, int x, int y);

/**
 * @brief Places pattern C at specified coordinates
 * @param map Reference to the game map
 * @param x Starting X-coordinate for the pattern
 * @param y Starting Y-coordinate for the pattern
 */
void C(vector<vector<char> >& map, int x, int y);

/**
 * @brief Places pattern D at specified coordinates
 * @param map Reference to the game map
 * @param x Starting X-coordinate for the pattern
 * @param y Starting Y-coordinate for the pattern
 */
void D(vector<vector<char> >& map, int x, int y);

/**
 * @brief Places pattern E at specified coordinates
 * @param map Reference to the game map
 * @param x Starting X-coordinate for the pattern
 * @param y Starting Y-coordinate for the pattern
 */
void E(vector<vector<char> >& map, int x, int y);

/**
 * @brief Sets side boundaries at specified coordinates
 * @param map Reference to the game map
 * @param x X-coordinate for the side boundary
 * @param y Y-coordinate for the side boundary
 */
void side(vector<vector<char> >& map, int x, int y);

/**
 * @brief Generates map layout for level 1000
 * @param map Reference to the game map to generate
 */
void generateMap1000(vector<vector<char> >& map);

#endif
