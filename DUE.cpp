#include "DUE.h"
#include "All_maps/map_utils.h"
#include "Incidents/pause_DUE.h"

// Define DUE-related variables
time_t lastDUETime;
int DUEPosition;

//initialize DUE
void initDUE() {
    lastDUETime = time(nullptr);
    DUEPosition = 0;
    levelStartTime = time(nullptr);  
}

// update DUE
void updateDUE(std::vector<std::vector<char> >& map) {
    if (isDUECurrentlyPaused()) {
        return;
    }

    //stop DUE for 3 second 
    time_t currentTime = time(nullptr);
    if (currentTime - levelStartTime < 3) {
        return;  
    }

    if (currentTime - lastDUETime >= DUE_SPEED) {
    //move due
        for (int i = 0; i < MAP_HEIGHT; ++i) {
            for (int j = DUEPosition; j < DUEPosition + DUE_WIDTH; ++j) {
                if (j < MAP_WIDTH) {

                    map[i][j] = "DUE"[i % 3];
                }
            }
        }
        DUEPosition += DUE_WIDTH;
        lastDUETime = currentTime;
    }
}

// check if meet due
bool checkDUECollision(const std::vector<std::vector<char> >& map, int x, int y) {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        return false;
    }
    char c = map[y][x];
    return (c == 'D' || c == 'U' || c == 'E'); \
} 
