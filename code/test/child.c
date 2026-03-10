#include "syscall.h"
#define stdout 1

int main() {
    int i;
    for (i = 0; i < 10; i++) {
        Write("This is the child thread.\n", 26, stdout);
    }
    return 0;
}
