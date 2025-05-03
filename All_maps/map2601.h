#ifndef MAP2601_H
#define MAP2601_H

#include <vector>
#include <iostream>
#include "./map_utils.h"

using namespace std;

// Map Constants
extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;

// Map Function Declarations
void displayMap(const vector<vector<char> >& map);
void initializeMap(vector<vector<char> >& map);
void setfloor(vector<vector<char> >& map, int x, int y);
void setv(vector<vector<char> >& map, int x, int y);
void setwall(vector<vector<char> >& map, int x, int y);
void A(vector<vector<char> >& map, int x, int y);
void B(vector<vector<char> >& map, int x, int y);
void C(vector<vector<char> >& map, int x, int y);
void D(vector<vector<char> >& map, int x, int y);
void E(vector<vector<char> >& map, int x, int y);
void side(vector<vector<char> >& map, int x, int y);
void generateMap2601(vector<vector<char> >& map);

#endif
