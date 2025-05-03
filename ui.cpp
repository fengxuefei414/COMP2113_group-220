#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <iomanip> // For std::setw and std::setprecision
#include <termios.h>    // For terminal control (tcgetattr, tcsetattr)
#include <unistd.h>     // For read, usleep, STDIN_FILENO
#include <algorithm>    // For std::max, std::min
#include <fstream>      // For ifstream

// Include the UI header file
#include "ui.h"

namespace UI {

// Define constants for special key inputs
const char KEY_UP = 'A';
const char KEY_DOWN = 'B';
const char KEY_RIGHT = 'C';
const char KEY_LEFT = 'D';
const char KEY_ENTER = '\n';
const char KEY_SPACE = ' ';
const char KEY_ESC = 27;
const char KEY_QUIT_LOWER = 'q';
const char KEY_QUIT_UPPER = 'Q';
const char KEY_NULL = 0; // Represents no key or error

namespace Detail {
    void TermiosManager::captureOriginal() {
        if (!initialized && isatty(STDIN_FILENO)) { // Check if stdin is a terminal
            if (tcgetattr(STDIN_FILENO, &original_termios) == 0) {
                initialized = true;
            } else {
                perror("UI::Detail::TermiosManager: tcgetattr failed");
                // Handle error appropriately, maybe throw or log
            }
        }
    }

    const struct termios& TermiosManager::getOriginal() {
        if (!initialized) {
            // Attempt to capture if not done yet, useful if initTerminal wasn't called first
            captureOriginal();
            if (!initialized) {
                // If still not initialized (e.g., stdin not a tty or tcgetattr failed)
                // Return a default-constructed termios? Or handle error.
                // For now, print an error and return the (potentially uninitialized) struct.
                std::cerr << "Warning: UI::Detail::TermiosManager: Original termios not captured." << std::endl;
            }
        }
        return original_termios;
    }

    // Static instance within the detail namespace
    TermiosManager& getTermiosManager() {
        static TermiosManager manager;
        return manager;
    }
} // namespace Detail

namespace Color {
    // Reset
    const std::string RESET = "\033[0m";

    // Regular Colors
    const std::string BLACK = "\033[30m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string WHITE = "\033[37m";

    // Bright Colors
    const std::string BRIGHT_BLACK = "\033[90m";
    const std::string BRIGHT_RED = "\033[91m";
    const std::string BRIGHT_GREEN = "\033[92m";
    const std::string BRIGHT_YELLOW = "\033[93m";
    const std::string BRIGHT_BLUE = "\033[94m";
    const std::string BRIGHT_MAGENTA = "\033[95m";
    const std::string BRIGHT_CYAN = "\033[96m";
    const std::string BRIGHT_WHITE = "\033[97m";

    // Formatting
    const std::string BOLD = "\033[1m";
    const std::string UNDERLINE = "\033[4m";
    const std::string INVERSE = "\033[7m";

    void drawTitle(const std::string& text) {
        std::cout << BRIGHT_MAGENTA
                  << "================================\n"
                  << "  " << BOLD << text << RESET << BRIGHT_MAGENTA << "\n" // Ensure reset doesn't affect border color
                  << "================================\n\n"
                  << RESET;
    }

    void drawMenuItem(const std::string& text, bool selected) {
        if (selected) {
            // Using bright green inverse for selection
            std::cout << INVERSE << BRIGHT_GREEN << " ➤ " << text << " " << RESET;
        } else {
            // Using bright white for non-selected items
            std::cout << BRIGHT_WHITE << "   " << text << " " << RESET;
        }
    }

    void drawWarning(const std::string& text) {
        std::cout << BRIGHT_RED << " ⚠ " << BOLD << text << RESET << "\n";
    }

    void drawSuccess(const std::string& text) {
        std::cout << BRIGHT_GREEN << " ✓ " << BOLD << text << RESET << "\n";
    }
} // namespace Color

// Terminal Control Functions

void clearScreen() {
    std::cout << "\033[2J\033[1;1H" << std::flush;
}

void sleep_ms(int ms) {
    usleep(ms * 1000);
}

void initTerminal() {
    Detail::getTermiosManager().captureOriginal(); // Ensure original settings are stored
    if (!Detail::getTermiosManager().initialized) return; // Don't proceed if capture failed

    struct termios raw = Detail::getTermiosManager().getOriginal();
    // Disable canonical mode (line buffering) and echo
    raw.c_lflag &= ~(ICANON | ECHO);
    // Set minimum characters for read to 1 and timeout to 0 (blocking read)
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) < 0) {
        perror("UI::initTerminal: tcsetattr failed");
    }
}

