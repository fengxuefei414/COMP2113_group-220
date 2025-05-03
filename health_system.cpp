#include "health_system.h"
#include <iostream>

const int MAX_HEALTH = 4;         // Maximum health
const int INVINCIBLE_TIME = 1;    // Invincibility time (seconds)

// Initialize the health system
void initHealth(HealthSystem& health) {
    health.health = MAX_HEALTH;
    health.isInvincible = false;
    health.lastHitTime = 0;
}

// Handle damage
bool handleDamage(HealthSystem& health) {
    time_t currentTime = time(nullptr);
    
    // Check if invincibility is active
    if (!health.isInvincible || currentTime - health.lastHitTime >= INVINCIBLE_TIME) {
        health.health--;
        health.isInvincible = true;
        health.lastHitTime = currentTime;
        
        // Return whether the player is dead
        return health.health <= 0;
    }
    
    return false;
}

// Update invincibility status
void updateInvincibility(HealthSystem& health) {
    time_t currentTime = time(nullptr);
    if (health.isInvincible && currentTime - health.lastHitTime >= INVINCIBLE_TIME) {
        health.isInvincible = false;
    }
}

// Get the current health
int getCurrentHealth(const HealthSystem& health) {
    return health.health;
}

// Reset health
void resetHealth(HealthSystem& health) {
    health.health = MAX_HEALTH;
    health.isInvincible = false;
}