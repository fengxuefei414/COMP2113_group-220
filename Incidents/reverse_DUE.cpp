#include "reverse_DUE.h"

// DUE倒退
void reverseDUE(int& DUEPosition) {
    DUEPosition -= 3;  // 倒退3格
    if (DUEPosition < 0) {  // 确保不会退到负数位置
        DUEPosition = 0;
    }
} 