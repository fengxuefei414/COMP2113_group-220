#ifndef INCIDENTS_H
#define INCIDENTS_H

#include "pause_DUE.h"
#include "reverse_DUE.h"
#include "add_health.h"
#include "reduce_health.h"
#include "../health_system.h"
#include <string>

/**
 * @brief Enumeration of all possible random events that can occur in the game
 */
enum IncidentType {
    REDUCE_TIME,    // Reduces the remaining time in the current level
    PAUSE_DUE,      // Temporarily pauses the DUE wall advancement
    REVERSE_DUE,    // Reverses the DUE wall movement
    ADD_TIME,       // Adds additional time to the current level
    ADD_HEALTH,     // Increases player's health
    REDUCE_HEALTH   // Decreases player's health
};

/**
 * @brief Triggers a random incident in the game
 * @param currentLevelTime Reference to the current level's time
 * @param playerHealth Reference to the player's health system
 * @return The type of incident that was triggered
 */
IncidentType triggerRandomIncident(int& currentLevelTime, HealthSystem& playerHealth);

/**
 * @brief Gets the display name of an incident
 * @param incident The type of incident to get the name for
 * @return String containing the incident's display name
 */
std::string getIncidentName(IncidentType incident);

/**
 * @brief Type definition for incident name functions
 */
using IncidentNameFunction = std::string(*)(IncidentType);

/**
 * @brief Array of function pointers for getting incident names by level
 */
extern IncidentNameFunction incidentNameFunctions[];

/**
 * @brief Gets the incident name for level 1
 * @param incident The incident type
 * @return String containing the level-specific incident name
 */
std::string getIncidentNameLevel1(IncidentType incident);

/**
 * @brief Gets the incident name for level 2
 * @param incident The incident type
 * @return String containing the level-specific incident name
 */
std::string getIncidentNameLevel2(IncidentType incident);

/**
 * @brief Gets the incident name for level 3
 * @param incident The incident type
 * @return String containing the level-specific incident name
 */
std::string getIncidentNameLevel3(IncidentType incident);

/**
 * @brief Gets the incident name for level 4
 * @param incident The incident type
 * @return String containing the level-specific incident name
 */
std::string getIncidentNameLevel4(IncidentType incident);

/**
 * @brief Gets the incident name for level 5
 * @param incident The incident type
 * @return String containing the level-specific incident name
 */
std::string getIncidentNameLevel5(IncidentType incident);

/**
 * @brief Gets the incident name for level 6
 * @param incident The incident type
 * @return String containing the level-specific incident name
 */
std::string getIncidentNameLevel6(IncidentType incident);

/**
 * @brief Gets the default incident name when level is unknown
 * @return String containing the default incident name
 */
std::string getIncidentNameDefault();

#endif // INCIDENTS_H 