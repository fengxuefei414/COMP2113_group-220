#include <iostream>
#include <vector>
#include <unistd.h>
#include <ctime>
#include <string>
#include "user_control.h"
#include "DUE.h"
#include "All_maps/map1001.h"
#include "All_maps/map1117.h"
#include "All_maps/map1000.h"
#include "All_maps/map1016.h"
#include "All_maps/map2014.h"
#include "All_maps/map2601.h"
#include "Incidents/incidents.h"
#include "health_system.h"
#include "score_system.h"
#include "ui.h" 
#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace std;


// Structure to record game incidents
struct IncidentRecord {
    string message;      
    time_t startTime;    
    int level;          
};

// Game constants
const float GRAVITY = 0.3f;        
const float JUMP_FORCE = -0.9f;     
const float TERMINAL_FPS = 30.0f;   

// Current level
int currentLevel = 1;
int MAX_LEVEL = 6;

// Time related variables
time_t levelStartTime;  
int currentLevelTime;   

// Event record related variables
vector<IncidentRecord> incidentRecords;  

// Structure for spawn points
struct SpawnPoint {
    int x;
    int y;
};

// Each level's spawn point (temporarily use the same spawn point)
const SpawnPoint LEVEL_SPAWNS[] = {
    {5, 13},    // Level 1
    {5, 13},    // Level 2
    {5, 13},    // Level 3
    {5, 9},     // Level 4
    {5, 5},     // Level 5
    {5, 15}     // Level 6
};

// Get spawn point for current level
SpawnPoint getCurrentSpawnPoint() {
    return LEVEL_SPAWNS[currentLevel - 1];
}

// Difficulty enum
enum Difficulty {
    EASY,
    MEDIUM,
    HARD
};

// Add global variable to store current difficulty
Difficulty currentDifficulty;

// Load level map and initialize game state
void loadLevel(vector<vector<char> >& map, int level) {
    // Check if it exceeds the maximum level number of the current difficulty
    switch(currentDifficulty) {
        case EASY:
            MAX_LEVEL = 4;  
            break;
        case MEDIUM:
            MAX_LEVEL = 5;  
            break;
        case HARD:
            MAX_LEVEL = 6;  
            break;
    }
    
    if (level > MAX_LEVEL) {
        cout << "Congratulations! You've completed all levels!" << endl;
        cout << "Final Score: " << getLevelScores().back().totalScore << endl;
        exit(0);
    }

    // Reset timer
    levelStartTime = time(nullptr);
    currentLevelTime = 0;
    
    // Initialize DUE
    initDUE();
    
    switch(level) {
        case 1:
            generateMap1001(map);
            break;
        case 2:
            generateMap1117(map);
            break;
        case 3:
            generateMap1000(map);
            break;
        case 4:
            generateMap1016(map);
            break;
        case 5:
            generateMap2014(map);
            break;
        case 6:
            generateMap2601(map);
            break;
        default:
            generateMap1001(map);
            break;
    }
}

// Player state structure
struct Player {
    int x;
    int y;
    float velocityX;
    float velocityY;
    bool isJumping;
    char symbol;
    int lastSafeX;  
    int lastSafeY;  
    HealthSystem health;
};

// Check if position contains a platform
bool isPlatform(const vector<vector<char> >& map, int x, int y) {
    if (y < 0 || y >= MAP_HEIGHT || x < 0 || x >= MAP_WIDTH) {
        return false;
    }
    char c = map[y][x];
    return (c == '-' || c == 'v' || c == '[' || c == ']' || c == '|'|| c == '#');
}

// Check if position is a level switch point
bool isLevelSwitch(const vector<vector<char> >& map, int x, int y) {
    if (y < 0 || y >= MAP_HEIGHT || x < 0 || x >= MAP_WIDTH) {
        return false;
    }
    char c = map[y][x];
    return (c == '[' || c == ']');
}

// Check if position contains a trap
bool isTrap(const vector<vector<char> >& map, int x, int y) {
    if (y < 0 || y >= MAP_HEIGHT || x < 0 || x >= MAP_WIDTH) {
        return false;
    }
    char c = map[y][x];
    return (c == 'v');
}

