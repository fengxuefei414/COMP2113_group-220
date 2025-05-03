#ifndef HEALTH_SYSTEM_H
#define HEALTH_SYSTEM_H

#include <ctime>

/**
 * @brief Structure containing player health system properties
 */
struct HealthSystem {
    int health;          // Current health points
    bool isInvincible;   // Invincibility status
    time_t lastHitTime;  // Time of last damage taken
};

/**
 * @brief Initializes the health system with default values
 * @param health Reference to the health system to initialize
 */
void initHealth(HealthSystem& health);

/**
 * @brief Processes damage taken by the player
 * @param health Reference to the player's health system
 * @return true if the damage was fatal, false otherwise
 */
bool handleDamage(HealthSystem& health);

/**
 * @brief Updates the invincibility status based on time elapsed
 * @param health Reference to the player's health system
 */
void updateInvincibility(HealthSystem& health);

/**
 * @brief Gets the current health points
 * @param health Reference to the player's health system
 * @return Current health points value
 */
int getCurrentHealth(const HealthSystem& health);

/**
 * @brief Resets health to full and clears status effects
 * @param health Reference to the player's health system
 */
void resetHealth(HealthSystem& health);

#endif 