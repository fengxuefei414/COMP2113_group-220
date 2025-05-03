#include "add_health.h"
#include "../health_system.h"

void addHealth(HealthSystem& health) {
    // 如果血量未满（假设最大血量为4），则增加1点血量
    if (health.health < 4) {
        health.health ++;
    }
} 