// Update player position and handle collisions
void updatePlayer(Player& player, vector<vector<char> >& map) {
    // Check if position contains DUE
    if (checkDUECollision(map, player.x, player.y)) {
        // Directly set health to 0
        player.health.health = 0;
        
        // If dead, enter next level
        if (currentLevel < MAX_LEVEL) {
            // Calculate current level score
            calculateLevelScore(currentLevel, currentLevelTime, player.health.health);
            
            currentLevel++;
            loadLevel(map, currentLevel);
            // Use spawn point of new level
            SpawnPoint spawn = getCurrentSpawnPoint();
            player.x = spawn.x;
            player.y = spawn.y;
            player.velocityX = 0;
            player.velocityY = 0;
            player.isJumping = false;
            player.lastSafeX = spawn.x;
            player.lastSafeY = spawn.y;
            resetHealth(player.health); // Reset health
        } else {
            // Calculate final level score
            calculateLevelScore(currentLevel, currentLevelTime, player.health.health);
            
            // Display all level scores
            system("clear");
            displayLevelScores();
            cout << "\nCongratulations!" << endl;
            exit(0);
        }
    }
    
    // Check if position is on a trap (check character's position below)
    if (player.velocityY > 0 && isTrap(map, player.x, player.y + 1)) {
        // Handle injury
        if (handleDamage(player.health)) {
            // If dead, enter next level
            if (currentLevel < MAX_LEVEL) {
                // Calculate current level score
                calculateLevelScore(currentLevel, currentLevelTime, player.health.health);
                
                currentLevel++;
                loadLevel(map, currentLevel);
                SpawnPoint spawn = getCurrentSpawnPoint();
                player.x = spawn.x;
                player.y = spawn.y;
                player.velocityX = 0;
                player.velocityY = 0;
                player.isJumping = false;
                player.lastSafeX = spawn.x;
                player.lastSafeY = spawn.y;
                resetHealth(player.health);
            } else {
                // Calculate final level score
                calculateLevelScore(currentLevel, currentLevelTime, player.health.health);
                
                // Display all level scores
                system("clear");
                displayLevelScores();
                cout << "\nCongratulations!" << endl;
                exit(0);
            }
        }
        
        // Return to previous safe position
        player.x = player.lastSafeX;
        player.y = player.lastSafeY;
        player.velocityX = 0;
        player.velocityY = 0;
        player.isJumping = false;
        return;
    }
    
    // Update invincible state
    updateInvincibility(player.health);
    
    // Check if position is a level switch point
    if (isLevelSwitch(map, player.x, player.y)) {
        if (currentLevel < MAX_LEVEL) {
            // Calculate current level score
            calculateLevelScore(currentLevel, currentLevelTime, player.health.health);
            
            currentLevel++;
            loadLevel(map, currentLevel);
            // Use spawn point of new level
            SpawnPoint spawn = getCurrentSpawnPoint();
            player.x = spawn.x;
            player.y = spawn.y;
            player.velocityX = 0;
            player.velocityY = 0;
            player.isJumping = false;
            resetHealth(player.health);
        } else {
            // Calculate final level score
            calculateLevelScore(currentLevel, currentLevelTime, player.health.health);
            
            // Display all level scores
            system("clear");
            displayLevelScores();
            cout << "\nCongratulations!" << endl;
            exit(0);
        }
    }
    
    // Check if position contains $
    if (map[player.y][player.x] == '$') {
        currentLevelTime = static_cast<int>(time(nullptr) - levelStartTime);
        IncidentType incident = triggerRandomIncident(currentLevelTime, player.health);
        
        // Create new event record
        IncidentRecord newRecord;
        //newRecord.message = "触发随机事件：" + getIncidentName(incident);
        newRecord.message = getIncidentName(incident);
        newRecord.startTime = time(nullptr);
        newRecord.level = currentLevel;
        
        // Add to event record list
        incidentRecords.push_back(newRecord);
        
        levelStartTime = time(nullptr) - currentLevelTime;  // Update start time to reflect reduced time
        map[player.y][player.x] = ' ';  // Remove $
    }
    
    // Apply gravity
    player.velocityY += GRAVITY;
    
    // Limit maximum falling speed
    if (player.velocityY > 1.0f) {  // Reduce maximum falling speed
        player.velocityY = 1.0f;
    }
    
    // Update vertical position
    float newY = player.y + player.velocityY;
    int newYInt = static_cast<int>(newY);
    
    // Check if reach maximum jump height (2 cells)
    if (player.velocityY < 0 && newY < player.y - 2.0f) {
        newY = player.y - 2.0f;
        player.velocityY = 0;
    }
    
    // Check vertical collision
    if (player.velocityY > 0) {  // Falling
        if (newYInt >= MAP_HEIGHT || isPlatform(map, player.x, newYInt)) {
            player.y = newYInt - 1;
            player.velocityY = 0;
            player.velocityX = 0;  // Reset horizontal speed
            player.isJumping = false;
            // Update safe position
            player.lastSafeX = player.x;
            player.lastSafeY = player.y;
        } else {
            player.y = newY;
        }
    } else if (player.velocityY < 0) {  // Rising
        if (newYInt < 0 || isPlatform(map, player.x, newYInt)) {
            player.y = newYInt + 1;
            player.velocityY = 0;
            player.velocityX = 0;  // Reset horizontal speed
            // Update safe position
            player.lastSafeX = player.x;
            player.lastSafeY = player.y;
        } else {
            player.y = newY;
        }
    }
    
    // Update horizontal position
    float newX = player.x + player.velocityX;
    int newXInt = static_cast<int>(newX);
    
    // Reduce horizontal movement speed when jumping
    if (player.isJumping && player.velocityX < 0) {
        newX = player.x + player.velocityX * 0.5f; // Reduce horizontal speed by 50%
        newXInt = static_cast<int>(newX);
    }
    
    // Check horizontal movement path collision
    if (player.velocityX > 0) { // Moving right
        for (int x = player.x; x <= newXInt; x++) {
            if (isPlatform(map, x, player.y)) {
                player.velocityX = 0;
                player.x = x - 1;
                return;
            }
        }
    } else if (player.velocityX < 0) { // Moving left
        for (int x = player.x; x >= newXInt; x--) {
            if (isPlatform(map, x, player.y)) {
                player.velocityX = 0;
                player.x = x + 1;
                return;
            }
        }
    }
    
    // If no collision, update position
    player.x = newXInt;
    
    // Check if out of map boundary
    if (player.x < 0) player.x = 0;
    if (player.x >= MAP_WIDTH) player.x = MAP_WIDTH - 1;
}

