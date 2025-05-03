#ifndef MAP2014_H
#define MAP2014_H

#include <vector>
#include <iostream>
#include "./map_utils.h"

using namespace std;

// 地图常量
extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;

// 地图函数声明
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
void generateMap2014(vector<vector<char> >& map);

#endif
