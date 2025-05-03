#include "reduce_health.h"
#include "../health_system.h"

void reduceHealth(HealthSystem& health) {
    // 如果血量大于0，则减少1点血量
    if (health.health > 0) {
        health.health--;
    }
} 