void resetTerminal() {
    if (Detail::getTermiosManager().initialized) {
        if (tcsetattr(STDIN_FILENO, TCSADRAIN, &Detail::getTermiosManager().getOriginal()) < 0) {
             perror("UI::resetTerminal: tcsetattr failed");
        }
    }
}

char readKeyInput() {
    char c = KEY_NULL;
    ssize_t nread = read(STDIN_FILENO, &c, 1);

    if (nread == -1) {
        perror("UI::readKeyInput: read error");
        return KEY_NULL;
    }
    if (nread == 0) { // Should not happen with VMIN=1, VTIME=0, but handle defensively
         return KEY_NULL;
    }

    if (c == KEY_ESC) { // Check for escape sequence (potential arrow key)
        char seq[3];
        // Try reading the next two characters of the sequence
        if (read(STDIN_FILENO, &seq[0], 1) != 1) return KEY_ESC; // Return ESC if sequence breaks
        if (read(STDIN_FILENO, &seq[1], 1) != 1) return KEY_ESC;

        if (seq[0] == '[') { // Standard ANSI escape sequence prefix
            switch (seq[1]) {
                case 'A': return KEY_UP;
                case 'B': return KEY_DOWN;
                case 'C': return KEY_RIGHT;
                case 'D': return KEY_LEFT;
            }
        }
        // If it was an escape sequence but not an arrow key we recognize,
        // return ESC. Other sequences might exist.
        return KEY_ESC;
    } else if (c == '\r') { // Treat carriage return like newline (Enter)
        return KEY_ENTER;
    } else {
        // Return the character itself (includes KEY_ENTER, KEY_SPACE, letters, etc.)
        return c;
    }
}

// Helper UI Display Functions

void showGameStart(const std::string& course,
                  const std::vector<std::string>& enemies,
                  const std::string& loadingMessage,
                  const std::string& titleColor,
                  const std::string& enemyTitleColor,
                  const std::string& enemyItemColor,
                  int loadTimeMs)
{
    clearScreen();
    std::cout << titleColor << "\n  Preparing " << course << " challenge...\n\n" << Color::RESET;
    std::cout << enemyTitleColor << "  Enemies approaching:\n" << Color::RESET;
    for (const auto& enemy : enemies) {
        std::cout << enemyItemColor << "  " << enemy << "\n" << Color::RESET;
    }
    std::cout << "\n" << Color::BRIGHT_WHITE << "  " << loadingMessage << Color::RESET;
    std::cout.flush();
    sleep_ms(loadTimeMs);
}

void showFinalEncouragement(const std::string& courseName,
                           const std::string& message,
                           const std::string& art)
{
    clearScreen();
    if (!art.empty()) {
         std::cout << Color::BRIGHT_GREEN << art << "\n" << Color::RESET;
    }
    std::cout << Color::BRIGHT_YELLOW << "\n  FINAL COURSE: " << courseName << "\n";
    std::cout << Color::BRIGHT_GREEN << "  " << message << "\n";
    std::cout << Color::BRIGHT_WHITE << "\n  Press any key to continue..." << Color::RESET;
    std::cout.flush();
    readKeyInput(); // Wait for key press
}

void showRecords() {
    clearScreen();
    std::cout << Color::BRIGHT_MAGENTA;
    std::cout << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n";
    std::cout << "█▓▒░░         GAME RECORDS         ░░▒▓█\n";
    std::cout << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\n";
    std::cout << Color::RESET;

    // 读取并显示 record.txt 的内容
    std::ifstream recordFile("record.txt");
    if (recordFile.is_open()) {
        std::string line;
        while (std::getline(recordFile, line)) {
            std::cout << Color::BRIGHT_WHITE << "  " << line << Color::RESET << std::endl;
        }
        recordFile.close();
    } else {
        std::cout << Color::BRIGHT_RED << "  No records found." << Color::RESET << std::endl;
    }

    std::cout << "\n" << Color::BRIGHT_WHITE << "  Press Q to return to main menu..." << Color::RESET << std::endl;
    
    // 等待用户按 Q 键返回
    while (true) {
        char key = readKeyInput();
        if (key == KEY_QUIT_LOWER || key == KEY_QUIT_UPPER) {
            break;
        }
    }
}

