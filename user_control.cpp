#include "user_control.h"
#include <iostream>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#include <cmath>

#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace std;

struct termios UserControl::orig_termios; // Static member variable definition

// Constructor: Enables raw terminal mode
UserControl::UserControl(){
    enableRawMode();
}

// Destructor: Restores the terminal to its original mode
UserControl::~UserControl() {
    enableRawMode();
    returnToMainMenu = false;  // Initialize the flag to false
}

void UserControl::resetReturnFlag() {
    returnToMainMenu = false;
}

// Enables raw terminal mode
void UserControl::enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios); // Save current terminal settings
    atexit(disableRawMode);                 // Restore terminal mode on program exit

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON | ISIG); // Disable echo, line buffering, and signal processing
    raw.c_cc[VMIN] = 0;                     // Non-blocking input
    raw.c_cc[VTIME] = 1;                    // Set timeout
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// Restores the terminal to its original mode (static function)
void UserControl::disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); // Restore original terminal settings
}

// Detects key presses
char UserControl::getKeyPress() {
    char c = 0;
    fd_set fds;
    struct timeval tv = {0, 0}; // Non-blocking
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);

    if (select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0) {
        read(STDIN_FILENO, &c, 1);
    }
    return c;
}

// Handles user input
void UserControl::handleInput(int &playerX, int &playerY, bool &isJumping, float &playerVelocityY, float &playerVelocityX, const float JUMP_FORCE, int SCREEN_WIDTH) {
    char key = getKeyPress();
    
    // Process key input
    switch (key) {
        case 'a': case 'A':
            if (playerX > 0 || playerX < SCREEN_WIDTH - 1) {
                if (!isJumping) {
                    playerX--; // Move one step left on the ground
                } else {
                    playerVelocityX = -1.0f; // Set a small horizontal velocity to the left while jumping
                }
            }
            break;
        case 'd': case 'D':
            if (playerX < SCREEN_WIDTH - 1) {
                if (!isJumping) {
                    playerX++; // Move one step right on the ground
                } else {
                    playerVelocityX = 1.0f; // Set horizontal velocity to the right while jumping
                }
            }
            break;
        case 'w': case 'W':
            if (!isJumping) {
                isJumping = true;
                playerVelocityY = JUMP_FORCE; // Start jumping
            }
            break;
        case 'q': case 'Q':
            // Set the flag to return to the main menu
            returnToMainMenu = true;
            // displayLevelScores(); // (Optional: Uncomment if a level score display is implemented)
            break;
        default:
            break;
    }
}