// Display game screen with current state
void displayGame(const vector<vector<char> >& map, const Player& player) {
    // Use ANSI escape sequence to move cursor to top left corner, instead of clearing screen
    cout << "\033[1;1H";  // Move cursor to top left corner
    
    // Update current level use time
    currentLevelTime = static_cast<int>(time(nullptr) - levelStartTime);
    
    // Copy map
    vector<vector<char> > displayMap = map;
    
    // Place player
    if (player.y >= 0 && player.y < MAP_HEIGHT && player.x >= 0 && player.x < MAP_WIDTH) {
        displayMap[player.y][player.x] = player.symbol;
    }
    
    // Display map
    for (int i = 0; i < MAP_HEIGHT; ++i) {
        for (int j = 0; j < MAP_WIDTH; ++j) {
            if (displayMap[i][j] == '$') {
                // Output golden $
                cout << "\033[33m" << displayMap[i][j] << "\033[0m";
            } else if (displayMap[i][j] == 'v') {
                // Output red trap
                cout << "\033[31m" << displayMap[i][j] << "\033[0m";
            } else if (displayMap[i][j] == '|') {
                // Output green wall
                cout << "\033[32m" << displayMap[i][j] << "\033[0m";
            } else if (displayMap[i][j] == '[' || displayMap[i][j] == ']') {
                // Output golden door
                cout << "\033[33m" << displayMap[i][j] << "\033[0m";
            } else if (i == player.y && j == player.x) {
                // Use green to display player
                cout << "\033[32m" << displayMap[i][j] << "\033[0m";
            } else {
                // Normal character display
                cout << displayMap[i][j];
            }
        }
        cout << endl;
    }
    
    // Display map name according to current level
    string mapName;
    switch(currentLevel) {
        case 1: mapName = "APAI1001"; break;
        case 2: mapName = "COMP1117"; break;
        case 3: mapName = "CAES1000"; break;
        case 4: mapName = "STAT1016"; break;
        case 5: mapName = "MATH2014"; break;
        case 6: mapName = "STAT2601"; break;
    }
    
    // First display health value and level information
    cout << "----------------------------------------" << endl;
    cout << "Lives: " << getCurrentHealth(player.health) << "/4   ";
    // Display heart icon according to health value
    if(getCurrentHealth(player.health) == 4) cout << "❤️‍🔥❤️‍🔥❤️‍🔥❤️‍🔥　　　　　";
    else if(getCurrentHealth(player.health) == 3) cout << "❤️❤️❤️　　　　";
    else if(getCurrentHealth(player.health) == 2) cout << "💔💔　　　　　";
    else if(getCurrentHealth(player.health) == 1) cout << "💔　　　　　　";
    cout << endl;
    cout << "Level " << currentLevel << "/" << MAX_LEVEL << " (" << mapName << ")" << endl;
    cout << "Time: " << currentLevelTime << " seconds  " << endl<<endl;

    // Display current level event records
    //cout << "Current level event records:" << endl;
    int randomEventCounter = 1;
    for (const auto& record : incidentRecords) {
        if (record.level == currentLevel) {
	    cout << "Random Event " <<currentLevel<<"-"<<randomEventCounter << ": "<< record.message<<endl;
	    randomEventCounter++;
        }                                                                                                                             
    }

    // Flush output buffer
    cout.flush();
}

