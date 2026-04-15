#include "syscall.h"

int main() {
    int x, y;
    Pipe(&x, &y);
    PrintNum(x);
    PrintString("\n");
    PrintNum(y);
    PrintString("\n");
    return 0;
}
