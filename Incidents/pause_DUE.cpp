#include "pause_DUE.h"
#include <ctime>

// Define DUE pause related variables
time_t DUEPauseStartTime;
bool isDUEPaused = false;

// Pause DUE
void pauseDUE() {
    DUEPauseStartTime = time(nullptr);
    isDUEPaused = true;
}

// Update DUE pause state
void updateDUEPause() {
    if (isDUEPaused) {
        time_t currentTime = time(nullptr);
        if (currentTime - DUEPauseStartTime >= 3) {  // Resume after 5 seconds
            isDUEPaused = false;
        }
    }
}

// Check if DUE is currently paused
bool isDUECurrentlyPaused() {
    return isDUEPaused;
}