MainMenuOption runMainMenu() {
    int selectedOption = 0; // 0: Start, 1: Settings, 2: Records, 3: Exit
    const int maxOption = 3;
    MainMenuOption choice = MainMenuOption::NONE;

    while (choice == MainMenuOption::NONE) {
        clearScreen();

        // Display Title Banner
        std::cout << Color::BRIGHT_MAGENTA;
        std::cout << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n";
        std::cout << "█▓▒░░      ~~ DDL FIGHTER ~~      ░░▒▓█\n";
        std::cout << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\n";
        std::cout << Color::RESET;

        // Display menu options using the drawMenuItem helper
        Color::drawMenuItem("Start Game", selectedOption == 0);
        std::cout << std::endl;
        Color::drawMenuItem("Settings", selectedOption == 1);
        std::cout << std::endl;
        Color::drawMenuItem("Records", selectedOption == 2);
        std::cout << std::endl;
        Color::drawMenuItem("Exit", selectedOption == 3);
        std::cout << std::endl << std::endl;

        // Display Instructions
        std::cout << Color::BRIGHT_WHITE << "\n  ▲▼ Navigate using arrow keys\n";
        std::cout << Color::BRIGHT_WHITE << "  ENTER to select\n" << Color::RESET;

        // Get user input
        char key = readKeyInput();

        switch (key) {
            case KEY_UP: // Up arrow
                selectedOption = (selectedOption > 0) ? selectedOption - 1 : maxOption;
                break;

            case KEY_DOWN: // Down arrow
                selectedOption = (selectedOption < maxOption) ? selectedOption + 1 : 0;
                break;

            case KEY_ENTER: // Enter key selects the option
            case KEY_SPACE: // Also allow space to select
                switch (selectedOption) {
                    case 0: // Start
                        choice = MainMenuOption::START;
                        break;
                    case 1: // Settings
                        choice = MainMenuOption::SETTINGS;
                        break;
                    case 2: // Records
                        showRecords();
                        break;
                    case 3: // Exit
                        clearScreen();
                        std::cout << Color::BRIGHT_MAGENTA << Color::BOLD
                                  << "Exiting DDL FIGHTER. Thanks for playing!\n"
                                  << Color::RESET;
                        sleep_ms(1000);
                        choice = MainMenuOption::EXIT;
                        break;
                }
                break;

            case KEY_QUIT_LOWER: // Allow 'q' to exit directly
            case KEY_QUIT_UPPER:
                clearScreen();
                std::cout << Color::BRIGHT_MAGENTA << Color::BOLD
                          << "Exiting DDL FIGHTER. Thanks for playing!\n"
                          << Color::RESET;
                sleep_ms(1000);
                choice = MainMenuOption::EXIT;
                break;
        }
    } // End while loop

    return choice;
}

SettingsMenuOption runSettingsMenu() {
    int selectedOption = 0; // 0: Back, 1: Reset Progress, 2: Controls
    const int maxOption = 2; // Corresponds to CONTROLS
    SettingsMenuOption choice = SettingsMenuOption::NONE;

    while (choice == SettingsMenuOption::NONE) {
        clearScreen();

        // Display Title Banner
        std::cout << Color::BRIGHT_MAGENTA;
        std::cout << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n";
        std::cout << "█▓▒░░         SETTINGS MENU        ░░▒▓█\n";
        std::cout << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\n";
        std::cout << Color::RESET;

        // Display menu items
        Color::drawMenuItem("Back", selectedOption == 0);
        std::cout << std::endl;
        Color::drawMenuItem("Reset Progress", selectedOption == 1);
        std::cout << std::endl;
        Color::drawMenuItem("Controls", selectedOption == 2);
        std::cout << std::endl << std::endl;

        // Instructions
        std::cout << Color::BRIGHT_WHITE << "\n  ▲▼ Navigate using arrow keys\n";
        std::cout << Color::BRIGHT_WHITE << "  ENTER to select\n" << Color::RESET;

        char key = readKeyInput();

        switch (key) {
            case KEY_UP:
                selectedOption = (selectedOption > 0) ? selectedOption - 1 : maxOption;
                break;

            case KEY_DOWN:
                selectedOption = (selectedOption < maxOption) ? selectedOption + 1 : 0;
                break;

            case KEY_ENTER:
            case KEY_SPACE:
                switch (selectedOption) {
                    case 0: // Back
                        clearScreen();
                        std::cout << Color::BRIGHT_CYAN << "Returning to main menu...\n" << Color::RESET;
                        sleep_ms(500);
                        choice = SettingsMenuOption::BACK; // Signal to exit this menu
                        break;

                    case 1: { // Reset Progress
                        clearScreen();
                        Color::drawWarning("This will erase all your progress!");
                        std::cout << std::endl << std::endl;
                        std::cout << Color::BRIGHT_YELLOW << "Are you sure? ("
                                  << Color::BOLD << "Y" << Color::RESET << Color::BRIGHT_YELLOW << "/"
                                  << Color::BOLD << "N" << Color::RESET << Color::BRIGHT_YELLOW << "): "
                                  << Color::RESET << Color::BRIGHT_WHITE;
                        std::cout.flush();

                        char confirm = readKeyInput();
                        std::cout << confirm << std::endl; // Echo confirmation for visibility

                        if (confirm == 'y' || confirm == 'Y') {
                            // 清空 record.txt 文件
                            std::ofstream recordFile("record.txt", std::ios::trunc);
                            if (recordFile.is_open()) {
                                recordFile.close();
                                Color::drawSuccess("\nProgress reset successfully!");
                            } else {
                                std::cout << Color::BRIGHT_RED << "\nError: Could not reset progress." << Color::RESET;
                            }
                        } else {
                            std::cout << Color::BRIGHT_MAGENTA << "\nReset cancelled." << Color::RESET;
                        }

                        std::cout << Color::BRIGHT_WHITE << "\n\nPress any key to continue..." << Color::RESET;
                        readKeyInput(); // Wait before returning to settings menu
                        break; // Break from inner switch, stay in settings menu
                    }

                    case 2: { // Controls
                        clearScreen();
                        std::cout << Color::BRIGHT_BLUE << Color::BOLD << "CONTROLS:\n\n" << Color::RESET
                                  << Color::BRIGHT_WHITE << "  Navigate:  " << Color::CYAN << "Arrow Keys (▲ ▼)\n" << Color::RESET
								  << Color::BRIGHT_WHITE << "  Select:    " << Color::CYAN << "ENTER\n" << Color::RESET
							      << Color::BRIGHT_WHITE << "  Jump:      " << Color::GREEN << "W\n" << Color::RESET
				                  << Color::BRIGHT_WHITE << "  Move Left: " << Color::GREEN << "A\n" << Color::RESET
				                  << Color::BRIGHT_WHITE << "  Move Right:" << Color::GREEN << "D\n" << Color::RESET
                                  << Color::BRIGHT_WHITE << "  Back/Quit: " << Color::MAGENTA << "Q\n\n" << Color::RESET
                                  << Color::BRIGHT_WHITE << "Press any key to return..." << Color::RESET;
                        readKeyInput(); // Wait before returning to settings menu
                        break; // Break from inner switch, stay in settings menu
                    }
                } // End inner switch (selectedOption)
                if (choice != SettingsMenuOption::NONE) break; // Exit loop if Back was chosen
                break; // End case KEY_ENTER/KEY_SPACE

            case KEY_QUIT_LOWER: // Allow 'q' to function as 'Back'
            case KEY_QUIT_UPPER:
                 clearScreen();
                 std::cout << Color::BRIGHT_CYAN << "Returning to main menu...\n" << Color::RESET;
                 sleep_ms(500);
                 choice = SettingsMenuOption::BACK;
                 break;

        } // End outer switch (key)
    } // End while loop

    return choice;
}

