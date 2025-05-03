#include "add_health.h"
#include "../health_system.h"

void addHealth(HealthSystem& health) {
    // If health is not full (max health is 4), increase health by 1
    if (health.health < 4) {
        health.health ++;
    }
} 