// Declare external variable
extern int DUEPosition;
HealthSystem playerHealth;  // Add player health system

// Select game difficulty level
Difficulty selectDifficulty() {
    cout << "Select difficulty level:" << endl;
    cout << "1. Easy (First 4 chapters)" << endl;
    cout << "2. Medium (First 5 chapters)" << endl;
    cout << "3. Hard (All 6 chapters)" << endl;
    cout << "Enter number (1-3): ";

    int choice;
    while (true) {
        cin >> choice;
        if (choice >= 1 && choice <= 3) {
            break;
        }
        cout << "Invalid choice, please enter again (1-3): ";
    }

    return static_cast<Difficulty>(choice - 1);
}

// Modify gameLoop function declaration, add difficulty parameter
void gameLoop(Difficulty difficulty);

// Main game entry point
int main() {
    // Initialize random number generator
    srand(time(0));
    
    // Initialize terminal
    UI::initTerminal();
    
    bool exitGame = false;
    
    while (!exitGame) {
        // Display main menu and get user choice
        UI::MainMenuOption menuChoice;
        do {
            menuChoice = UI::runMainMenu();
            
            if (menuChoice == UI::MainMenuOption::SETTINGS) {
                UI::runSettingsMenu();  // Display settings menu
                // Display main menu again after settings menu returns
            }
        } while (menuChoice == UI::MainMenuOption::SETTINGS);
        
        // If user chooses to exit
        if (menuChoice == UI::MainMenuOption::EXIT) {
            exitGame = true;
            continue;
        }
        
        // If user chooses to start game
        if (menuChoice == UI::MainMenuOption::START) {
            // Select difficulty
            UI::Difficulty uiDifficulty = UI::runDifficultySelection();
            if (uiDifficulty == UI::Difficulty::BACK || uiDifficulty == UI::Difficulty::NONE) {
                continue;  // Return to main menu
            }
            
            // Convert UI difficulty to game difficulty
            Difficulty gameDifficulty;
            switch(uiDifficulty) {
                case UI::Difficulty::EASY:
                    gameDifficulty = EASY;
                    break;
                case UI::Difficulty::MEDIUM:
                    gameDifficulty = MEDIUM;
                    break;
                case UI::Difficulty::HARD:
                    gameDifficulty = HARD;
                    break;
                default:
                    gameDifficulty = EASY;
                    break;
            }
            
            // Call course selection map UI
            int selectedCourseIndex = 0;
            bool courseChosen = UI::runCourseSelection(uiDifficulty, 4, selectedCourseIndex); // Assume initial health value is 4
            
            // If user selects a course, start game
            if (courseChosen) {
                // Set starting level based on selected course
                currentLevel = selectedCourseIndex + 1;
                
                // Display start interface
                std::vector<std::string> enemies = {"DUE", "Time Record", "Trap"};
                UI::showGameStart("DDL Fighter", enemies, "Loading...");
                
                // Run game
                gameLoop(gameDifficulty);
                // If gameLoop returns normally, it means user pressed Q key
                // Will continue to loop back to main menu
            }
        }
    }
    
    displayLevelScores();
    
    // Reset terminal
    UI::resetTerminal();
    return 0;
}

