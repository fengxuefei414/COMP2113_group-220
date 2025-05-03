#ifndef DDL_FIGHTER_UI_H
#define DDL_FIGHTER_UI_H
#include <iostream>     // For cout, endl, flush
#include <vector>       // For vector
#include <string>       // For string
#include <termios.h>    // For terminal control (tcgetattr, tcsetattr)
#include <unistd.h>     // For read, usleep, STDIN_FILENO
#include <iomanip>      // For setw, setprecision, fixed, left
#include <algorithm>    // For std::max, std::min
#include <fstream>      // For ifstream

/**
 * @brief UI namespace containing all user interface related functionality
 */
namespace UI {
    /**
     * @brief Detail namespace containing internal implementation details
     */
    namespace Detail {
        /**
         * @brief Manages terminal settings and state
         */
        struct TermiosManager {
            struct termios original_termios;
            bool initialized = false;

            TermiosManager() = default; // Keep it simple
            void captureOriginal();
            const struct termios& getOriginal();
        };

        // Static instance within the detail namespace
        TermiosManager& getTermiosManager();
    } // namespace Detail

    /**
     * @brief Color namespace containing ANSI color codes and UI drawing functions
     */
    namespace Color {
        // Reset
        extern const std::string RESET;

        // Regular Colors
        extern const std::string BLACK;
        extern const std::string RED;
        extern const std::string GREEN;
        extern const std::string YELLOW;
        extern const std::string BLUE;
        extern const std::string MAGENTA;
        extern const std::string CYAN;
        extern const std::string WHITE;

        // Bright Colors
        extern const std::string BRIGHT_BLACK;
        extern const std::string BRIGHT_RED;
        extern const std::string BRIGHT_GREEN;
        extern const std::string BRIGHT_YELLOW;
        extern const std::string BRIGHT_BLUE;
        extern const std::string BRIGHT_MAGENTA;
        extern const std::string BRIGHT_CYAN;
        extern const std::string BRIGHT_WHITE;

        // Formatting
        extern const std::string BOLD;
        extern const std::string UNDERLINE;
        extern const std::string INVERSE;

        /**
         * @brief Draws a title banner with the given text
         * @param text The text to display in the title
         */
        void drawTitle(const std::string& text);

        /**
         * @brief Draws a menu item with optional selection highlighting
         * @param text The text of the menu item
         * @param selected Whether this item is currently selected
         */
        void drawMenuItem(const std::string& text, bool selected = false);

        /**
         * @brief Displays a warning message with a warning symbol
         * @param text The warning message to display
         */
        void drawWarning(const std::string& text);

        /**
         * @brief Displays a success message with a checkmark symbol
         * @param text The success message to display
         */
        void drawSuccess(const std::string& text);
    } // namespace Color

    // --- Terminal Control Functions ---

    /**
     * @brief Clears the terminal screen using ANSI escape codes.
     *        Moves cursor to top-left (1,1).
     */
    void clearScreen();

    /**
     * @brief Pauses execution for a specified number of milliseconds.
     * @param ms Milliseconds to sleep.
     */
    void sleep_ms(int ms);

    /**
     * @brief Initializes the terminal for raw input (disables ICANON and ECHO).
     *        Stores the original terminal settings for later restoration.
     *        Should be called once at the start of the application.
     */
    void initTerminal();

    /**
     * @brief Restores the terminal to its original settings captured by initTerminal.
     *        Should be called before the application exits.
     */
    void resetTerminal();

    // Define constants for special key inputs
    extern const char KEY_UP;
    extern const char KEY_DOWN;
    extern const char KEY_RIGHT;
    extern const char KEY_LEFT;
    extern const char KEY_ENTER;
    extern const char KEY_SPACE;
    extern const char KEY_ESC;
    extern const char KEY_QUIT_LOWER;
    extern const char KEY_QUIT_UPPER;
    extern const char KEY_NULL;

   /**
    * @brief Reads a single key press from standard input without waiting for Enter.
    *        Handles regular characters, Enter, Space, Esc, and Arrow Keys (via escape sequences).
    * @return The character read, or special constants KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT,
    *         KEY_ESC, KEY_NULL (on read error or unrecognized sequence).
    */
    char readKeyInput();

    // --- Helper UI Display Functions ---

    /**
     * @brief Shows the game start screen with enemy list and loading animation
     * @param course The name of the course/level
     * @param enemies List of enemy names to display
     * @param loadingMessage Message to show during loading
     * @param titleColor Color for the title text
     * @param enemyTitleColor Color for the enemy list header
     * @param enemyItemColor Color for individual enemy names
     * @param loadTimeMs Duration of loading animation in milliseconds
     */
    void showGameStart(const std::string& course,
                       const std::vector<std::string>& enemies,
                       const std::string& loadingMessage,
                       const std::string& titleColor = Color::BRIGHT_GREEN,
                       const std::string& enemyTitleColor = Color::BRIGHT_YELLOW,
                       const std::string& enemyItemColor = Color::BRIGHT_RED,
                       int loadTimeMs = 1500);

    /**
     * @brief Displays an encouraging message before the final course
     * @param courseName Name of the final course
     * @param message Encouragement message to display
     * @param art Optional ASCII art to display
     */
    void showFinalEncouragement(const std::string& courseName,
                               const std::string& message,
                               const std::string& art = "");

    /**
     * @brief Displays the final grade report screen.
     * @param grades Vector of pairs (Course Name, Grade Character).
     * @param gpa The calculated final GPA.
     */
    void displayFinalScreen(const std::vector<std::pair<std::string, char>>& grades, float gpa);


    // --- Main UI Screen Functions ---

    // Enum for Main Menu options
    enum class MainMenuOption { START, SETTINGS, RECORDS, EXIT, NONE };

    /**
     * @brief Displays the contents of the record file
     */
    void showRecords();

    /**
     * @brief Runs the main menu interface and returns the selected option
     * @return Selected MainMenuOption enum value
     */
    MainMenuOption runMainMenu();

    // Enum for Settings Menu options
    enum class SettingsMenuOption { BACK, RESET_PROGRESS, CONTROLS, NONE };

    /**
     * @brief Runs the settings menu interface and returns the selected option
     * @return Selected SettingsMenuOption enum value
     */
    SettingsMenuOption runSettingsMenu();

    // Enum for Difficulty levels
    enum class Difficulty { EASY, MEDIUM, HARD, BACK, NONE };

    /**
     * @brief Runs the difficulty selection menu and returns the chosen difficulty
     * @return Selected Difficulty enum value
     */
    Difficulty runDifficultySelection();


    /**
     * @brief Runs the course selection interface
     * @param difficulty Current game difficulty setting
     * @param playerLives Number of lives remaining
     * @param selectedCourseIndex Reference to store the selected course index
     * @return true if a course was selected, false if user chose to go back
     */
    bool runCourseSelection(Difficulty difficulty, int playerLives, int& selectedCourseIndex);

    /**
     * @brief Displays the final game results including grades and GPA
     * @param grades Vector of pairs containing course names and their corresponding grades
     * @param gpa Final calculated GPA
     */
    void displayGameResults(const std::vector<std::pair<std::string, char>>& grades, float gpa);

    /**
     * @brief Helper function to generate sample grades for testing the final screen
     */
    std::vector<std::pair<std::string, char>> generateSampleGrades(Difficulty difficulty);

    /**
     * @brief Helper function to calculate a sample GPA based on grades
     */
    float calculateSampleGpa(const std::vector<std::pair<std::string, char>>& grades);

} // namespace UI

#endif // DDL_FIGHTER_UI_H