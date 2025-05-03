#include "map1117.h"
#include "map_utils.h"

void generateMap1117(vector<vector<char> >& map) {
    initializeMap(map);
    int x, y;
    
    // Generate ground floor
    for(int k = 5; k <= 119; k++) {
        setv(map, k, 16);
    }
    
    // Generate first platform layer
    for (x = 5; x <= 119; x++) {
        if (map[2][x] == ' ') {
            setfloor(map, x, 2);
        }
    }
    
    // Generate second platform layer
    for(y = 6; y <= 6; y++) {
        for(x = 5; x < 16; x++) {
            setfloor(map, x, y);
        }
        for(x = 33; x < 39; x++) {
            setfloor(map, x, y);
        }
        for(x = 108; x <= 119; x++) {
            setfloor(map, x, y);
        }
    }
    
    // Generate third platform layer
    for(y = 8; y <= 8; y++) {
        for(x = 26; x < 31; x++) {
            setfloor(map, x, y);
        }
        for(x = 41; x < 46; x++) {
            setfloor(map, x, y);
        }
        for(x = 63; x < 67; x++) {
            setfloor(map, x, y);
        }
        for(x = 71; x < 75; x++) {
            setfloor(map, x, y);
        }
        for(x = 104; x < 109; x++) {
            setfloor(map, x, y);
        }
    }
    
    // Generate fourth platform layer
    for(y = 10; y <= 10; y++) {
        for(x = 5; x < 11; x++) {
            setfloor(map, x, y);
        }
        for(x = 18; x < 24; x++) {
            setfloor(map, x, y);
        }
        for(x = 48; x < 54; x++) {
            setfloor(map, x, y);
        }
        for(x = 60; x < 65; x++) {
            setfloor(map, x, y);
        }
        for(x = 73; x < 78; x++) {
            setfloor(map, x, y);
        }
        for(x = 100; x < 105; x++) {
            setfloor(map, x, y);
        }
    }
    
    // Generate fifth platform layer
    for(y = 12; y <= 12; y++) {
        for(x = 12; x < 17; x++) {
            setfloor(map, x, y);
        }
        for(x = 26; x < 31; x++) {
            setfloor(map, x, y);
        }
        for(x = 41; x < 46; x++) {
            setfloor(map, x, y);
        }
        for(x = 62; x < 67; x++) {
            setfloor(map, x, y);
        }
        for(x = 71; x < 76; x++) {
            setfloor(map, x, y);
        }
        for(x = 96; x < 101; x++) {
            setfloor(map, x, y);
        }
    }    
    
    // Generate seventh platform layer
    for(y = 14; y <= 14; y++) {
        for(x = 5; x < 16; x++) {
            setfloor(map, x, y);
        }
        for(x=31;x<35;x++){
            setfloor(map,x,y);
        }
        for(x=38;x<41;x++){
            setfloor(map,x,y);
        }
        for(x = 54; x < 60; x++) {
            setfloor(map, x, y);
        }
        for(x = 67; x < 71; x++) {
            setfloor(map, x, y);
        }
        for(x = 78; x < 82; x++) {
            setfloor(map, x, y);
        }
        for(x = 85; x < 89; x++) {
            setfloor(map, x, y);
        }
        for(x = 92; x < 96; x++) {
            setfloor(map, x, y);
        }
    }
    
    // Generate walls
    for(x = 68; x <= 69; x++) {
        for(y = 8; y <= 13; y++) {
            setwall(map, x, y);
        }
    }
    
    setwall(map, 59, 8);
    setwall(map, 59, 9);
    setwall(map, 78, 8);
    setwall(map, 78, 9);
    
    // Generate slopes
    A(map, 67, 8);
    A(map, 68, 7);
    B(map, 69, 7);
    B(map, 70, 8);
    
    // Generate special elements
    C(map, 112, 5);
    D(map, 114, 5);
    E(map, 75, 9);
    E(map, 87, 13);
    E(map,36,11);
    E(map,10,9);
    setv(map, 14, 6);
    setv(map, 12, 7);
    setv(map, 11, 8);
    setv(map, 16, 7);
    setv(map, 17, 8);
} 
