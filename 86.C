#include <stdio.h>

int main() {
    // Keep halving a number
    int num = 100;
    while (num > 1) {
        num = num / 2;
        printf("%d ", num);
    }
    return 0;
}