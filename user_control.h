#ifndef USER_CONTROL_H
#define USER_CONTROL_H

#include "score_system.h"
#include <termios.h>
#include <unistd.h>

/**
 * @brief Class handling user input and terminal control for the game
 */
class UserControl {
private:
    static struct termios orig_termios;  // Original terminal settings
    
    /**
     * @brief Enables raw mode for terminal input
     * Configures terminal for immediate character-by-character input
     */
    void enableRawMode();
    
    /**
     * @brief Disables raw mode and restores original terminal settings
     */
    static void disableRawMode();
    
    /**
     * @brief Gets a single keypress from the user
     * @return The character representing the key pressed
     */
    char getKeyPress();

public:
    bool returnToMainMenu;  // Flag indicating whether to return to main menu

    /**
     * @brief Constructor - initializes terminal settings
     */
    UserControl();

    /**
     * @brief Destructor - restores terminal settings
     */
    ~UserControl();

    /**
     * @brief Handles user input for player movement and actions
     * @param playerX Reference to player's X position
     * @param playerY Reference to player's Y position
     * @param isJumping Reference to player's jumping state
     * @param playerVelocityY Reference to player's vertical velocity
     * @param playerVelocityX Reference to player's horizontal velocity
     * @param JUMP_FORCE Constant for jump force
     * @param SCREEN_WIDTH Constant for screen width
     */
    void handleInput(int &playerX, int &playerY, bool &isJumping, 
                    float &playerVelocityY, float &playerVelocityX, 
                    const float JUMP_FORCE, int SCREEN_WIDTH);

    /**
     * @brief Resets the return to main menu flag
     */
    void resetReturnFlag();
};

#endif