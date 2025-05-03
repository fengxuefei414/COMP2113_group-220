#include "health_system.h"
#include <iostream>

const int MAX_HEALTH = 4;         // 最大血量
const int INVINCIBLE_TIME = 1;    // 无敌时间（秒）

// 初始化血量系统
void initHealth(HealthSystem& health) {
    health.health = MAX_HEALTH;
    health.isInvincible = false;
    health.lastHitTime = 0;
}

// 处理受伤
bool handleDamage(HealthSystem& health) {
    time_t currentTime = time(nullptr);
    
    // 检查是否处于无敌状态
    if (!health.isInvincible || currentTime - health.lastHitTime >= INVINCIBLE_TIME) {
        health.health--;
        health.isInvincible = true;
        health.lastHitTime = currentTime;
        
        // 返回是否死亡
        return health.health <= 0;
    }
    
    return false;
}

// 更新无敌状态
void updateInvincibility(HealthSystem& health) {
    time_t currentTime = time(nullptr);
    if (health.isInvincible && currentTime - health.lastHitTime >= INVINCIBLE_TIME) {
        health.isInvincible = false;
    }
}

// 获取当前血量
int getCurrentHealth(const HealthSystem& health) {
    return health.health;
}

// 重置血量
void resetHealth(HealthSystem& health) {
    health.health = MAX_HEALTH;
    health.isInvincible = false;
} 