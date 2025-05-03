#include "reduce_health.h"
#include "../health_system.h"

void reduceHealth(HealthSystem& health) {
    // If health is greater than 0, decrease health by 1
    if (health.health > 0) {
        health.health--;
    }
} 