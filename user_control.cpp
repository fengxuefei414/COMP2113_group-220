#include "user_control.h"
#include <iostream>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#include <cmath>

#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace std;

struct termios UserControl::orig_termios; // 静态成员变量定义

// 构造函数：启用终端原始模式
UserControl::UserControl(){
    enableRawMode();
}

// 析构函数：恢复终端原始模式
UserControl::~UserControl() {
    enableRawMode();
    returnToMainMenu = false;  // 初始化标志为false
}

void UserControl::resetReturnFlag() {
    returnToMainMenu = false;
}

// 启用终端原始模式
void UserControl::enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios); // 保存当前终端设置
    atexit(disableRawMode);                 // 程序退出时恢复终端模式

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON | ISIG); // 关闭回显、行缓冲和信号处理
    raw.c_cc[VMIN] = 0;                     // 非阻塞输入
    raw.c_cc[VTIME] = 1;                    // 设置超时时间
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// 恢复终端原始模式（静态函数）
void UserControl::disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); // 恢复原始终端设置
}

// 检测按键输入
char UserControl::getKeyPress() {
    char c = 0;
    fd_set fds;
    struct timeval tv = {0, 0}; // 非阻塞
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);

    if (select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0) {
        read(STDIN_FILENO, &c, 1);
    }
    return c;
}

// 处理用户输入
void UserControl::handleInput(int &playerX, int &playerY, bool &isJumping, float &playerVelocityY, float &playerVelocityX, const float JUMP_FORCE, int SCREEN_WIDTH) {
    char key = getKeyPress();
    
    // 处理按键输入
    switch (key) {
        case 'a': case 'A':
            if (playerX > 0 || playerX < SCREEN_WIDTH - 1) {
                if (!isJumping) {
                    playerX--; // 在地面上直接向左移动一格
                } else {
                    playerVelocityX = -1.0f; // 在跳跃时设置较小的向左水平速度
                }
            }
            break;
        case 'd': case 'D':
            if (playerX < SCREEN_WIDTH - 1) {
                if (!isJumping) {
                    playerX++; // 在地面上直接向右移动一格
                } else {
                    playerVelocityX = 1.0f; // 在跳跃时设置向右的水平速度
                }
            }
            break;
        case 'w': case 'W':
            if (!isJumping) {
                isJumping = true;
                playerVelocityY = JUMP_FORCE; // 开始跳跃
            }
            break;
        case 'q': case 'Q':
            // 设置返回主菜单标志
            returnToMainMenu = true;
            // displayLevelScores();
            break;
        default:
            break;
    }
}