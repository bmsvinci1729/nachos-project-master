#include "syscall.h"

int arr[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int x = 19;

int main() {
    int i;
    PrintString("Printing array\n");
    for (i = 0; i < 10; i++) {
        PrintNum(arr[i]);
        PrintString(" ");
    }
    PrintString("\nDone with loop, x:\n");
    PrintNum(x);
    PrintString("\n");
    Halt();
}