Difficulty runDifficultySelection() {
    int selectedOption = 0; // 0: Easy, 1: Normal, 2: Hard
    const int maxOption = 2;
    Difficulty choice = Difficulty::NONE;

    while (choice == Difficulty::NONE) {
        clearScreen();

        // Title
        std::cout << Color::BRIGHT_MAGENTA;
        std::cout << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n";
        std::cout << "█▓▒░░          DIFFICULTY         ░░▒▓█\n";
        std::cout << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\n";
        std::cout << Color::RESET;
        std::cout << Color::BRIGHT_CYAN << Color::BOLD << "       SELECT YOUR ACADEMIC CHALLENGE\n\n" << Color::RESET;

        // Menu Options
        Color::drawMenuItem(" Easy Mode     (4 Courses)", selectedOption == 0);
        std::cout << std::endl;
        Color::drawMenuItem(" Medium Mode   (5 Courses)", selectedOption == 1);
        std::cout << std::endl;
        Color::drawMenuItem(" Hard Mode     (6 Courses)", selectedOption == 2);
        std::cout << std::endl << std::endl;

        // Instructions
        std::cout << Color::BRIGHT_WHITE << "\n  ▲▼ Navigate using arrow keys\n";
        std::cout << Color::BRIGHT_WHITE << "  ENTER to select\n";
        std::cout << Color::BRIGHT_WHITE << "  Q to go back\n" << Color::RESET;

        char key = readKeyInput();

        switch (key) {
            case KEY_UP:
                selectedOption = (selectedOption > 0) ? selectedOption - 1 : maxOption;
                break;
            case KEY_DOWN:
                selectedOption = (selectedOption < maxOption) ? selectedOption + 1 : 0;
                break;
            case KEY_ENTER:
            case KEY_SPACE:
                clearScreen();
                switch (selectedOption) {
                    case 0:
                        std::cout << Color::BRIGHT_GREEN << Color::BOLD << "  Selected Easy Mode! Loading 4 Courses...\n" << Color::RESET;
                        choice = Difficulty::EASY;
                        break;
                    case 1:
                        std::cout << Color::BRIGHT_YELLOW << Color::BOLD << "  Selected Medium Mode! Loading 5 Courses...\n" << Color::RESET;
                        choice = Difficulty::MEDIUM;
                        break;
                    case 2:
                        std::cout << Color::BRIGHT_RED << Color::BOLD << "  Selected Hard Mode! Loading 6 Courses...\n" << Color::RESET;
                        choice = Difficulty::HARD;
                        break;
                }
                std::cout.flush();
                sleep_ms(1200); // Pause to show selection message
                break; // Exit switch after selection

            case KEY_QUIT_LOWER:
            case KEY_QUIT_UPPER:
                choice = Difficulty::BACK; // Signal to go back
                break;
        } // End switch (key)
    } // End while loop

    return choice;
}