// Main game loop
void gameLoop(Difficulty difficulty) {
    currentDifficulty = difficulty;  // Set current difficulty
    vector<vector<char> > map(MAP_HEIGHT, vector<char>(MAP_WIDTH));
    Player player;
    player.symbol = 'H';  // Change character symbol to 'H'
    HealthSystem playerHealth;
    initHealth(playerHealth);  // Initialize health value system
    player.health = playerHealth;

    // Initialize map
    loadLevel(map, currentLevel);
    
    // Get initial spawn point
    SpawnPoint spawn = getCurrentSpawnPoint();
    
    // Initialize player
    player = {
        .x = spawn.x,
        .y = spawn.y,
        .velocityX = 0.0f,
        .velocityY = 0.0f,
        .isJumping = false,
        .symbol = 'H',
        .lastSafeX = spawn.x,
        .lastSafeY = spawn.y,
    };
    initHealth(player.health); // Initialize health value system
    initHealth(playerHealth); // Initialize health value system
    
    // Initialize user control
    UserControl controller;
    // Game main loop
    while (true) {
        // Handle user input
        controller.handleInput(player.x, player.y, player.isJumping, 
                            player.velocityY, player.velocityX, JUMP_FORCE, MAP_WIDTH);
        
        // Check if need to return to main menu
        if (controller.returnToMainMenu) {
            return;  // Return to caller (main function)
        }
        
        // Update DUE
        updateDUE(map);
        
        // Update player position
        updatePlayer(player, map);
        
        // Display game screen
        displayGame(map, player);
        
        // Control frame rate
        usleep(1000000 / TERMINAL_FPS);
        
        // Update DUE pause state
        updateDUEPause();

        // Check if reach next level
        if (isLevelSwitch(map, player.x, player.y)) {
            currentLevel++;
            if (currentLevel > MAX_LEVEL) {
                // Calculate final score
                std::vector<std::pair<std::string, char>> finalGrades;
                std::vector<std::string> courseNames;
                
                // Set course name according to difficulty
                switch(difficulty) {
                    case EASY:
                        courseNames = {"CAES1000", "COMP1117", "APAI1001", "STAT1016"};
                        break;
                    case MEDIUM:
                        courseNames = {"CAES1000", "COMP1117", "APAI1001", "STAT1016", "MATH2014"};
                        break;
                    case HARD:
                        courseNames = {"CAES1000", "COMP1117", "APAI1001", "STAT1016", "MATH2014", "STAT2601"};
                        break;
                }
                
                // Get score of each level
                const auto& scores = getLevelScores();
                for (size_t i = 0; i < scores.size() && i < courseNames.size(); ++i) {
                    finalGrades.push_back({courseNames[i], scores[i].grade});
                }
                
                float finalGpa = calculateGPA();
                
                // Use new UI to display final score
                UI::displayFinalScreen(finalGrades, finalGpa);
                return;
            }
            loadLevel(map, currentLevel);
            SpawnPoint spawn = getCurrentSpawnPoint();
            player.x = spawn.x;
            player.y = spawn.y;
            player.velocityX = 0.0f;
            player.velocityY = 0.0f;
            player.isJumping = false;
            player.lastSafeX = spawn.x;
            player.lastSafeY = spawn.y;
            levelStartTime = time(nullptr);
        }
    }
} 