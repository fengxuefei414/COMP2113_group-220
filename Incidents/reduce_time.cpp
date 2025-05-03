#include "reduce_time.h"

// Reduce level time
void reduceLevelTime(int& levelTime) {
    levelTime -= 10;  // Reduce by 10 seconds
    if (levelTime < 0) {  // Ensure time doesn't become negative
        levelTime = 0;
    }
} 