#include "map_utils.h"

void displayMap(const vector<vector<char> >& map) {
    cout << "地图：" << endl;
    for (int i = 0; i < MAP_HEIGHT; ++i) {
        for (int j = 0; j < MAP_WIDTH; ++j) {
            cout << map[i][j];
        }
        cout << endl;
    }
}

void initializeMap(vector<vector<char> >& map) {
    for (int i = 0; i < MAP_HEIGHT; ++i) {
        for (int j = 0; j < MAP_WIDTH; ++j) {
            map[i][j] = ' ';
        }
    }
}

void setfloor(vector<vector<char> >& map, int x, int y) {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        map[y][x] = '-';
    } else {
        cout << "坐标超出地图范围！" << endl;
    }
}

void setv(vector<vector<char> >& map, int x, int y) {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        map[y][x] = 'v';
    } else {
        cout << "坐标超出地图范围！" << endl;
    }
}

void setwall(vector<vector<char> >& map, int x, int y) {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        map[y][x] = '|';
    } else {
        cout << "坐标超出地图范围！" << endl;
    }
}

void A(vector<vector<char> >& map, int x, int y) {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        map[y][x] = '/';
    } else {
        cout << "坐标超出地图范围！" << endl;
    }
}

void B(vector<vector<char> >& map, int x, int y) {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        map[y][x] = '\\';
    } else {
        cout << "坐标超出地图范围！" << endl;
    }
}

void C(vector<vector<char> >& map, int x, int y) {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        map[y][x] = '[';
    } else {
        cout << "坐标超出地图范围！" << endl;
    }
}

void D(vector<vector<char> >& map, int x, int y) {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        map[y][x] = ']';
    } else {
        cout << "坐标超出地图范围！" << endl;
    }
}

void E(vector<vector<char> >& map, int x, int y) {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        map[y][x] = '$';
    } else {
        cout << "坐标超出地图范围！" << endl;
    }
}

void side(vector<vector<char> >& map, int x, int y) {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        map[y][x] = '#';
    } else {
        cout << "坐标超出地图范围！" << endl;
    }
}

void setleftv(vector<vector<char> >& map, int x, int y) {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        map[y][x] = '<';
    } else {
        cout << "坐标超出地图范围！" << endl;
    }
}

void setrightv(vector<vector<char> >& map, int x, int y) {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        map[y][x] = '>';
    } else {
        cout << "坐标超出地图范围！" << endl;
    }
}

void F(vector<vector<char> >& map, int x, int y) {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        map[y][x] = '<';
    } else {
        cout << "坐标超出地图范围！" << endl;
    }
}

void G(vector<vector<char> >& map, int x, int y) {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        map[y][x] = '>';
    } else {
        cout << "坐标超出地图范围！" << endl;
    }
}

void setfloors(vector<vector<char> >& map, int x, int y) {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        map[y][x] = '-';
        map[y][x+1] = '-';
        map[y][x+2] = '-';
    } else {
        cout << "坐标超出地图范围！" << endl;
    }
} 