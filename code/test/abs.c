#include "syscall.h"

int main() {
    int result;
    result = Abs(-42);
    PrintNum(result);
    result = Abs(100);
    PrintNum(result);
    Halt();
}
