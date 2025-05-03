#include "reverse_DUE.h"

// Reverse DUE movement
void reverseDUE(int& DUEPosition) {
    DUEPosition -= 3;  // Move back 3 spaces
    if (DUEPosition < 0) {  // Ensure position doesn't become negative
        DUEPosition = 0;
    }
} 