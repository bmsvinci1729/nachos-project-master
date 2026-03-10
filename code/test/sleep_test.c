#include "syscall.h"

int main() {
    int i;
    for (i = 0; i < 5; i++) {
        Sleep(50000);
        PrintNum(i);
    }
    return 0;
}