bool runCourseSelection(Difficulty difficulty, int playerLives, int& selectedCourseIndex) {
    std::vector<std::string> courses;
    std::string modeTitle;
    std::string titleColor;
    std::string pathConnector;
    std::string selectedIcon;
    std::string unselectedIcon;
    std::string finalCourseLabelColor;
    int initialLives = playerLives; // Keep track for display

    // Configure based on difficulty
    switch (difficulty) {
        case Difficulty::EASY:
            courses = {"CAES1000", "COMP1117", "APAI1001", "STAT1016"};
            modeTitle = "EASY MODE";
            titleColor = Color::BRIGHT_GREEN;
            pathConnector = Color::BRIGHT_BLUE + "     ║\n     ║\n" + Color::RESET;
            selectedIcon = "🌟";
            unselectedIcon = "🛡️";
            finalCourseLabelColor = Color::BRIGHT_GREEN;
            break;
        case Difficulty::MEDIUM:
            courses = {"CAES1000", "COMP1117", "APAI1001", "STAT1016", "MATH2014"};
             modeTitle = "MEDIUM MODE";
            titleColor = Color::BRIGHT_CYAN; // Changed from original for variety
            pathConnector = Color::BRIGHT_BLACK + "     │\n     │\n" + Color::RESET;
            selectedIcon = "⚔️";
            unselectedIcon = "○";
            finalCourseLabelColor = Color::BRIGHT_RED; // Keep final boss distinct
            break;
        case Difficulty::HARD:
            courses = {"CAES1000", "COMP1117", "APAI1001", "STAT1016", "MATH2014", "STAT2601"};
            modeTitle = "HARD MODE";
            titleColor = Color::BRIGHT_RED;
            pathConnector = Color::BRIGHT_RED + "     ║\n     ║\n" + Color::RESET; // Intense connector
            selectedIcon = "🔥";
            unselectedIcon = "☠";
            finalCourseLabelColor = Color::BRIGHT_RED;
            break;
        default: // Should not happen if called correctly
            std::cerr << "Error: Invalid difficulty passed to runCourseSelection." << std::endl;
            return false;
    }

    int currentSelection = 0; // Start at the first course
    bool exitMap = false;
    bool courseChosen = false;

    while (!exitMap) {
        clearScreen();

        // Draw Title
        std::cout << titleColor;
        std::cout << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n";
        std::cout << "█▓▒░░          " << std::left << std::setw(14) << modeTitle << "       ░░▒▓█\n"; // Adjust spacing for title length
        std::cout << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\n";
        std::cout << Color::RESET;

        // Top status bar (using initialLives for display consistency)
        std::cout << Color::BRIGHT_RED << "  Lives: " << initialLives;
         // Use different heart icons based on difficulty maybe? For now, consistent.
        if (difficulty == Difficulty::HARD) std::cout << " 💔";
        else if (difficulty == Difficulty::MEDIUM) std::cout << " ❤️";
        else std::cout << " 💖"; // Easy gets a fancy heart
        std::cout << "  " << Color::RESET << "\n\n";


        // Course path visualization
        for (size_t i = 0; i < courses.size(); ++i) {
            std::string courseDisplay;
            if (static_cast<int>(i) == currentSelection) {
                // Highlight selected course
                courseDisplay = Color::INVERSE + titleColor + "   " + selectedIcon + " " + courses[i] + " " + Color::RESET;
            } else {
                // Display non-selected course
                courseDisplay = "   " + unselectedIcon + " " + Color::BRIGHT_WHITE + courses[i] + " " + Color::RESET;
            }
            std::cout << courseDisplay;

            // Add special labels (Starting Point, Final Course)
            if (i == 0) {
                std::cout << " " << Color::BRIGHT_BLUE << "(Starting Point)";
            } else if (i == courses.size() - 1) {
                std::cout << " " << finalCourseLabelColor << Color::BOLD << "(FINAL COURSE)" << Color::RESET;
            }

            // Add action prompt for the currently selected course
             if (static_cast<int>(i) == currentSelection) {
                std::cout << " " << Color::BRIGHT_YELLOW << Color::BOLD << "[SELECT]" << Color::RESET;
             }

            std::cout << "\n";

            // Draw path connectors between courses
            if (i < courses.size() - 1) {
                std::cout << pathConnector;
            }
        }

        // Instructions
        std::cout << "\n" << Color::BRIGHT_WHITE << "  ▲▼ Navigate using arrow keys\n";
        std::cout << Color::BRIGHT_GREEN << "  ENTER to select course\n";
        std::cout << Color::BRIGHT_WHITE << "  Q to exit to main menu\n" << Color::RESET;

        // Get input
        char key = readKeyInput();

        switch (key) {
            case KEY_UP:
                currentSelection = std::max(0, currentSelection - 1);
                break;

            case KEY_DOWN:
                currentSelection = std::min(static_cast<int>(courses.size() - 1), currentSelection + 1);
                break;

            case KEY_ENTER:
            case KEY_SPACE:
                // Check if it's the final course to show special message
                if (currentSelection == static_cast<int>(courses.size() - 1)) {
                    if (difficulty == Difficulty::HARD) {
                         showFinalEncouragement(courses[currentSelection],
                                               "Prepare to face the legendary Probability Dragon!",
                                               R"(
  ▄████████  ▄█        ▄█  ███▄▄▄▄   ███    █▄     ▄████████
 ███    ███ ███       ███  ███▀▀▀██▄ ███    ███   ███    ███
 ███    █▀  ███       ███▌ ███   ███ ███    ███   ███    █▀
 ███        ███       ███▌ ███   ███ ███    ███  ▄███▄▄▄
▀███████████ ███       ███▌ ███   ███ ███    ███ ▀▀███▀▀▀
        ███ ███       ███  ███   ███ ███    ███   ███    █▄
  ▄█    ███ ███▌    ▄ ███  ███   ███ ███    ███   ███    ███
▄████████▀  █████▄▄██ █▀    ▀█   █▀  ████████▀    ██████████
           ▀
                                               )"); // Boss ASCII Art
                    } else { // Easy and Medium final encouragement
                         showFinalEncouragement(courses[currentSelection],
                                               "You've got this! Show what you've learned!",
                                               R"(
   _____                 _ _
  / ____|               | | |
 | |  __  ___   ___   __| | |
 | | |_ |/ _ \ / _ \ / _` | |
 | |__| | (_) | (_) | (_| |_|
  \_____|\___/ \___/ \__,_(_)
                                               )"); // Generic "Good Luck" Art
                    }
                }

                // Set the chosen course index and flags to exit the loop
                selectedCourseIndex = currentSelection;
                courseChosen = true;
                exitMap = true;
                break; // Exit switch after selection

            case KEY_QUIT_LOWER:
            case KEY_QUIT_UPPER:
                exitMap = true; // Exit loop, courseChosen remains false
                courseChosen = false;
                break;

            // Ignore other keys like Left/Right for now in this menu
            case KEY_LEFT:
            case KEY_RIGHT:
                 break;

        } // End switch (key)
    } // End while loop

    // If a course was chosen, show the appropriate game start sequence
    if (courseChosen) {
        std::vector<std::string> enemies;
        std::string loadingMsg;
        std::string startTitleColor;
        int loadTime = 1500;

         switch (difficulty) {
             case Difficulty::EASY:
                enemies = {"📚 Study Buddies", "🧮 Math Mascots", "⏳ Time Tutors"};
                loadingMsg = "Loading beginner-friendly environment...";
                startTitleColor = Color::BRIGHT_GREEN;
                break;
            case Difficulty::MEDIUM:
                enemies = {"- Deadline Demons", "- Procrastination Phantoms", "- Time-Crunch Titans"};
                loadingMsg = "Loading game assets...";
                startTitleColor = Color::BRIGHT_GREEN; // Keep green for start message consistency
                loadTime = 2000;
                break;
            case Difficulty::HARD:
                enemies = {"☠️ Thesis Terminators", "💀 Final Exam Fiends", "👹 Project Demons", "🧟 Deadline Zombies"};
                loadingMsg = "Loading extreme challenge...";
                startTitleColor = Color::BRIGHT_RED; // Red for hard mode start
                loadTime = 3000;
                break;
            default: break; // Should not happen
        }
        // Call the generalized showGameStart
         showGameStart(courses[selectedCourseIndex], enemies, loadingMsg, startTitleColor,
                      (difficulty == Difficulty::HARD ? Color::BRIGHT_MAGENTA : Color::BRIGHT_YELLOW), // Enemy title color variation
                      (difficulty == Difficulty::HARD ? Color::BRIGHT_RED : Color::BRIGHT_CYAN), // Enemy item color variation
                      loadTime);
    }

    return courseChosen; // Return true if a course was selected, false if user quit
}

// Helper function to generate sample grades for testing the final screen
std::vector<std::pair<std::string, char>> generateSampleGrades(Difficulty difficulty) {
    std::vector<std::pair<std::string, char>> grades;
    std::vector<std::string> courses;
    int numCourses = 4; // Default for Easy

    switch (difficulty) {
        case Difficulty::EASY:
            courses = {"CAES1000", "COMP1117", "APAI1001", "STAT1016"};
            numCourses = 4;
            break;
        case Difficulty::MEDIUM:
            courses = {"CAES1000", "COMP1117", "APAI1001", "STAT1016", "MATH2014"};
            numCourses = 5;
            break;
        case Difficulty::HARD:
            courses = {"CAES1000", "COMP1117", "APAI1001", "STAT1016", "MATH2014", "STAT2601"};
            numCourses = 6;
            break;
        default: // Should not happen, but default to easy courses
             courses = {"CAES1000", "COMP1117", "APAI1001", "STAT1016"};
             numCourses = 4;
             break;
    }

    // 只使用ABC三个等级
    char possibleGrades[] = {'A', 'B', 'C'};
    int numPossible = sizeof(possibleGrades) / sizeof(char);

    for (int i = 0; i < numCourses; ++i) {
        grades.push_back({courses[i], possibleGrades[rand() % numPossible]});
    }

    return grades;
}

// Helper function to calculate a sample GPA based on grades
float calculateSampleGpa(const std::vector<std::pair<std::string, char>>& grades) {
    float totalPoints = 0.0f;
    int numCourses = grades.size();

    for (const auto& grade : grades) {
        switch (grade.second) {
            case 'A':
                totalPoints += 4.0f;
                break;
            case 'B':
                totalPoints += 3.0f;
                break;
            case 'C':
                totalPoints += 2.0f;
                break;
            default:
                totalPoints += 0.0f;
                break;
        }
    }

    return numCourses > 0 ? totalPoints / numCourses : 0.0f;
}

// Chinese version
void displayGameResults(const std::vector<std::pair<std::string, char>>& grades, float gpa) {
    clearScreen();

    // 根据GPA确定总体结果
    bool isPass = gpa >= 2.0; // 假设2.0是及格线
    std::string resultText = isPass ? "学业胜利！" : "学业警告";
    std::string resultSymbol = isPass ? "🎓" : "💀";
    std::string resultColor = isPass ? Color::BRIGHT_GREEN : Color::BRIGHT_RED;

    // 显示标题
    std::cout << Color::BRIGHT_MAGENTA;
    std::cout << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n";
    std::cout << "█▓▒░░      ~ 成绩发布 ~      ░░▒▓█\n";
    std::cout << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\n";
    std::cout << Color::RESET;

    // 显示总体结果
    std::cout << resultColor << "  " << resultSymbol << "  " << Color::BOLD << resultText << Color::RESET << resultColor << "  " << resultSymbol << "\n\n" << Color::RESET;

    // 显示成绩表头
    std::cout << Color::BRIGHT_WHITE << "  课程         成绩       状态\n";
    std::cout << Color::BRIGHT_BLACK << "  ────────────────────────────────────\n" << Color::RESET;

    // 遍历并显示每门课程的成绩
    for (const auto& course : grades) {
        std::string gradeColor = Color::BRIGHT_WHITE; // 默认颜色
        char gradeChar = course.second;

        // 根据成绩分配颜色
        if (gradeChar == 'A') gradeColor = Color::BRIGHT_GREEN;
        else if (gradeChar == 'B') gradeColor = Color::BRIGHT_CYAN;
        else if (gradeChar == 'C') gradeColor = Color::BRIGHT_YELLOW;
        else if (gradeChar == 'D') gradeColor = Color::BRIGHT_RED;
        else gradeColor = Color::BRIGHT_RED;

        // 打印课程名称、成绩（带颜色）和状态
        std::cout << Color::BRIGHT_WHITE << "  " << std::left << std::setw(12) << course.first
                  << "   " << gradeColor << std::setw(3) << gradeChar << Color::RESET
                  << Color::BRIGHT_WHITE << "      ";

        // 确定通过/未通过状态
        if (gradeChar >= 'A' && gradeChar <= 'D') {
            std::cout << Color::BRIGHT_GREEN << "✓ 通过" << Color::RESET;
        } else {
            std::cout << Color::BRIGHT_RED << "✗ 未通过" << Color::RESET;
        }
        std::cout << "\n";
    }

    // 显示最终GPA（带颜色编码）
    std::cout << "\n" << Color::BRIGHT_WHITE << "  最终GPA: ";
    if (gpa >= 3.5) std::cout << Color::BRIGHT_GREEN;
    else if (gpa >= 2.5) std::cout << Color::BRIGHT_CYAN;
    else if (gpa >= 2.0) std::cout << Color::BRIGHT_YELLOW;
    else std::cout << Color::BRIGHT_RED;

    // 显示GPA值，格式化为一位小数
    std::cout << Color::BOLD << "✦ " << std::fixed << std::setprecision(1) << gpa << " ✦" << Color::RESET << "\n\n";

    // 退出提示
    std::cout << Color::BRIGHT_WHITE << "  按 " << Color::BOLD << "Q" << Color::RESET << Color::BRIGHT_WHITE << " 退出游戏\n";
    std::cout << Color::RESET << std::flush;

    // 等待用户按'q'或'Q'退出
    while (true) {
        char key = readKeyInput();
        if (key == KEY_QUIT_LOWER || key == KEY_QUIT_UPPER) {
            break;
        }
    }
}

// English version
void displayFinalScreen(const std::vector<std::pair<std::string, char>>& grades, float gpa) {
    clearScreen();

    // Determine overall result based on GPA
    bool isPass = gpa >= 2.0; // Assuming 2.0 is the passing threshold
    std::string resultText = isPass ? "ACADEMIC VICTORY!" : "ACADEMIC PROBATION";
    std::string resultSymbol = isPass ? "🎓" : "💀";
    std::string resultColor = isPass ? Color::BRIGHT_GREEN : Color::BRIGHT_RED;

    // Display title using the Color namespace function
    std::cout << Color::BRIGHT_MAGENTA;
    std::cout << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n";
    std::cout << "█▓▒░░      ~ GRADE RELEASE ~      ░░▒▓█\n";
    std::cout << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\n";
    std::cout << Color::RESET;

    // Display overall result
    std::cout << resultColor << "  " << resultSymbol << "  " << Color::BOLD << resultText << Color::RESET << resultColor << "  " << resultSymbol << "\n\n" << Color::RESET;

    // Display header for the grade table
    std::cout << Color::BRIGHT_WHITE << "  COURSE         GRADE       STATUS\n";
    std::cout << Color::BRIGHT_BLACK << "  ────────────────────────────────────\n" << Color::RESET;

    // Loop through grades and display each course
    for (const auto& course : grades) {
        std::string gradeColor = Color::BRIGHT_WHITE; // Default color
        char gradeChar = course.second;

        // Assign color based on grade
        if (gradeChar == 'A') gradeColor = Color::BRIGHT_GREEN;
        else if (gradeChar == 'B') gradeColor = Color::BRIGHT_CYAN;
        else if (gradeChar == 'C') gradeColor = Color::BRIGHT_YELLOW;
        else if (gradeChar == 'D') gradeColor = Color::BRIGHT_RED; // D might be passing but low
        else gradeColor = Color::BRIGHT_RED; // Assume F or other non-passing grades are red

        // Print course name, grade (with color), and status
        std::cout << Color::BRIGHT_WHITE << "  " << std::left << std::setw(12) << course.first
                  << "   " << gradeColor << std::setw(3) << gradeChar << Color::RESET // Reset after grade color
                  << Color::BRIGHT_WHITE << "      "; // Spacing before status

        // Determine pass/fail status (assuming D is the lowest passing grade)
        if (gradeChar >= 'A' && gradeChar <= 'D') {
            std::cout << Color::BRIGHT_GREEN << "✓ Passed" << Color::RESET;
        } else {
            std::cout << Color::BRIGHT_RED << "✗ Failed" << Color::RESET;
        }
        std::cout << "\n";
    }

    // Display Final GPA with color coding
    std::cout << "\n" << Color::BRIGHT_WHITE << "  FINAL GPA: ";
    if (gpa >= 3.5) std::cout << Color::BRIGHT_GREEN;
    else if (gpa >= 2.5) std::cout << Color::BRIGHT_CYAN;
    else if (gpa >= 2.0) std::cout << Color::BRIGHT_YELLOW;
    else std::cout << Color::BRIGHT_RED;

    // Show GPA value, formatted to one decimal place
    std::cout << Color::BOLD << "✦ " << std::fixed << std::setprecision(1) << gpa << " ✦" << Color::RESET << "\n\n";

    // Instructions to quit
    std::cout << Color::BRIGHT_WHITE << "  Press " << Color::BOLD << "Q" << Color::RESET << Color::BRIGHT_WHITE << " to quit game\n";
    std::cout << Color::RESET << std::flush;

    // Wait for the user to press 'q' or 'Q' to exit
    while (true) {
        char key = readKeyInput();
        if (key == KEY_QUIT_LOWER || key == KEY_QUIT_UPPER) {
            break;
        }
    }
}

} // namespace UI