#include "reduce_time.h"

// 减少关卡时间
void reduceLevelTime(int& levelTime) {
    levelTime -= 10;  // 减少10秒
    if (levelTime < 0) {  // 确保时间不会变成负数
        levelTime = 0;
    }
} 