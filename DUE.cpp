#include "DUE.h"
#include "All_maps/map_utils.h"
#include "Incidents/pause_DUE.h"

// 定义DUE相关变量
time_t lastDUETime;
int DUEPosition;

// 初始化DUE
void initDUE() {
    lastDUETime = time(nullptr);
    DUEPosition = 0;
    levelStartTime = time(nullptr);  // 记录关卡开始时间
}

// 更新DUE
void updateDUE(std::vector<std::vector<char> >& map) {
    // 如果DUE处于暂停状态，不进行更新
    if (isDUECurrentlyPaused()) {
        return;
    }

    // 检查是否已经过了初始暂停时间（3秒）
    time_t currentTime = time(nullptr);
    if (currentTime - levelStartTime < 3) {
        return;  // 如果还没到3秒，不更新DUE
    }

    if (currentTime - lastDUETime >= DUE_SPEED) {
        // 推进DUE
        for (int i = 0; i < MAP_HEIGHT; ++i) {
            for (int j = DUEPosition; j < DUEPosition + DUE_WIDTH; ++j) {
                if (j < MAP_WIDTH) {
                    // 根据行数循环显示D、U、E，紧密排列
                    map[i][j] = "DUE"[i % 3];
                }
            }
        }
        DUEPosition += DUE_WIDTH;
        lastDUETime = currentTime;
    }
}

// 检查是否碰到DUE
bool checkDUECollision(const std::vector<std::vector<char> >& map, int x, int y) {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        return false;
    }
    char c = map[y][x];
    return (c == 'D' || c == 'U' || c == 'E');  // 修改碰撞检测条件
} 