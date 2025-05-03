#ifndef MAP_UTILS_H
#define MAP_UTILS_H

#include <vector>
#include <iostream>

using namespace std;

/**
 * @brief Map dimension constants
 */
const int MAP_WIDTH = 120;    // Width of all game maps
const int MAP_HEIGHT = 20;    // Height of all game maps

/**
 * @brief Core map utility functions for map generation and manipulation
 */

/**
 * @brief Displays the current state of any map
 * @param map The game map to display
 */
void displayMap(const vector<vector<char> >& map);

/**
 * @brief Initializes an empty map with default values
 * @param map Reference to the map vector to initialize
 */
void initializeMap(vector<vector<char> >& map);

/**
 * @brief Sets a single floor tile at specified coordinates
 * @param map Reference to the game map
 * @param x X-coordinate for the floor tile
 * @param y Y-coordinate for the floor tile
 */
void setfloor(vector<vector<char> >& map, int x, int y);

/**
 * @brief Sets multiple floor tiles at specified coordinates
 * @param map Reference to the game map
 * @param x Starting X-coordinate for the floor tiles
 * @param y Starting Y-coordinate for the floor tiles
 */
void setfloors(vector<vector<char> >& map, int x, int y);

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
 * @brief Places pattern F at specified coordinates
 * @param map Reference to the game map
 * @param x Starting X-coordinate for the pattern
 * @param y Starting Y-coordinate for the pattern
 */
void F(vector<vector<char> >& map, int x, int y);

/**
 * @brief Places pattern G at specified coordinates
 * @param map Reference to the game map
 * @param x Starting X-coordinate for the pattern
 * @param y Starting Y-coordinate for the pattern
 */
void G(vector<vector<char> >& map, int x, int y);

/**
 * @brief Sets side boundaries at specified coordinates
 * @param map Reference to the game map
 * @param x X-coordinate for the side boundary
 * @param y Y-coordinate for the side boundary
 */
void side(vector<vector<char> >& map, int x, int y);

/**
 * @brief Sets a left vertical boundary at specified coordinates
 * @param map Reference to the game map
 * @param x X-coordinate for the left boundary
 * @param y Y-coordinate for the left boundary
 */
void setleftv(vector<vector<char> >& map, int x, int y);

/**
 * @brief Sets a right vertical boundary at specified coordinates
 * @param map Reference to the game map
 * @param x X-coordinate for the right boundary
 * @param y Y-coordinate for the right boundary
 */
void setrightv(vector<vector<char> >& map, int x, int y);

#endif 