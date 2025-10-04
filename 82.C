#include <stdio.h>

int main() {
    // Count down from 3
    int count = 3;
    while (count > 0) {
        printf("%d... ", count--);
    }
    return 0;
}